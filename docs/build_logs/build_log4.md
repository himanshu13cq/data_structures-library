# Build Log

## Date: 10/07/2026

### Session - 1

### Work Completed
-Built the HashMap skeleton: constructor, destructor, and createNode/destroyNode-style helpers
-Constructor allocates the bucket array with malloc and placement-news each bucket as an empty LinkedList
-Verified the empty skeleton compiles and constructs/destructs cleanly before adding any real logic

### Problems Faced
Unlike DynamicArray, HashMap can't start with _capacity = 0, since every lookup does hash(key) % _capacity and dividing by zero is undefined behavior.

### Solution
Start the constructor at a fixed initial capacity (8) instead of growing lazily from zero, so the bucket array always has at least one valid bucket to hash into.

---

## Date: 10/07/2026

### Session - 2

### Work Completed
-Implemented hash() using if constexpr to branch on the Key type at compile time
-Supported int (direct cast to size_t) and std::string (base-31 polynomial rolling hash)
-Added a static_assert for any other Key type, with a clear error message

### Problems Faced
A plain runtime if wouldn't work here — the string-hashing branch (looping over characters) doesn't even compile for a Key like int, since int can't be iterated over.

### Solution
if constexpr discards the untaken branch entirely at compile time per instantiation, so only the branch matching the actual Key type is ever compiled. Also learned why size_t (unsigned) is required instead of int for hash values: a signed overflow can wrap negative, and negative % capacity can produce a negative array index — size_t makes that impossible.

---

## Date: 10/07/2026

### Session - 3

### Work Completed
-Implemented insert(), using a private find() helper to check for an existing key and update it in place, or append a new KV pair otherwise
-Implemented rehash(): doubles capacity and re-hashes every existing entry into the new bucket array once load factor exceeds 0.9
-Extended LinkedList to support this: added find() (replacing the old bool-only search()), deleteValue(), and a nested Iterator class supporting range-based for loops

### Problems Faced
LinkedList's old search() could only answer true/false — it couldn't hand back a way to update the matching element. rehash() also needed to visit every element in a bucket's chain from outside the LinkedList class, without exposing raw Node pointers.

### Solution
find() returns T* instead of bool, so a caller gets both a found/not-found answer and a mutable pointer to update the value in place if needed (nullptr represents "not found," avoiding the need for an exception in a simple internal helper). For traversal, added a minimal Iterator (only *, ++, and != operators — the minimum required for range-based for) rather than exposing getHead(), so external code can visit every element without being able to corrupt the list's internal pointers.

Also hit the same class of bug twice: writing a member function definition (find, later deleteValue) without the LinkedList<T>:: / HashMap<K,V>:: scope qualifier. Without it, the compiler treats it as an unrelated free function with no access to the class's private members at all — a good reminder to double check every out-of-line template definition has its scope qualifier before debugging anything deeper.

---

## Date: 10/07/2026

### Session - 4

### Work Completed
-Implemented get(), contains(), and remove() on top of find()
-Implemented deleteValue() in LinkedList using a two-pointer (prev/curr) walk, reusing deleteFront() for the head-removal case
-Implemented HashMap's copy constructor and copy assignment operator (Rule of Four), which required first implementing LinkedList's own copy constructor (previously declared but never defined)
-Added size() and isEmpty()

### Problems Faced
get() needed a decision on missing-key behavior. Also, HashMap's deep copy depends entirely on LinkedList's copy constructor actually existing and being correct — discovered it had only ever been declared, never defined.

### Solution
Chose operator[]-style semantics for get(): a missing key gets inserted with a default-constructed value and a reference to it is returned, rather than throwing. This differs from the original design proposal, which assumed exception-on-missing-key — noted as an intentional deviation in the v2 design doc. For the copy constructor, wrote LinkedList's version using the same "reset to empty, then insertBack every element from the source" pattern already used in its operator=, then built HashMap's own copy constructor/operator= on top of it — each bucket is placement-new'd directly using LinkedList's copy constructor, giving a true deep copy of every chain.