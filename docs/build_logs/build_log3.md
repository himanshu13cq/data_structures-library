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
The assignment operator would return a reference to the object it is done by returning *this,this here is pointer to the object and *this is used for returning the reference.It is done because of assignment chaining like a = b = c
b = c will assign b to c,but it does not return anything therefore a will assigned void which will cause error therefore 

