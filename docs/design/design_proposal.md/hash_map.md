# Design Proposal — Hash Map

**SuperCoders — Project 01: Collections Library**

---

# Objective

The main objective of this project is to build a reusable **Data Structure Library** containing **Dynamic Array, Linked List and Hash Map** completely from scratch without using STL containers inside the library. The implementation will use manually managed heap memory so that the working of each data structure can be understood at a low level. The project is mainly focused on understanding how memory is allocated and deallocated manually, how different data structures are implemented internally and the design decisions involved while building them. The library will also serve as the foundation for future projects like **Redis Lite** and other **SuperCoders** projects.

The objective of the **Hash Map** is to understand hashing, collision handling, bucket management and key-value storage. It will also help in understanding how hash functions distribute keys, how collisions are handled efficiently and how resizing improves the performance of the hash map.

---

# Section 1 — Public API

```cpp
template<typename Key, typename Value>
class HashMap
{
public:

    HashMap();

    ~HashMap();

    HashMap(const HashMap& other);

    HashMap& operator=(const HashMap& other);

    void insert(const Key& key,const Value& value);

    void remove(const Key& key);

    Value& get(const Key& key);

    bool contains(const Key& key) const;

    int size() const;

    bool isEmpty() const;

private:

    size_t hash(const Key& key) const;

    void rehash();

};
```

- `insert()` inserts a new key-value pair into the hash map. If the key already exists its value will be updated.

- `remove()` removes the key-value pair associated with the given key.

- `get()` returns the value associated with the given key.

- `contains()` checks whether the key exists inside the hash map.

---

# Section 2 — Internal Representation

The Hash Map will be implemented using **template programming** so that it can store any type of key and value. It will use **Separate Chaining** to handle collisions.

The class will contain the following private data members.

```cpp
Bucket* buckets;

int _size;

int _capacity;

float _loadFactor;
```

- **buckets** points to the dynamically allocated bucket array which store pointer to linked list object.

- **_size** stores the total number of key-value pairs currently present.

- **_capacity** stores the total number of buckets.

- **_loadFactor** determines when rehashing should be performed.

Each bucket will point to a linked list.

```cpp
template<typename Key,typename Value>
struct Node
{
    Key key;
    Value value;
    Node* next;
};
```

Whenever two different keys produce the same hash value they will be stored in the same bucket using a linked list.

![Hash Map Memory Layout](/design/memory_diagram/hash_map.jpg)

---

### Memory Management

Every node will be allocated dynamically using **malloc()** followed by **placement new**. Whenever a node is removed its destructor will be called manually before freeing the memory.

The bucket array will also be allocated dynamically.

---

### Rehashing

Whenever the load factor becomes greater than **0.9**, a new bucket array with double the previous capacity will be allocated.

Every existing key-value pair will then be hashed again using the new capacity and inserted into the new bucket array.

After all elements are copied, the previous bucket array will be destroyed and freed.

---

### Rule of Three

- **Destructor** frees every linked list node and then frees the bucket array.

- **Copy Constructor** creates a completely new bucket array and inserts every key-value pair into the new hash map.

- **Assignment Operator** first frees the previous hash map and then performs a deep copy.

---

# Section 3 — Complexity Estimates

| Operation | Best Case | Average Case | Worst Case | Reason |
|------------|-----------|--------------|-------------|--------|
| Constructor | O(1) | O(1) | O(1) | Initializes member variables. |
| Destructor | O(n) | O(n) | O(n) | Every node must be destroyed. |
| Copy Constructor | O(n) | O(n) | O(n) | Every key-value pair is copied. |
| Assignment Operator | O(n) | O(n) | O(n) | Frees old data and copies every element. |
| insert() | O(1) | O(1) | O(n) | Normally inserts into one bucket. Worst case all keys collide. |
| remove() | O(1) | O(1) | O(n) | Searches only one bucket unless all keys collide. |
| get() | O(1) | O(1) | O(n) | Direct bucket access followed by linked list traversal. |
| contains() | O(1) | O(1) | O(n) | Same as get(). |
| size() | O(1) | O(1) | O(1) | Returns stored size. |
| isEmpty() | O(1) | O(1) | O(1) | Checks whether size is zero. |
| rehash() | O(n) | O(n) | O(n) | Every element must be inserted into the new bucket array. |

---

# Section 4 — Design Decisions

## Separate Chaining

The Hash Map will use **Separate Chaining** to handle collisions. If multiple keys produce the same hash value they will be stored inside a linked list of that bucket. This keeps insertion and deletion simple and avoids the clustering problem of open addressing. In Linear Probing, if a collision occurs the new element is inserted into the next available index. If that index is also occupied it checks the next one and continues until an empty position is found. Over time many consecutive positions become occupied, forming a cluster. As the cluster grows, future insertions and searches require more comparisons because more occupied positions need to be checked. In Separate Chaining, collided elements are stored in the linked list of the same bucket instead of occupying consecutive buckets, so this clustering problem does not occur.

---

## Automatic Resizing 

Why I need to resize the hashmap if infinite key-value pair can be stored using chaining. The reason is performance, suppose hash map have a capacity of 4 and we are storing 1000 element, average nodes per bucket will be 1000/4 that is 250 now for searching a specific node there will 250 comparision rather than 1 or 2 so the complexity will become O(n).
So for solving this problem we do resizing generally we double the capacity, from 4 the capacity will become 8 then 16,32,64 now 1000/64 will be 16 which will make the linked list shorter and decrease number of comparision for searching result in reducing the time complexity for operation like insertion,deletion,search.

---

## Why Rehashing

We do rehashing because the bucket capacity changes. During resizing a new bucket array with larger capacity is allocated in heap memory and all the old key-value pairs need to be copied into it. But now the capacity has changed, so the bucket index generated by the hash function will also change. Therefore the keys cannot simply be copied to the same position in the new bucket array. Suppose we just copy the old data to the same bucket index. Later when we try to search for a key, the hash function will use the new capacity to calculate the bucket index **(hash(key) % newCapacity)**. This will generate a different bucket index while the key is still stored in the old bucket, so the element will not be found. Therefore every key must be hashed again and inserted into its new bucket.

---

## Load factor

The load factor is used to decide when the hash map should be resized.It is the ratio of the number of key-value pairs stored in the Hash Map to the total number of buckets.
**Formula -> Load Factor = size / capacity**
For example, if the Hash Map contains 6 key-value pairs and the bucket array has 8 buckets, then

Load Factor = 9 / 8 = 1.1

Whenever the load factor becomes greater than the predefined threshold (0.9), the Hash Map will create a new bucket array with double the capacity and perform rehashing. This keeps the average number of elements in each bucket small, resulting in faster insertion, searching and deletion.

---

## Load factor threshold
I have set the load factor to 0.9.If I set the load factor smaller like 0.5 there will be need to resize even after small number of insertion like I have 5 capacity i insert 11 element,now I insert 10 element more then resize again even if there are empty slot in the bucket.If I make the load factor large like 2 resizing would never happen and the timecomplexity of operation like insert,search would be O(n). 

## Memory Management Using malloc() and Placement New

The implementation uses **malloc()**, **placement new** and **free()** because the project requires manual memory management. Constructors and destructors must be called manually for every stored object.

---

## Exception Handling
The methods get() will throw an exception if the given key is not found in the Hash Map. This is done because returning a dummy value is not possible for a template class. Different data types have different valid values, so there is no single value that can represent an error. Throwing an exception makes the error clear and avoids unexpected behaviour.

---

