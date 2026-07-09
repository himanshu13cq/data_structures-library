# Build Log 1

## Date: 07/07/2026

### Session - 1

### Work Completed
- Created the GitHub repository **data_structures_library** for Project 1.
- Set up the project structure with `include`, `src`, `design_proposal` and `docs`.
- Started working on the **Dynamic Array Design Proposal**.
- Finalized the public API for the `DynamicArray` class.
- Documented all public methods with their purpose and functionality.
- Wrote the internal representation explaining `_size`, `_capacity` and `data`.

### Problems Faced
I was thinking about using `operator[]` overload to access elements of the array but there was also a `get()` function. I was unsure whether both functions were required or if one of them was enough.

### Solution
Both functions are going to be used. The `get()` function will be used for safe access while `operator[]` will provide array-like syntax and return a reference so that elements can also be modified.

---

## Date: 07/07/2026

### Session - 2

### Work Completed
- Completed the remaining sections of the **Dynamic Array Design Proposal**.
- Wrote the Rule of Three section.
- Completed the complexity analysis for all public methods.
- Wrote the design decisions explaining heap memory, template programming, contiguous memory and automatic resizing.
- Created the memory representation diagram for the Dynamic Array.
- Pushed the completed Design Proposal to the GitHub repository.

### Problems Faced
I spent time thinking about the resizing strategy of the dynamic array whether the capacity should increase by **1.5x**, **2x** or **2.5x** whenever the array becomes full.

### Solution
After comparing different resizing strategies, I decided to double the capacity whenever `size == capacity`. Doubling provides a good balance between memory usage and append performance and is also the most commonly used strategy for dynamic arrays.

---

## Date: 07/07/2026

### Session - 3

### Work Completed
- Started working on the **Linked List Design Proposal**.
- Finalized the public API for the `LinkedList` class.
- Added the Destructor, Copy Constructor and Assignment Operator following the Rule of Three.
- Designed the internal representation using `head`, `tail` and `_size`.
- Started writing the memory management section explaining the use of `malloc()`, placement new and `free()`.

### Problems Faced
Using templates with `malloc()` and `free()` will cause problems because `malloc()` does not call a constructor when a user-defined object like `std::string` is created. `malloc()` only allocates raw memory and does not create an actual object. Later when a value is assigned to that memory, the assignment operator assumes that a valid object already exists. Since the constructor was never called, the internal members remain uninitialized which can lead to undefined behaviour, heap corruption or invalid free errors.

### Solution
After understanding how object construction works, I decided to use **placement new** immediately after `malloc()` to construct the object in the allocated memory. Before freeing the memory, the destructor will be called explicitly and then `free()` will be used. This allows the linked list to safely store user-defined types like `std::string` while still satisfying the requirement of using `malloc()` and `free()`.