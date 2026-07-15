# Journal

**Date: 15/07/2026**

Today started with something I had already implemented weeks ago but never completely understood — the custom `Iterator` inside my `LinkedList`. Until now, I knew it worked, but I wanted to understand *why* it was written that way. While reading about iterators, I also came across a C++ template rule that had confused me before: writing `typename` before a nested type such as `LinkedList<T>::Iterator`. I learned that because `Iterator` depends on the template parameter `T`, the compiler cannot know during its first parsing phase whether `Iterator` is a type or something else. Writing `typename` removes that ambiguity by explicitly telling the compiler that it is a type. It was one of those language rules that looked strange at first but made sense once I understood how templates are compiled.

After that, I moved on to writing unit tests for the `HashMap`. While running the tests I became confused by GoogleTest's `TEST` and `TEST_F` macros. The test output grouped them separately, and for a while I thought the tests written using `TEST` were not executing at all. After reading the documentation more carefully, I realized that GoogleTest groups tests by test suite rather than by source file. Both kinds of tests were executing correctly; they simply appeared under different suite names.

Once the HashMap tests were complete, I started implementing Redis Lite. Since Redis Lite is built directly on top of my own `HashMap`, most of the work involved connecting user commands to the data structure rather than implementing new storage logic. I built the REPL, implemented command tokenization, added command dispatching, and then implemented the core commands (`SET`, `GET`, `DEL`, `EXISTS`, `COUNT`, and `CLEAR`).

While implementing the command handlers, I ran into a const-correctness problem. The handlers accepted `const DA<std::string>&`, but my `DynamicArray` only had a non-const version of `operator[]`. This led me to learn why containers usually provide two overloads of the same function: one for mutable objects and another for const objects. I added a const overload returning `const T&` and also learned what the `const` written after a member function declaration actually means. It doesn't make the function itself constant—it promises that calling the function will not modify the object's state. Understanding the difference between the two `const`s in `const T& operator[](int) const` finally made const correctness much clearer.

Another improvement came while implementing the `CLEAR` command. Redis Lite needed a way to remove every stored key-value pair, but my `HashMap` had no `clear()` function. Initially I considered writing the logic directly inside Redis Lite, but that would have violated the separation of responsibilities between the application and the data structure. Instead, I added `clear()` to `LinkedList`, reused it inside `HashMap::clear()`, and then had Redis Lite simply call `store.clear()`. This small change also simplified the `LinkedList` destructor by allowing it to reuse `clear()` instead of duplicating node deletion logic.

The rest of the day was spent on testing. I completed the Redis Lite test suite and then added regression tests for the newly introduced `clear()` functions in both `LinkedList` and `HashMap` to ensure the refactoring hadn't broken existing functionality.

At the end of today's work, the project contains **240 passing unit tests** across all components:

* DynamicArray — 71 tests
* LinkedList — 69 tests
* HashMap — 59 tests
* Redis Lite — 41 tests

