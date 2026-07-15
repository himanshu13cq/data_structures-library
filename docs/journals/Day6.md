# Journal – 15/07/2026

First, I designed the RedisLite design proposal. For this, I learned what Redis is, how it works, and how I can implement a simplified version of it using my own data structure library. Making the design proposal helped me understand the overall architecture and the components I need to build before starting the implementation.

While working on the design, I also learned about some important C++ concepts that will be useful for implementing the hash table. I studied the difference between `reinterpret_cast` and `static_cast`. I learned that `reinterpret_cast` does not change the bits stored in memory; it only changes how those bits are interpreted. On the other hand, `static_cast` converts the value itself, so the bit representation may change.

After that, I learned about `size_t` and found that its size depends on the system. It is 32 bits on a 32-bit system and 64 bits on a 64-bit system. While designing the hashing function for `double`, I realized that a `double` occupies 64 bits, so I first convert it into a `uint64_t`. If this value is directly returned as a `size_t` on a 32-bit system, the upper 32 bits will be lost. To solve this, I added another helper function that folds the upper bits into the lower bits using the XOR operation whenever `sizeof(uint64_t)` and `sizeof(size_t)` are different. This makes the hash function portable across different systems.

Next, I integrated Google Test into my project. At first, I tried using CMake's `FetchContent`, but later I switched to `find_package(GTest REQUIRED)` with the system-installed GTest package because it was simpler for my setup. I also created a separate `unit_tests` executable, enabled CTest, and configured automatic test discovery.

Then, I started writing unit tests for `DynamicArray::insert()`. While writing these tests, I was confused about why `insert(size(), value)` is valid but `get(size())` is not. After thinking through some examples, I understood that `insert()` inserts before a position, so `size()` means inserting after the last element. However, `get()` and `operator[]` access existing elements only, so `size()` is outside the valid range.

To make these tests possible, I replaced all the `exit()` calls in both `DynamicArray` and `LinkedList` with `std::out_of_range` exceptions. This allowed me to use `EXPECT_THROW` in Google Test instead of terminating the entire test program.

In the second session, I expanded the DynamicArray test suite by writing tests for `append()`, `remove()`, `get()`, `operator[]`, the copy constructor, the assignment operator, and the size, capacity, and `isEmpty()` functions.

I also decided to write some tests using `std::string` instead of only testing with `int`. While doing this, I found a bug in the `insert()` function. The implementation was assigning to memory where no object had been constructed yet. This bug never appeared with `int`, but it caused a crash with `std::string`. I fixed the problem by constructing the new object first using placement `new` before shifting the existing elements. After fixing it, I kept the same test as a permanent regression test. I also noticed that `append()` and `insert()` contained duplicate resizing code, so I moved that logic into a single private `grow()` helper function.

In the last session, I completed the LinkedList test suite by writing tests for insertion, deletion, searching, iterators, the copy constructor, and the assignment operator.

While running the tests, I found that `LinkedList::insert()` did not check for negative indices. Calling `insert(-1, value)` inserted the value into the list instead of throwing an exception. I fixed the bounds check by validating both negative indices and indices greater than the list size.

I also found that my iterator only implemented `operator!=`, so comparing two iterators directly using `EXPECT_EQ` caused a compilation error. Instead of changing the tests, I added `operator==` to the iterator class.

Finally, I discovered that one of my own tests was incorrect because it expected an element to have its old value even after I had changed it. After correcting the test, I built Google Test directly from source and ran the complete test suite both normally. All **135 tests across 21 test files passed successfully**, and no memory errors or undefined behavior were reported.
