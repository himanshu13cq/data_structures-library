# Design Proposal — LinkedList

**SuperCoders — Project 01: Collections Library**

---

# Objective

The main objective of this project is to build a reusable **Data Structure Library** containing **Dynamic Array, Linked List and Hash Map** completely from scratch without using STL containers inside the library. The implementation will use manually managed heap memory so that the working of each data structure can be understood at a low level. The project is mainly focused on understanding how memory is allocated and deallocated manually, how different data structures are implemented internally and the design decisions involved while building them. The library will also serve as the foundation for future projects like **Redis Lite** and other **SuperCoders** projects.

The objective of the **Linked List** is to understand pointer based data structures where every node is allocated separately in heap memory and connected using pointers instead of storing data in contiguous memory. It will also help in understanding manual memory management, traversal using pointers and the Rule of Three to avoid shallow copy, dangling pointers and double free problems.

---

## Section 1 — Public API

```cpp
template<typename T>
class LinkedList {
public:
    LinkedList();
    ~LinkedList();
    LinkedList(const LinkedList& other);              
    LinkedList& operator=(const LinkedList& other);    

    void insertFront(const T& value);
    void insertBack(const T& value);
    void insert(int index, const T& value);

    void deleteFront();
    void deleteAt(int index);

    bool search(const T& value) const;
    void print() const;
    int  size() const;

private:
    Node<T>* createNode(const T& value);
    void     destroyNode(Node<T>* node);
};
```

- `insertBack` gives O(1) append by maintaining a `tail` pointer, which several later
  use cases (e.g. building a list in original order, or using this structure as a queue)
  need. Without it, appending would require O(n) traversal every time.
- `deleteAt(index)` is the natural counterpart to `insert(index, value)` — the handbook
  requires "deletion" alongside "insertion (front and arbitrary)," and without it you could insert anywhere but only delete from the front.

---

## Section 2 — Internal Representation

The Linked List will be implemented using template programming so that it can store any type of data like **int, double, char, string or user defined classes**. Unlike Dynamic Array the elements are not stored in contiguous memory. Every element is stored inside a separate node allocated in heap memory and every node stores the address of the next node.

**Node structure:**
```cpp
template<typename T>
struct Node {
    T data;
    Node* next;
};
```
Singly linked (one `next` pointer, no `prev`). Each node is a separate heap allocation
obtained via `malloc` + placement-new  rather than `new`.

**Class fields:** `head`, `tail`, `_size`.

`tail` is kept in addition to `head` specifically so `insertBack` is O(1) instead of O(n).
The tradeoff is that every operation which can change what the *last* node is
(`insertBack`, `insertFront` on an empty list, `deleteFront` on a single-node list,
`deleteAt` on the last index) must also correctly update `tail` — this is the most
error-prone part of the implementation.

![Linked List memory layout](/design/memory_diagram/linked_list.jpg)


### Memory Management (malloc/placement-new instead of new/delete)

Nodes are allocated with `malloc` and constructed with
placement-new, rather than `new`:

```cpp
Node<T>* createNode(const T& value) {
    Node<T>* node = static_cast<Node<T>*>(std::malloc(sizeof(Node<T>)));
    new (node) Node<T>(value);   // placement new: construct T in raw memory
    return node;
}

void destroyNode(Node<T>* node) {
    node->~Node<T>();            // explicitly call T's destructor
    std::free(node);             // then release raw memory
}
```

`malloc` only reserves raw, uninitialized bytes — it does not invoke `T`'s constructor,
which is why placement-new is required immediately afterward. Symmetrically, `free`
only releases bytes — it does not invoke `T`'s destructor, so the destructor must be
called explicitly before `free`. Every allocation and deallocation in the class routes
through these two helpers so this pairing is never duplicated or forgotten at a call site.

### Rule of Three

- **Destructor:** walks `head` to the end, calling `destroyNode` on every node, then
  resets `tail` to `nullptr`. This guarantees zero leaks regardless of list length.
- **Copy constructor:** initializes the new list to empty (`head = tail = nullptr`,
  `_size = 0`), then walks the *source* list from its `head`, calling `insertBack` for
  each element. This produces a deep copy — every node in the new list is a fresh
  `malloc`'d allocation, not a shared pointer to the source's nodes.
- **Copy assignment operator:** guards against self-assignment (`this == &other`) by
  returning immediately if true. Otherwise, it frees all of `*this`'s existing nodes
  (same loop as the destructor), resets to empty, then deep-copies from `other` using
  the same walk-and-`insertBack` pattern as the copy constructor.
- **Consequence of choosing deep copy over shallow copy:** shallow copy (copying the
  `head`/`tail` pointers directly) would leave two `LinkedList` objects pointing at the
  same physical nodes. When the first object's destructor runs, it frees those nodes;
  when the second object's destructor later runs, it attempts to free already-freed
  memory — a double free, which crashes and is flagged by valgrind as "Invalid free."
  Deep copy avoids this entirely at the cost of an O(n) copy instead of O(1).

---

## Section 3 — Complexity Estimates

| Operation | Best | Average | Worst | Why |
|---|---|---|---|---|
| `insertFront` | O(1) | O(1) | O(1) | Only reassigns `head` (and `tail` if list was empty); no traversal. |
| `insertBack` | O(1) | O(1) | O(1) | `tail` pointer gives direct access to the last node; no traversal needed. |
| `insert(index)` | O(1) | O(n) | O(n) | Best case is index 0 or `_size` (delegates to O(1) shortcuts). Otherwise must walk from `head` to reach position `index - 1`. |
| `deleteFront` | O(1) | O(1) | O(1) | Only reassigns `head` (and `tail` if list becomes empty); no traversal. |
| `deleteAt(index)` | O(1) | O(n) | O(n) | Best case is index 0 (delegates to `deleteFront`). Otherwise must walk to position `index - 1` to find the predecessor node. |
| `search` | O(1) | O(n) | O(n) | Best case: value is at `head`. Worst case: value is at the last node or absent — must traverse the whole list. |
| Copy constructor / assignment | O(n) | O(n) | O(n) | Must visit and re-allocate every node in the source list; no shortcut is possible for a correct deep copy. |

---

## Section 4 — Design Decisions

## Singly Linked List
The Linked List will be implemented as a **Singly Linked List** because only forward traversal is required. A Doubly Linked List would require an extra `prev` pointer in every node which would increase memory usage and make insertion and deletion more complex.

## Maintaining a Tail Pointer
A **tail** pointer will also be maintained so that inserting a node at the end of the list can be done in **O(1)** time. Without a tail pointer every insertion at the back would require traversing the whole linked list resulting in **O(n)** time.

## Exception Handling
The implementation will use **exceptions** whenever an invalid index is accessed or deletion is performed on an empty list. Returning sentinel values is not suitable because the linked list is implemented using templates and every data type does not have a common invalid value.

## Memory Management Using Helper Functions
The helper functions **createNode()** and **destroyNode()** will be used so that memory allocation and deallocation is handled at only one place. This avoids writing the same code multiple times and reduces the chances of memory leaks.

## Reusing Existing Functions
Boundary cases like inserting at index **0** or deleting the first node will use the already existing **insertFront()** and **deleteFront()** functions instead of writing the same logic again. This keeps the implementation simpler and avoids code duplication.