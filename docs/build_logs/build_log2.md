# Build Log

## Date: 08/07/2026

### Session - 1

### Work Completed
- Completed the linkedlist design proposal with memory diagram.
- Modify the dynamic array design proposal update the format,added objective,improve internal representation with new memory diagram and modify heading of design decisions
- Improve the memory diagram to explain automatic resizing
- Start working on hash map design proposal 
- Decide the public api for hashmap

### Problems Faced
While designing the Hash Map I realized that supporting template programming creates a problem for hashing user defined objects. For primitive data types like `int` and `char`, creating a hash value is straightforward, but for user defined classes there is no way to know which member should be used to generate the hash.

Initially I thought about hashing the address of the object, but two different objects can store exactly the same value while having different addresses. This would generate different hash values for the same key.

I then thought about hashing the raw bytes of the object. This also creates problems because objects like `std::string` or `std::vector` internally store pointers to heap memory. Two strings with the same text can have different heap addresses, so their raw bytes are different even though their values are equal. Structure padding can also contain different unused bytes, producing different hashes for identical objects. Some objects also contain mutable members like `_size`; if those values change after insertion, the generated hash would also change and the element could no longer be found.

### Solution
After studying this problem I decided that user defined objects should provide their own way of generating the hash. Primitive types will use the library's default hash implementation, but for custom classes the user should provide the hashing logic. I am currently exploring whether this should be done by asking the user to provide a hash function (functor) or by specializing a template similar to the STL. I am also studying explicit template specialization to understand which approach is better.

---

## Date: 09/07/2026

### Session - 2

### Work Completed
- Continued working on the Hash Map Design Proposal.
- Designed the internal representation using buckets and linked lists.
- Added the Rule of Three section.
- Wrote the memory management section.
- Completed the complexity analysis for all public methods.

### Problems Faced
Another issue I found was comparing user defined objects. While inserting a new key-value pair, if the same key already exists its value should be updated instead of creating another entry. For primitive types this comparison is simple, but for user defined objects the Hash Map cannot know when two objects should be considered equal.

### Solution
I decided that user defined key types should provide an overloaded `operator==` so the Hash Map can compare keys correctly. This operator will also be used while searching and deleting elements from the map.

---
## Date: 09/07/2026

### Session - 3

### Work Completed
- Completed the Hash Map Design Proposal.
- Added the design decisions explaining collision handling, rehashing and template programming.
- Reviewed all three Design Proposals to keep the documentation format consistent.


### Problems Faced
I was unsure whether the Hash Map should ask the user to provide a hash value directly or a hash function that generates the hash. I also wanted to understand how the STL solves this problem for custom types.

### Solution
I started studying functors, function objects and template specialization used by `std::unordered_map`. My current understanding is that providing a hash function is much more flexible than asking the user to provide a hash value because the hash is always generated whenever it is needed instead of storing it separately. I will continue researching this before starting the implementation.

## 