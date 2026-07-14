# Build Log 5

## Date: 13/07/2026

### Session - 1

### Work Completed

* Added a third template parameter to `HashMap` (`HashMap<Key, Value, Hasher = DefaultHash<Key>>`) so users can provide their own hash function for custom key types.
* Moved the hashing logic for `int` and `std::string` from `HashMap::hash()` into a separate `DefaultHash<Key>` class.
* Tested the HashMap with a custom key type (`HashMap<Employee, int, EmployeeHasher>`) and verified that insertion, updating, collision handling, and rehashing all worked correctly.

### Problems Faced

After adding the third template parameter (`H`), I forgot to update a few member function definitions. The copy constructor, copy assignment operator, and `remove()` still used the old template declaration with only `K` and `V`, so the compiler didn't recognize `H`.

### Solution

Added `typename H` to the missing `template<>` declarations. This reminded me that whenever I change a class's template parameters, I need to update every member function definition as well, not just the class declaration.

---

## Date: 13/07/2026

### Session - 2

### Work Completed

* Added support for hashing `double` values by hashing their actual bit representation instead of converting them to integers.
* Compared different ways of hashing floating-point numbers and learned why directly casting them to `size_t` is not a good idea.
* Explored different ways to support user-defined key types.

### Problems Faced

I wanted the HashMap to work with any key type without forcing the user to always write a custom hash function.

### Solution

I decided to use hash-by-address as a fallback for unsupported types. This allows the HashMap to work, but two different objects with the same data will still hash differently unless the user provides a proper custom hasher.

I also added a compile-time check to make sure the key type supports `operator==`. Since I used a `requires` expression for this, I upgraded the project from C++17 to C++20.

---

## Date: 13/07/2026

### Session - 3

### Work Completed

* Found and fixed a bug in `DynamicArray::append()`.
* Changed `append()` and the resize logic to use placement `new` instead of assigning into unconstructed memory.
* Replaced the manually managed bucket array in `HashMap` with `DA<LinkedList<KV<Key, Value>>>`.
* Simplified the HashMap constructor, destructor, copy constructor, copy assignment operator, and `rehash()` because `DynamicArray` now manages the bucket memory.

### Problems Faced

The bug in `DynamicArray` didn't appear when storing simple types like `int`, but it showed up when storing `LinkedList` objects. The code was assigning to memory before the object had been constructed, which caused crashes.

While refactoring `HashMap`, I also accidentally destroyed the same `LinkedList` objects twice. `rehash()` manually called the destructor, but `DynamicArray::operator=` was already destroying those objects during assignment.

I also made a template syntax mistake by forgetting a closing `>` in a nested template declaration, which produced confusing compiler errors.

### Solution

Fixed `append()` by constructing new objects directly with placement `new` instead of assigning into raw memory. After the fix, storing `LinkedList` objects inside `DynamicArray` worked correctly.

Removed the manual destructor calls from `rehash()` and let `DynamicArray` manage object destruction on its own. This avoided calling the destructor twice and made the code cleaner.

For the template syntax error, I carefully checked the matching angle brackets and corrected the missing `>`. This reminded me to slow down and verify nested template declarations whenever they become more complex.
