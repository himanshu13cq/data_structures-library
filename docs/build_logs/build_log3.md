# Build Log

## Date: 09/07/2026

### Session - 1

### Work Completed
-Started Implementation of dynamic array
-learn about mulitfile projects and header gaurds
-learn about cmake
-in array implementation add the rule of three and append method implement about resizing logic
-implement []operator overload 

### Problems Faced
Confusion about what would =operator overload will return,why it have a return type of class object rather than void,
What would be the return type for []operator overload it will be return type T or return T&.

### Solution
The assignment operator would return a reference to the object, it is done by returning *this,this here is pointer to the object and *this is used for returning the reference.We do this because of assignment chaining like a = b = c,
b = c will assign b to c,but it does not return anything therefore 'a' will be assigned void which will cause error therefore assignment operator return the reference of the class object which is begin assigned.


## Date: 09/07/2026

### Session - 2

### Work Completed
-Completed the full implementation of dynamic array
-Started the implementation of linked list 


### Problems Faced
I faces difficulties on how to strucutre file as in header file .h,if use generic programming then I need to write the defination also inside the .h file.
There is confusion about linked list, there is two structure first is node and second is linked list the linked list will store node,the node will contain the data which is of type T so we need to have both linked list and node work on generic programming and how the constructor of T will be called,in linked list i am going to call the constructor of node 

### Solution
I learned to move all template function definitions into a **`.tpp`** file and include that file at the end of the corresponding header file. This keeps the implementation separate while allowing the compiler to see the template definitions.
For node creation, I construct the `Node<T>` object using **placement new** after allocating memory with `malloc()`. Since `Node` contains a member of type `T`, constructing the node automatically constructs the `T` object as well.

---

## Date: 09/07/2026

### Session - 3

### Work Completed
-Completed the implementation of Linked list
-Structure file using CMake
-Make file structure change in both dynamic array and linked list implementation


### Problems Faced
I faces problem with insertion, how to insert a node if both head and tail are null.
In deletion where to move the tail pointer if there is one node only to delete 

### Solution
Learn properly about how to implement insertion at front, back and at any index.For deletion also if there is only single node than i need to set tail to null ptr.
