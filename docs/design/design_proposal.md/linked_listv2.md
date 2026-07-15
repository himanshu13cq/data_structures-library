# Design Proposal v2 — LinkedList

**SuperCoders — Project 01: Collections Library**

---

# Objective

This is the second version of my LinkedList design proposal. I didn't originally plan to change the LinkedList API, but once I started designing the HashMap,I realized that the original interface wasn't enough.

The main objective of LinkedList is still the same: to understand how pointer-based, heap-allocated data structures work and to correctly implement the Rule of Three. However, now the LinkedList also needs to work as a reusable building block for the HashMap.

While designing the HashMap, I found two new requirements that my original LinkedList couldn't support. First, I needed a way to search for an element and update it directly if it already existed. Returning only a boolean from search() wasn't enough because I also needed access to the actual stored object. Second, during rehashing, I needed a way to visit every element in every bucket without exposing the internal Node pointers outside the class.

Because of these new requirements, I revised the public API and added a few new features while keeping the internal implementation almost the same.

---

## Section 1 — Public API (v2)

```cpp
template<typename T>
class LinkedList {
public:
    class Iterator
    {
        Iterator(Node<T>* node);
        T& operator*();
        Iterator& operator++();
        bool operator!=(const Iterator& other) const;
    };

    Iterator begin() const;
    Iterator end() const;

    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);              
    LinkedList& operator=(const LinkedList& other);    

    void insertFront(const T& value);
    void insertBack(const T& value);
    void insert(int index, const T& value);

    void deleteFront();
    void deleteAt(int index);
    bool deleteValue(const T& value);

    T* find(const T& value) const;
    void print() const;
    const int size() const;

private:
    Node<T>* createNode(const T& value);
    void     destroyNode(Node<T>* node);
};
```

### What changed from v1, and why

In the first version, I had a search() function that returned only a boolean. At that time, it was enough because I only needed to know whether an element existed or not.

Later, while designing the HashMap, I realized that this wasn't sufficient anymore. When inserting a key-value pair into the HashMap, I first need to check whether the key already exists. If it does, I don't want to insert another node—I simply want to update the existing value. Returning true or false doesn't tell me where that element is, so I replaced search() with find(), which returns a T*. Now I can both check whether an element exists (nullptr means it doesn't) and modify it directly if it does.

Although find() is marked as const, it still returns a non-const pointer. The const here only means that searching should not modify the structure of the LinkedList itself. The list's head, tail, and size remain unchanged during the search. Returning a mutable pointer allows the HashMap to update an existing value without performing another lookup.

I also added deleteValue(). Earlier, I only had deleteAt(index), but the HashMap never knows the position of an element inside a bucket. It only knows the key that should be removed. Because of that, removing by index wasn't useful for the HashMap, so I added deleteValue(), which searches for the element and removes it if it exists.

Another important addition is the nested Iterator class. Before this, there was no safe way for another class to visit every element stored inside the LinkedList. One option was exposing the internal Node<T>*, but that would allow outside code to directly modify next pointers and potentially corrupt the list. Instead, I added a simple iterator that only supports dereferencing, moving to the next node, and comparison. This gives the HashMap everything it needs for rehashing while keeping the internal structure of the LinkedList hidden.

---

## Section 2 — Internal Representation

The internal representation remains almost the same as the first version. Each node is allocated separately on the heap using malloc and placement new. Every node stores the data and a pointer to the next node, while the LinkedList itself maintains head, tail, and m_size. I also renamed _size to m_size so the naming is consistent with the other data structures in the project.

The iterator itself is very simple. Internally, it only stores a single Node<T>* representing the current position in the list.

**`Iterator` internal representation:**
```cpp
class Iterator
{
    Node<T>* current;
public:
    Iterator(Node<T>* node) : current(node) {}
    T& operator*() { return current->data; }
    Iterator& operator++() { current = current->next; return *this; }
    bool operator!=(const Iterator& other) const { return current != other.current; }
};
```
begin() simply returns an iterator pointing to head, while end() returns an iterator containing nullptr. Since the LinkedList already ends with a null pointer, I can reuse that as the "one past the last element" position instead of introducing another special marker.

Both find() and deleteValue() rely on operator== being available for the stored type T. The LinkedList itself doesn't define what equality means. Instead, it leaves that responsibility to the type stored inside the list, keeping the implementation completely generic.

![LinkedList Memory Layout](/docs/design/memory_diagram/linked_list.jpg)

---

## Section 3 — Complexity Estimates (additions)

| Operation | Best | Average | Worst | Why |
|---|---|---|---|---|
| `find(value)` | O(1) | O(n) | O(n) | Best case: value is at `head`. Worst case: value is at the last node or absent — must traverse the whole list. |
| `deleteValue(value)` | O(1) | O(n) | O(n) | Best case delegates to `deleteFront()`. Otherwise requires a `prev`/`curr` walk to locate the matching node and its predecessor. |
| `begin()` / `end()` | O(1) | O(1) | O(1) | Each just wraps a single pointer (`head` or `nullptr`); no traversal happens until the loop actually calls `operator++`. |

---

## Section 4 — Design Decisions (additions)

## Iterator Instead of an `getHead()` function

When I started implementing the HashMap, one idea was to simply expose a getHead() function so the HashMap could walk through the LinkedList using raw Node<T>* pointers. Although this would have worked, I decided not to do it because it would expose the internal implementation of the LinkedList. Any external code could then directly modify the next pointers and accidentally corrupt the list.

Instead, I implemented a simple Iterator. It still allows other classes to visit every element in the list, which is exactly what the HashMap needs during rehashing, but it keeps the internal nodes hidden. This way, the LinkedList remains encapsulated while still being reusable.

## `find()` Returns a Pointer, Not a Reference

While designing the new API, I considered returning a reference from find(). However, a reference always has to refer to a valid object, so there would be no way to represent the case where the element doesn't exist.

Returning a pointer makes this much simpler. If the element is found, find() returns a pointer to it. Otherwise, it returns nullptr. This also lets the HashMap directly update an existing value without performing another lookup.

## `deleteValue()` Reuses `deleteFront()` for the Head Case

When implementing deleteValue(), I noticed that deleting the first node is different from deleting any other node. In the head case, there is no previous node, and both head and tail may need to be updated if the list becomes empty.

Since I had already implemented this logic correctly inside deleteFront(), I decided to reuse that function instead of writing the same code again. This avoids duplication and ensures that the head deletion logic only exists in one place, making it easier to maintain and less likely to introduce bugs later.