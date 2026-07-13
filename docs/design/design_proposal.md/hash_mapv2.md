# Design Proposal v2 — Hash Map

**SuperCoders — Project 01: Collections Library**

---

# Objective

This is a revision of the original Hash Map design proposal, written after implementation revealed several places where the original design was underspecified or needed to change once real code had to compile and run. The core objective — understanding hashing, collision handling, bucket management and resizing — is unchanged; this document fills in what the original left open: how buckets are actually represented, how a generic `Key` gets hashed at all, and how lookup/update/removal share logic.

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

- **Buckets are `LinkedList<KV<Key,Value>>*`, not a custom `Bucket` type.** The original proposal described "buckets point to linked list objects" without specifying the concrete type. Rather than inventing a separate `Bucket` wrapper class, each bucket directly reuses the project's own `LinkedList<T>` — each bucket *is* a `LinkedList` whose element type happens to be a `KV` pair. This avoids duplicating chain-management logic (traversal, insertion, deletion) that `LinkedList` already implements and tests.
- **A `KV` struct replaces the bare `Node<Key,Value>` described in v1.** The original proposal's `Node` combined "an element in a chain" with "a key-value pair" into one struct. Splitting them lets `LinkedList<T>`'s existing `Node<T>` handle the chain-linkage part generically, while `KV<Key,Value>` handles only the key-value pairing — `LinkedList<KV<Key,Value>>` composes the two rather than duplicating linked-list logic inside the Hash Map itself.
- **`remove()` now returns `bool`, not `void`.** The original signature couldn't distinguish "the key was removed" from "the key was never there" — both looked identical to a caller. Returning whether removal actually happened lets calling code detect a no-op removal without a separate `contains()` check first.
- **`get()` follows `operator[]`-style semantics, not `at()`-style.** The v1 proposal implied `get()` on a missing key was simply invalid/undefined. In the actual implementation, `get()` on a missing key inserts that key with a default-constructed `Value` and returns a reference to it — mirroring `std::map::operator[]` rather than `std::map::at()`. This was a deliberate trade during implementation: it keeps `get()` usable for both reading and "get-or-create" patterns without a second method, at the cost of requiring `Value` to be default-constructible and of silently creating entries on typos. **This is the one part of the original design intentionally not followed as originally written** — the original spec assumed exception-on-missing-key behavior.
- **`hash()` only supports `int` and `std::string` keys, resolved at compile time via `if constexpr`.** The original proposal left "how does hash() work for an arbitrary Key type" unanswered. Since a truly generic hash (working for any possible `Key`) isn't something that can be written without either restricting `Key` or requiring the caller to supply their own hash function, the implementation currently branches on `Key`'s actual type at compile time and rejects anything else via `static_assert`, with a clear compiler error rather than a confusing one.
- **`find()` is a new private helper, shared by `insert()`, `get()`, and `contains()`.** All three operations need the exact same first step — hash the key, locate the bucket, search its chain — so this logic lives in exactly one place instead of being duplicated three times.

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

Writing a separate `Bucket` class purely to wrap a chain of `KV` pairs would have duplicated logic (insertion, deletion, traversal) that `LinkedList<T>` already provides generically. Making each bucket a `LinkedList<KV<Key,Value>>` treats the Hash Map as *composed of* the project's own data structures rather than reimplementing chain management a second time — this is also why `LinkedList` gained a generic `Iterator` and `find()`/`deleteValue()` methods during this revision: they weren't originally needed until `LinkedList` had to serve double duty as a reusable bucket type.

## Restricting `hash()` to `int` and `std::string` For Now

A fully generic hash function that works for *any* `Key` type isn't achievable without either requiring callers to supply their own hashing strategy (e.g. a template policy parameter) or restricting supported types. Given the project's current scope, restricting to `int` and `std::string` — resolved at compile time so unsupported types fail fast with a clear `static_assert` message — was chosen over the added complexity of a pluggable hashing policy, which remains a possible future extension.

## `get()`'s Insert-on-Missing-Key Behavior

This is a deliberate deviation from the original design proposal (which assumed `get()` would throw or otherwise reject a missing key). Implementing `get()` to insert a default-constructed value on a miss — matching `std::map::operator[]` rather than `std::map::at()` — was chosen for simplicity, avoiding a separate exception-handling path for what is, in practice, a common "get or create" access pattern. The tradeoff, noted for future revisions: this makes it impossible to distinguish "the key existed with a default value" from "the key didn't exist and was just created," and a mistyped key silently creates a new entry rather than surfacing an error.