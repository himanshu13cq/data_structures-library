# Design Proposal v2 — LinkedList

**SuperCoders — Project 01: Collections Library**

---

# Objective

This is a revision of the original Linked List design proposal, written after the Hash Map's separate-chaining requirements exposed gaps in the original public API. The core objective is unchanged — understanding pointer-based, heap-allocated data structures and the Rule of Three — but the class now also needs to support being used as a **reusable building block for another data structure** (the Hash Map's buckets), which introduced two new requirements: searching/updating by value from outside the class, and read access to every element without exposing raw `Node` pointers.

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

- **`search()` was replaced with `find()`.** The original `bool search(const T& value) const` could only answer "does this value exist?" — it had no way to hand back *where* it was found. Once the Hash Map needed to update an existing key's value in place (rather than just check for existence), a boolean wasn't enough information. `find()` returns `T*` — a pointer directly into the matching node's data — so a caller can both check existence (`!= nullptr`) and modify the element through the returned pointer.
- **`find()` returns a non-`const` `T*` even though the method is `const`.** `const` here is a promise about the *list structure* (head/tail/size won't change during the search) — it says nothing about the element itself. Returning a mutable pointer lets `HashMap::insert()` overwrite an existing value in place without needing a second, separate lookup.
- **`deleteValue(const T& value)` is new.** `deleteAt(index)` only supports removal by position, but the Hash Map needs to remove an entry by *key*, without knowing (or caring about) its position in the bucket's chain. `deleteValue` searches for a matching element and removes it if found, reusing `deleteFront()` for the head case and a standard two-pointer (`prev`/`curr`) walk for every other position.
- **`Iterator` (nested class) is new.** Before this, there was no way to read every element in a list from outside the class without exposing `Node<T>*` directly (which would break encapsulation — external code could then freely rewrite `next` pointers and corrupt the list). The Hash Map's `rehash()` needs to visit every entry in every bucket to relocate it into a bigger bucket array. `Iterator` wraps a `Node<T>*` and implements just the three operators (`*`, `++`, `!=`) required for C++'s range-based `for` loop, letting `rehash()` write `for(auto& kv : bucket) { ... }` instead of manually chasing `->next` pointers itself.

---

## Section 2 — Internal Representation

Unchanged from v1: nodes are separately heap-allocated via `malloc` + placement-new, linked forward-only via `next`, with `head`/`tail`/`m_size` (renamed from `_size` for naming consistency with `HashMap` and `DynamicArray`) tracked as class fields.

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
An iterator is nothing more than a wrapper around "a position in the list" — here, a single `Node<T>*`. `begin()` returns `Iterator(head)`; `end()` returns `Iterator(nullptr)`, using the list's existing null-termination as a free sentinel for "one past the last element" rather than inventing separate bookkeeping.

**`find()` and `deleteValue()` both rely on `T` supporting `operator==`.** Neither `LinkedList` nor `Node` define this — it's a requirement pushed onto whatever `T` is used for the list, deliberately kept that way so `LinkedList` itself stays fully generic and has no knowledge of what "equality" means for its stored type.

---

## Section 3 — Complexity Estimates (additions)

| Operation | Best | Average | Worst | Why |
|---|---|---|---|---|
| `find(value)` | O(1) | O(n) | O(n) | Best case: value is at `head`. Worst case: value is at the last node or absent — must traverse the whole list. |
| `deleteValue(value)` | O(1) | O(n) | O(n) | Best case delegates to `deleteFront()`. Otherwise requires a `prev`/`curr` walk to locate the matching node and its predecessor. |
| `begin()` / `end()` | O(1) | O(1) | O(1) | Each just wraps a single pointer (`head` or `nullptr`); no traversal happens until the loop actually calls `operator++`. |

---

## Section 4 — Design Decisions (additions)

## Iterator Instead of an Exposed `getHead()`

An earlier option considered was simply exposing a `getHead()` accessor so external code (the Hash Map) could walk the chain itself using raw `Node<T>*` pointers. This was rejected: it would let any caller freely rewrite `next` pointers and corrupt the list's internal structure from outside the class. A minimal `Iterator` (supporting only read/advance/compare, not arbitrary pointer mutation) gives external code the ability to *visit* every element without the ability to *break* the list's invariants.

## `find()` Returns a Pointer, Not a Reference

`T*` was chosen over `T&` specifically so "not found" has a natural representation: `nullptr`. A reference cannot be null, which would have forced an exception-based "not found" signal even for a simple internal helper used only by trusted, cooperating code (the Hash Map itself) — unnecessary overhead for a private-facing utility method.

## `deleteValue()` Reuses `deleteFront()` for the Head Case

Removing the first node is structurally different from removing any other node — there is no "previous" node whose `next` pointer needs rewriting; instead `head` itself must move forward, and `tail` may also need resetting if the list becomes empty. Since `deleteFront()` already solves this correctly, `deleteValue()` delegates to it rather than duplicating that logic, keeping the "shrink from the front" edge case defined in exactly one place.