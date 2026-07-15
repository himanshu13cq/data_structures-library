# Build Log 6

## Date: 14/07/2026

### Session 1

#### Work Completed
- Prepared the initial RedisLite Design Proposal, outlining the planned architecture, core components, implementation strategy, and project roadmap before beginning development.
- Studied C++ casting mechanisms, differences between reinterpret_cast and static_cast
- Researched the platform-dependent nature of size_t, noting that it is typically 32 bits on 32-bit systems and 64 bits on 64-bit systems
- While designing the hashing function, observed that hashing a double would produces a 64-bit representation (uint64_t). Returning this value directly as size_t would silently truncate the upper 32 bits on 32-bit systems.
Implemented a portable solution by introducing an additional helper function that folds the discarded upper bits into the lower bits using an XOR operation whenever sizeof(uint64_t) != sizeof(size_t). On 64-bit systems this helper is skipped, while on 32-bit systems it preserves entropy instead of simply losing the upper half of the hash.
- Integrated Google Test (GTest) into the project using CMake.Initially explored the `FetchContent` approach before switching to `find_package(GTest REQUIRED)` with the system-installed `gtest-devel` package.
- Added a dedicated `unit_tests` executable target separate from the main application, along with `enable_testing()` and `gtest_discover_tests()` so that `ctest` can discover and execute each test individually.
- Created the first DynamicArray test suite for `insert()`, covering:
  - insertion at the beginning,
  - insertion in the middle,
  - insertion at the end,
  - insertion into an empty array,
  - insertion that triggers a resize,
  - negative index exception cases, and
  - past-end index exception cases.

#### Problems Faced
The Dynamic array function named insert() does not work when index is equal to m_size.I previously assumed that inserting at _size is going to be invalid but it is possible as we are inserting after the last existed element.

`insert(size(), value)` was expected to behave like an append operation.

Invalid operations were expected to throw exceptions instead of terminating the program with `exit()`.

Another point of confusion was understanding why `insert()` allows `index == size()` while `get()` and `operator[]` do not. Working through several indexing examples clarified the distinction:

- `insert(index, value)` inserts **before** the specified position, making `size()` a valid "one-past-the-end" insertion point.
- `get()` and `operator[]` access existing elements only, so `size()` is genuinely out of range.

#### Solution
Replaced every `exit()`-based error path in both `DynamicArray` and `LinkedList` with `std::out_of_range` exceptions.

Updated the bounds check in `DynamicArray::insert()` from:

```cpp
index >= m_size
```

to:

```cpp
index > m_size
```

allowing insertion at the end of the array.

This change was essential before introducing `EXPECT_THROW` tests, since `exit()` immediately terminates the test process and cannot be verified by Google Test.

---

## Date: 14/07/2026

### Session 2

#### Work Completed
Expanded the DynamicArray test suite to cover:

- `append()`
- `remove()`
- `get()`
- `operator[]`
- copy constructor
- assignment operator (`operator=`)
- `size()`
- `capacity()`
- `isEmpty()`

The tests were organized into separate files based on functionality, making the suite easier to maintain and extend.

Additionally, at least one `std::string`-based test was written for every major operation instead of relying solely on `int` test cases.

#### Problems Faced
A genuine bug was discovered in `insert()`'s element-shifting logic.

When the array already had spare capacity, the implementation assigned into `data[m_size]` before constructing an object in that memory location. This is undefined behavior because the memory exists but no object has been created yet.

The issue is effectively invisible when testing with primitive types such as `int`, where assigning into unconstructed memory appears to work. However, it causes crashes when storing non-trivial types like `std::string`, which require proper object construction.

This turned out to be the same underlying issue that had previously affected `append()`.

#### Solution
Modified `insert()` so that the newly opened slot is first created using placement `new`, copy-constructing it from its neighboring element before any assignment operations occur.

The fix was verified using a targeted test involving a `DynamicArray<std::string>` with:

- 3 elements,
- capacity 4,
- insertion without triggering reallocation.

This scenario consistently reproduced the crash before the fix and passed successfully afterward.

I added the  regression test (`InsertWithSlackCapacityDoesNotCrash`) to the suite to ensure this bug cannot silent return.

To reduce duplication and future maintenance effort, the shared capacity-growth logic from both `append()` and `insert()` was refactored into a single private `grow()` helper.

---

## Date: 14/07/2026

### Session 3

#### Work Completed
Completed a comprehensive LinkedList test suite covering:

- `insertFront()`
- `insertBack()`
- `insert(index)`
- `deleteFront()`
- `deleteAt()`
- `deleteValue()`
- `find()`
- Iterator functionality
- copy constructor
- assignment operator (`operator=`)

Executed the complete combined test suite for both `DynamicArray` and `LinkedList`, consisting of:

- **21 test files**
- **135 individual test cases**

#### Problems Faced
A bug was found in `LinkedList::insert()`.

The bounds check validated only:

```cpp
index > m_size
```

and failed to reject negative indices.

As a result, calling:

```cpp
insert(-1, value);
```

did not throw an exception. Instead, execution bypassed every guard clause and inserted the value near the beginning of the list, producing incorrect behavior without crashing.

A second issue appeared during testing when using:

```cpp
EXPECT_EQ(list.begin(), list.end());
```

Compilation failed because the custom `Iterator` implemented `operator!=` (sufficient for range-based `for` loops) but did not define `operator==`.

Finally, one test case (`CopyConstructorWithString`) contained a contradiction. After assigning:

```cpp
copy[0] = "Orange";
```

the test immediately expected:

```cpp
copy[0] == "Baingan";
```

making the test impossible to satisfy regardless of implementation correctness.

#### Solution
Updated `LinkedList::insert()` to validate:

```cpp
index < 0 || index > m_size
```

bringing its behavior into alignment with `DynamicArray::insert()`.

Implemented `Iterator::operator==` instead of merely modifying the test, ensuring direct iterator comparisons are fully supported throughout the codebase.

Corrected the faulty copy-constructor test so that:

- `copy[0]` is compared against the newly assigned value (`"Orange"`), and
- `copy[1]` is verified to retain its original value.


