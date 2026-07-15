# Design Proposal v2 — Hash Map

**SuperCoders — Project 01: Collections Library**

---

# Objective

This is the second version of my Hash Map design proposal. After I started implementing the Hash Map, I realized that some parts of my original design were either incomplete or needed to change once I started writing the actual code.

The main objective is still the same: to understand how hashing works, how collisions are handled, how buckets are managed, and how resizing is performed. However, during implementation I had to make several design decisions that were not covered in the first proposal. In this version, I have updated the design to explain how buckets are actually represented, how different key types are hashed, and how lookup, insertion, update, and removal share common logic instead of duplicating code.

---

# Section 1 — Public API (v2)

```cpp
template<typename Key, typename Value>
struct KV
{
    Key key;
    Value value;
    KV(Key k, Value v);
    bool operator==(const KV<Key,Value>& other) const;
};

template<typename Key, typename Value>
class HashMap
{
public:

    HashMap();
    ~HashMap();
    HashMap(const HashMap& other);
    HashMap& operator=(const HashMap& other);

    void insert(const Key& key, const Value& value);
    bool remove(const Key& key);
    Value& get(const Key& key);
    bool contains(const Key& key);

    int size() const;
    bool isEmpty() const;

private:
    size_t hash(const Key& key) const;
    void rehash();
    Value* find(const Key& key);
};
```

### What changed from v1, and why

In my first proposal, I mentioned that each bucket would point to a linked list, but I never clearly defined what a bucket actually was. During implementation, I realized there was no need to create a separate Bucket class because I had already built a generic LinkedList<T>. Instead of writing another class that performs insertion, deletion, and traversal again, I simply made every bucket a LinkedList<KV<Key, Value>>. This allowed me to reuse code that was already implemented and tested.

I also changed the way key-value pairs are stored. In the original proposal, I combined the linked list node and the key-value pair into a single structure. Later I realized that this duplicated responsibilities. The Node<T> inside LinkedList already manages the linked list structure, so I introduced a separate KV<Key, Value> structure whose only job is to store the key and value. This keeps both classes cleaner and more reusable.

Another change was the remove() function. Earlier it returned void, but during implementation I realized that the caller has no way to know whether anything was actually removed. Returning a bool makes it possible to know if the key existed without having to call contains() first.

I also changed the behavior of get(). My original design assumed that trying to access a missing key would simply be an error. While implementing it, I decided to follow the behavior of std::map::operator[] instead. Now, if a key doesn't exist, a default value is inserted automatically and a reference to it is returned. This makes the function useful for both reading and creating entries, although it also means that missing keys are silently created.

Another problem I had to solve was hashing generic key types. In the original proposal, I simply wrote a hash() function without explaining how it would work for different types. During implementation, I decided to support only int and std::string keys for now. I used if constexpr to choose the correct hashing implementation at compile time and added a static_assert so unsupported key types produce a clear compiler error instead of confusing compilation failures.

Finally, I noticed that insert(), get(), and contains() all started by performing exactly the same steps: hash the key, locate the correct bucket, and search inside the linked list. Instead of writing the same logic three times, I added a private find() helper that all three functions can reuse.
---

# Section 2 — Internal Representation

```cpp
LinkedList<KV<Key,Value>>* buckets;
int m_size;
int m_capacity;
```

(`_loadFactor` from the original proposal is now a fixed constant of `0.9f` checked inline in `insert()`, rather than a stored member — it never needs to vary at runtime, so storing it as a field added a member with no behavioral benefit.)

### Constructing the bucket array

Unlike `DynamicArray`, which can start with `_capacity = 0` and allocate lazily on first use, `HashMap` must allocate a non-empty bucket array immediately in its constructor — every lookup computes `hash(key) % m_capacity`, and a `_capacity` of `0` would divide by zero. The constructor starts at a fixed initial capacity of `8` buckets, each `malloc`'d as raw memory and placement-new'd into an empty `LinkedList<KV<Key,Value>>()`.

### Hashing (`if constexpr` type dispatch)

```cpp
if constexpr (std::is_integral<Key>::value)
{
    return static_cast<size_t>(key);
}
else if constexpr (std::is_same<Key, std::string>::value)
{
    size_t h = 0;
    for (char c : key) { h = h * 31 + static_cast<unsigned char>(c); }
    return h;
}
else
{
    static_assert(std::is_integral<Key>::value || std::is_same<Key, std::string>::value,
                  "HashMap only supports int and std::string keys for now");
}
```
`if constexpr` (rather than a plain runtime `if`) is required here: the string-hashing branch (`for(char c : key)`) would fail to *compile* for a `Key` like `int`, which can't be iterated over. `if constexpr` discards the non-matching branch entirely at compile time for each instantiation, so only the branch relevant to the actual `Key` type is ever compiled.

`size_t` (rather than `int`) is used throughout for hash values and bucket indices specifically because it is unsigned: an `int` hash that overflows can wrap to a negative number, and `negative % capacity` in C++ can itself be negative — producing an out-of-bounds, negative array index. `size_t` makes that entire failure mode structurally impossible.

### Separate Chaining via Reused `LinkedList`

When `hash(key) % m_capacity` produces the same index for two different keys, both are simply appended to that bucket's `LinkedList<KV<Key,Value>>` — collision handling costs nothing extra to implement since it's just ordinary list insertion.

### Rule of Four (Constructor, Destructor, Copy Constructor, Copy Assignment)

- **Copy constructor / copy assignment** both allocate a fresh bucket array at `other.m_capacity`, then placement-new **each bucket using `LinkedList`'s own copy constructor** (`new (&buckets[i]) LinkedList<KV<Key,Value>>(other.buckets[i])`), so every chain — and every `KV` node within it — is independently, deeply copied. This depends on `LinkedList` itself correctly implementing a deep-copying copy constructor, which was a gap identified and fixed as part of this same revision.
- **Copy assignment** additionally destroys and frees `*this`'s existing bucket array *before* copying from `other`, and checks for self-assignment (`this == &other`) first — without that check, freeing `*this`'s buckets would also destroy `other`'s buckets when `other` and `*this` are the same object.

### Resizing (`rehash()`)

When `m_size / m_capacity` exceeds a load factor of `0.9`, `insert()` triggers `rehash()`: a new bucket array of double the capacity is allocated, then every existing entry (visited via each old bucket's `Iterator`) is re-hashed against the *new* capacity and reinserted, since an entry's correct bucket index depends on capacity. Every entry must be revisited — an entry's old index has no guaranteed relationship to its new one once capacity changes.

![Hash Map Memory Layout](/docs/design/memory_diagram/hash_map.jpg)

---

# Section 3 — Complexity Estimates

| Operation | Best | Average | Worst | Why |
|---|---|---|---|---|
| `hash()` | O(1) | O(1) / O(k) for strings | O(k) | Constant for integral keys; O(k) for a string key of length k (one pass over its characters). |
| `insert()` | O(1) | O(1) | O(n) | Average case assumes good hash distribution (short chains). Worst case: all keys collide into one bucket, degrading to a linear scan of that chain; also amortized cost of an occasional `rehash()`. |
| `get()` / `find()` / `contains()` | O(1) | O(1) | O(n) | Same reasoning as `insert()` — dependent on chain length in the target bucket. |
| `remove()` | O(1) | O(1) | O(n) | Locating the key costs the same as `find()`; unlinking within `LinkedList::deleteValue` is O(1) once the node is located. |
| `rehash()` | O(n) | O(n) | O(n) | Must visit and reinsert every existing entry into the new, larger bucket array. |
| `size()` / `isEmpty()` | O(1) | O(1) | O(1) | Return the stored `m_size` counter directly. |

---

# Section 4 — Design Decisions (additions)

## Reusing `LinkedList` for Buckets Instead of a Custom Bucket Class

While designing the Hash Map, I thought about creating a separate Bucket class. However, I realized that it would mostly duplicate the work my LinkedList<T> already does. A bucket only needs to store multiple key-value pairs and support insertion, deletion, searching, and traversal. Since my LinkedList already provides all of these operations, creating another class didn't make much sense.

Instead, I made every bucket a LinkedList<KV<Key, Value>>. This lets the Hash Map reuse the LinkedList implementation instead of maintaining two different classes that solve the same problem. This decision also led me to improve the LinkedList itself by adding Iterator, find(), and deleteValue(), making it reusable by other data structures as well.

## Restricting `hash()` to `int` and `std::string` For Now

While implementing the hashing function, I realized that writing a truly generic hash function isn't as simple as I originally thought. Different types require different hashing strategies, and supporting every possible type would require users to provide their own hash function or use a more complex design.

Since the goal of this project is to understand how a Hash Map works rather than build a complete STL replacement, I decided to support only int and std::string keys for now. Using if constexpr allows the correct hashing code to be selected at compile time, and unsupported types produce a clear compiler error using static_assert. This keeps the implementation simple while leaving room for future improvements.

## `get()`'s Insert-on-Missing-Key Behavior

My original design assumed that calling get() with a missing key should result in an error. While implementing the Hash Map, I realized that automatically creating the entry makes many common use cases much simpler.

Because of this, I changed the behavior to match std::map::operator[]. If the key already exists, the stored value is returned. If it doesn't exist, a default-constructed value is inserted first, and then a reference to that value is returned.

I know this also has a drawback because typing the wrong key will silently create a new entry instead of reporting an error. However, for this project I felt that the simpler interface was a better tradeoff, and this behavior can always be changed in a future version if needed.