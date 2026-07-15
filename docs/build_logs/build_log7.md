# Build Log 7

## Date: 15/07/2026

### Session - 1

### Work Completed

- Spent some time understanding the custom `Iterator` that I had previously implemented inside `LinkedList`.
- Learned that an iterator is essentially a small wrapper around an internal pointer which provides a standard way to traverse a container.
- Read about why functions like `begin()` and `end()` require `typename` in their return type.

### Problems Faced

I was confused by this function declaration:

```cpp
typename LinkedList<T>::Iterator LinkedList<T>::begin() const
```

I understood that `Iterator` was a nested class inside `LinkedList`, but I couldn't understand why `typename` was required before it.

### Solution

The reason is something called **Dependent Name Resolution**. Since `LinkedList<T>::Iterator` depends on the template parameter `T`, the compiler cannot immediately know whether `Iterator` refers to a type or something else like a static member. By writing `typename`, we explicitly tell the compiler that `Iterator` is a type. Without it, the compiler assumes it isn't a type and produces an error.

---

## Date: 15/07/2026

### Session - 2

### Work Completed

- Started writing test cases for `HashMap`.
- Completed a total of **59** test cases covering insertion, searching, updating existing keys, deletion, collisions, rehashing, copy constructor, assignment operator, and edge cases.

### Problems Faced

While running the tests, I became confused by GoogleTest's `TEST` and `TEST_F`. Their output appeared under different groups, so I initially thought the tests written using `TEST` were not executing at all.

### Solution

After reading the GoogleTest documentation, I learned that tests are grouped by **test suite**, not by source file. `TEST` creates a normal test suite, while `TEST_F` creates tests using a fixture class. Both are executed normally; they simply appear in different sections of the test output.

---

## Date: 15/07/2026

### Session - 3

### Work Completed

- Started implementing Redis Lite.
- Built the REPL (Read-Evaluate-Print Loop).
- Implemented command parsing using a tokenizer.
- Added support for the following commands:
  - `SET`
  - `GET`
  - `DEL`
  - `EXISTS`
  - `COUNT`
  - `CLEAR`

### Problems Faced

While implementing the command handlers, I passed the tokens as `const DA<std::string>&`. However, my `DynamicArray` only had a non-const version of `operator[]`, so accessing an element from a const object resulted in a compilation error.
So this problem happen when I am writing handleset in this I am accessing tokens array [1],[2] element but the array passed to this handleset function is const and my []operator overload return T& means a reference which is not const so this is illegal in C++ I cannot do this therfore I overload this function again with now return type const T

### Solution

Added another overload of `operator[]`:

```cpp
const T& operator[](int index) const;
```

While fixing this, I also learned what the `const` written after a member function actually means. It tells the compiler that the function promises not to modify the object, allowing it to be called on const objects. I also learned why the returned value is `const T&` instead of `T&`—returning a non-const reference would allow modification of an object that is supposed to be constant.

---

## Date: 15/07/2026

### Session - 4

### Work Completed

- Added a reusable `clear()` function to `LinkedList`.
- Refactored the destructor to reuse `clear()`.
- Added `clear()` to `HashMap`.
- Completed the implementation of the `CLEAR` command in Redis Lite.

### Problems Faced

Redis Lite required a `CLEAR` command, but `HashMap` didn't have a `clear()` function. My first thought was to implement the clearing logic directly inside Redis Lite.

### Solution

Instead of duplicating the logic, I moved the responsibility to the correct layer. First I added `clear()` to `LinkedList`, then implemented `HashMap::clear()` by clearing every bucket, and finally Redis Lite simply calls `store.clear()`. This keeps each class responsible only for managing its own resources.Actually implementing it also improve the linkedlist design as well the destructor got simple the copy constructor and assignment become more simpler.

---

## Date: 15/07/2026

### Session - 5

### Work Completed

- Wrote unit tests for Redis Lite.
- Made the necessary member functions public so the test suite could access them.
- Added regression tests for the new `clear()` functionality in both `LinkedList` and `HashMap`.

### Outcome

The project currently contains:

| Component | Tests |
|----------|------:|
| DynamicArray | 71 |
| LinkedList | 69 |
| HashMap | 59 |
| Redis Lite | 41 |
| **Total** | **240** |

Final test results:

- **37 test suites**
- **240 unit tests**
- **240 passing**
