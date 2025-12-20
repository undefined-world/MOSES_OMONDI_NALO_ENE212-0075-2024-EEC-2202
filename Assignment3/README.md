TASK1:

1.Difference between a normal variable and a pointer.


A normal variable stores an actual data value directly in a memory location, and its memory is accessed directly using the variable name, whereas a pointer stores the memory address of another variable rather than the value itself. A normal variable’s value is read and modified by directly using its name in expressions or assignments, on the other hand, a pointer accesses memory indirectly by first referencing the stored address and then using dereferencing (*) to read or modify the value at that address. Whereas assigning a new value to a normal variable changes only its own stored data, modifying a dereferenced pointer changes the value of the variable it points to, thereby allowing indirect access and manipulation of memory.


2. How variable declaration and definition defers from pointer declaration and definition.

Variable declaration and definition involve specifying a data type and creating a memory location to store a value, for example int x; declares and defines an integer variable, and x = 5; assigns it a value, whereas pointer declaration and definition involve specifying a data type together with the * operator to create a variable that can store the address of another variable, for example int *p; declares a pointer to an integer and p = &x; defines it by assigning it the address of x. The * operator in a declaration indicates that the variable is a pointer, while in expressions it is used to dereference the pointer and access or modify the value stored at the referenced address, on the other hand the & operator is used to obtain the memory address of a variable so that it can be stored in a pointer.

3. Meaning of dereferencing a pointer.

Dereferencing a pointer means using the * operator to access the value stored at the memory address held by the pointer. When a pointer is dereferenced, the program goes to the referenced memory location and reads or modifies the data stored there. For example, if int x = 10; and int *p = &x;, the pointer p stores the address of x, and using *p accesses the value 10 stored at that address. If we then assign a new value using dereferencing, such as *p = 25;, the value at that memory address is changed, and as a result the variable x is also updated to 25.

4. Scenarios where pointers are preferred over normal variables.

Pointers are preferred over normal variables in situations where efficient memory use, indirect data access, or shared data manipulation is required. One common scenario is when a function is required to modify the value of a locally defined variable.Another practical use case is dynamic memory allocation, where pointers are necessary to access memory allocated at runtime using functions such as malloc, allowing programs to handle data structures like arrays, linked lists, and trees whose sizes are not known at compile time.

5. Limitations and risks associated with using pointers as compared to normal variables

Dangling pointers, which occur when a pointer references memory that has already been deallocated,may lead to unpredictable program behavior. Another limitation is the possibility of null or uninitialized pointers, which can cause program crashes if dereferenced. Unlike normal variables that are automatically managed and safer to use, pointers require careful handling to avoid memory leaks, especially when dynamically allocated memory is not properly freed. Additionally, pointer misuse can result in buffer overflows and memory corruption, making programs harder to debug and less secure compared to using normal variables that provide direct and controlled access to memory.

6. A comparison between call by value and call by reference.

In call by value, a function receives a copy of the actual argument, meaning any changes made inside the function do not affect the original variable, whereas in call by reference, the function receives the address of the variable, allowing it to modify the original data directly

7.
    (a) Scenario where call by value is preferred.
        Call by value is ideal when a function only needs to read or use data without changing the original variable. It ensures the original variable remains safe from unintended modifications. For example, a function that calculates the square of a number or returns a computed result based on inputs without altering them.

    (b) Scenario where call by reference is preferred.

        Call by reference is preferred when a function needs to modify the original variable or when passing large data structures efficiently to save memory and processing time. Examples include swapping two numbers or modifying elements of an array
