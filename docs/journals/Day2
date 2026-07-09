Date: 08/07/2026

Today I completed the Hash Map Design Proposal. While writing it I realized that designing a generic Hash Map is much 
more complicated than Dynamic Array or Linked List because the biggest problem is not storing the data but generating 
a correct hash value for every possible data type.

At first I thought I could simply hash the address of the object, but after thinking about it I realized two different 
objects can store exactly the same value while having different addresses. If the address is used as the hash, both 
objects will produce different hash values even though they represent the same key.

Then I thought about hashing the raw bytes of the object. This also has several problems. Objects like std::string 
and std::vector store pointers to heap memory internally. Even if two strings contain the same text, their internal 
pointers are different, so hashing the bytes would still produce different hash values. I also learned that structure
 padding and changing member variables can make hashing raw memory unreliable.

This made me realize that a generic library cannot automatically decide which member of a user-defined object
 should be used to generate the hash. The user knows their object better than the library.

After reading about STL I found that std::unordered_map solves this by allowing the user to provide a hash function 
for custom types. I also realized that user-defined keys should provide operator== because after two keys fall
 into the same bucket the Hash Map still needs a way to check whether they are actually equal.

I have not finalized the implementation yet because I am still learning about function objects (functors) and 
template specialization. I want to understand how the STL implements hashing before I start writing the code.