# Design Proposal — Dynamic Array

**SuperCoders — Project 01: Collections Library**

---

# Objective

The main objective of this project is to build a reusable **Data Structure Library** containing **Dynamic Array, Linked List and Hash Map** completely from scratch without using STL containers inside the library. The implementation will use manually managed heap memory so that the working of each data structure can be understood at a low level. The project is mainly focused on understanding how memory is allocated and deallocated manually, how different data structures are implemented internally and the design decisions involved while building them. The library will also serve as the foundation for future projects like **Redis Lite** and other **SuperCoders** projects.

The objective of the **Dynamic Array** is to understand contiguous memory allocation, automatic resizing, template programming and manual memory management. It will also help in understanding how dynamic arrays grow at runtime, how amortized time complexity works and why the Rule of Three is required when managing heap memory.

---

# Section 1 — Public API

```cpp
template<typename T>
class DynamicArray
{
public:

    DynamicArray();

    ~DynamicArray();

    DynamicArray(const DynamicArray& other);

    DynamicArray& operator=(const DynamicArray& other);

    void append(const T& value);

    void insert(int index,const T& value);

    void remove(int index);

    const T& get(int index) const;

    T& operator[](int index);

    int size() const;

    int capacity() const;

    bool isEmpty() const;

private:

    void resize();
};
```

- `append()` inserts an element at the end of the array. If the array becomes full it automatically resizes before inserting the new element.

- `insert(index,value)` inserts an element at any valid index by shifting all the following elements one position to the right.

- `remove(index)` removes the element at the specified index and shifts all the remaining elements one position to the left.

- `get()` and `operator[]` are kept separate. `get()` is mainly used for reading an element while `operator[]` returns a reference so elements can also be modified using array syntax.

---

# Section 2 — Internal Representation

The Dynamic Array will be implemented using **template programming** so that it can store any type of data like **int, double, char, string or user defined classes**. The elements will be stored in **contiguous heap memory**, allowing constant time random access using an index.

The class will contain three private data members.

```cpp
T* data;
int _size;
int _capacity;
```

- **data** points to the first element stored in heap memory.
- **_size** stores the current number of elements in the array.
- **_capacity** stores the total allocated memory available before resizing is required.

![Dynamic Array Memory Layout](/design/memory_diagram/dynamic_array2.jpg)

### Memory Management (malloc/placement-new instead of new/delete)

The project requires using **malloc()** and **free()** instead of **new** and **delete**.

Memory for the array will first be allocated using **malloc()**. Since `malloc()` only allocates raw memory and does not call constructors, every element will be constructed using **placement new**.

Whenever the array is destroyed or resized, the destructor of every constructed object will be called manually before releasing the allocated memory using **free()**.

### Automatic Resizing

Whenever **_size** becomes equal to **_capacity**, a new memory block having double the previous capacity will be allocated.

All the elements from the previous array will be copied into the new array, the old objects will be destroyed, the previous memory block will be freed and finally the data pointer will point to the new memory block.

### Rule of Three

- **Destructor:** Destroys every constructed element and frees the allocated heap memory.

- **Copy Constructor:** Allocates a completely new memory block and copies every element from the source array. This performs a deep copy and avoids shallow copy.

- **Assignment Operator:** First frees the previously allocated memory and then performs a deep copy of the source object. Self assignment will also be checked before copying.

---

# Section 3 — Complexity Estimates

| Operation | Best Case | Average Case | Worst Case | Reason |
|------------|-----------|--------------|-------------|--------|
| Constructor | O(1) | O(1) | O(1) | Only initializes the member variables. |
| Destructor | O(n) | O(n) | O(n) | Every constructed element must be destroyed before freeing the memory. |
| Copy Constructor | O(n) | O(n) | O(n) | Every element is copied into a newly allocated memory block. |
| Assignment Operator | O(n) | O(n) | O(n) | Frees the old array and performs a deep copy of every element. |
| append() | O(1) | O(1) amortized | O(n) | Normally inserts at the end. During resizing every element must be copied into a larger array. |
| insert() | O(1) | O(n) | O(n) | Inserting at the end without resizing is constant time. Otherwise elements must be shifted. |
| remove() | O(1) | O(n) | O(n) | Removing the last element is constant time. Otherwise remaining elements are shifted left. |
| get() | O(1) | O(1) | O(1) | Direct indexing into contiguous memory. |
| operator[] | O(1) | O(1) | O(1) | Direct indexing into contiguous memory. |
| size() | O(1) | O(1) | O(1) | Returns the stored size variable. |
| capacity() | O(1) | O(1) | O(1) | Returns the stored capacity variable. |
| isEmpty() | O(1) | O(1) | O(1) | Checks whether `_size` is zero. |


---

# Section 4 — Design Decisions

## Using Heap Memory

The Dynamic Array uses heap memory because its size is not known at compile time. Heap memory allows the array to grow dynamically whenever more space is required.

---

## Automatic Resizing by Doubling Capacity

So in the append operation where the user is adding a new element at the end of the array, if the capacity is greater than the _size then there is no problem as there is space present in the allocated heap memory. But if _size becomes equal to the _capacity, then there is a need to resize the array. Resizing is done by allocating a new contiguous heap memory block with double the previous capacity. I have doubled the capacity because it provides a good balance between memory usage and performance. If the capacity is increased by a very small factor like 1.5x, resizing will happen more frequently, increasing the number of allocations and copy operations. On the other hand, increasing it by a very large factor like 2.5x will waste more heap memory because many allocated locations will remain unused. Therefore, doubling the capacity is the most commonly used strategy as it keeps the number of resize operations low while avoiding excessive memory wastage.

---

## Memory Management Using malloc() and Placement New

The implementation uses **malloc()**, **placement new** and **free()** because the project requires manual memory management. `malloc()` only allocates raw memory, therefore placement new is required to construct every object and destructors must be called manually before freeing the memory.

---

## Exception Handling

Functions like **get()** and **operator[]** will throw an **IndexOutOfBoundsException** whenever an invalid index is accessed. Returning sentinel values is not suitable because the Dynamic Array is implemented using templates and every data type does not have a common invalid value.

---

## Separate Read and Write Access

The functions **get()** and **operator[]** are kept separate. `get()` returns a constant reference for safe read-only access while `operator[]` returns a reference so elements can also be modified using array indexing.

---

## Following the Rule of Three

Since the Dynamic Array manages heap memory manually, it implements the **Destructor**, **Copy Constructor** and **Assignment Operator**. This ensures every object owns its own memory and prevents shallow copy, dangling pointers and double free.