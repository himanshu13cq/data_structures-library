Build Log 1

Date: 06/07/2026
Duration - 4:30 - 6:30

Work Completed
Created the GitHub repository data_structure_library for project 1.
Set up the project structure with include, src, design_proposal and docs.
Completed the Design Proposal.
Designed the public API for the DynamicArray class.
Documented all public methods along with their purpose.
Wrote the design decisions explaining why heap memory, template programming, Rule of Three, automatic resizing and contiguous memory are used.
Completed the complexity analysis for all public methods.

Problems Faced
 I was thinking about using operator[] overload to access element of array but there was also get() function.I also spend time thinking about the resizing strategy of the dynamic array whether to increase the size by 1.5x,2x or 2.5x

Solution
Both functions operator[] and get() are going to be used.The get will be modified to give only the constant reference so that using it don't modify the element at index i.The operator will return the reference and using it access with modification is also possible it will give feel of using array.
For resizing the array when size becomes equal capacity the doubling the capacity would be better choice it is most commonly used and provide a balance between memory space and append time.

Date: 07/07/2026
Duration: 9:30 - 11:30

Work Completed
Push the design_proposal along with memory_diagram for dynamic array into Github repo

Problems Faced
Using template with malloc and free will cause problem as malloc do not call a contructor when a user defined object like string is created.malloc() only allocates raw memory and does not create an actual object.Later when a value is assigned to that memory, the assignment operator would assume that a valid object already exists.Since the constructor was never called, the internal member of heap remain unintialized which can lead to undefined behaviour.



