parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
previous::[Scope](Scope.md), [Counting - Hexadecimal Binary and Decimal](Counting%20-%20Hexadecimal%20Binary%20and%20Decimal.md)

### Introduction

Pointers are variables that instead of holding a character or number, hold an address in memory. This way they “point” to a place in memory - the catch is that the place in memory can function as normal, holding a character, integer or anything else. 

Whats the point? Pointers provide us a way to work with stored data by passing around the reference to the address, instead of having to copy the data between various scopes of the program.

Here are some use cases:
- access data from different scopes, e.g. "pass by reference"
- efficiently use memory
- point to the first character in a string (commonly: `const char* ptr)

### Syntax 

#### Pointers - `*`

Declaration syntax: `<type> *<variable_name> = <address>`

`int *ptr = 0xFF;`
- creates a variable of type pointer named `ptr` that stores the address of an `int` (e.g. 16 bits) - here the address is 0xFF Note the pointer variable itself typically takes up a [word size](word%20size.md) (2 bytes in Arduino) to store the address.
- in practice we don't explicitly set the address, but rather use the address of an already created variable (see below)

> [!CAUTION] `int *p` vs. `value = *p`
> - if the `*` used on the right side of the equal sign it is a _dereference operator_
> - this dereferences the pointer and returns the **value** stored at the address
> - In fact, anywhere the pointer is not being _declared_, the asterisk means "dereference" or "get the value at the address of the pointer"

Another important syntax is the ampersand operator (`&`), which is used on **"normal" variables** to get the address they are stored at.  We commonly use this to store the address of an already-created variable into the pointer.

> [!EXAMPLE]+ Example - Declare a Pointer and an Int, Change the Value of the Int Using the Pointer
> ```cpp
> int *p;       // declare a pointer to an int data type
> int i = 5;
> int result = 0;
> p = &i;       // now 'p' contains the address of 'i'
> result = *p;  // 'result' gets the value at the address pointed by 'p'
>               // i.e., it gets the value of 'i' which is 5
> ```
> Source: https://www.arduino.cc/reference/en/language/structure/pointer-access-operators/reference/

#### Reference Variable and Address Of - `&`
`int *ptr = &val`
- if the `*` is on the left side, it creates a _pointer_
- this creates a pointer to the address of `val` which stores an `int` type

`&porcupine_count`
 - `&` is the "address of operator"
- returns the address of the variable (hex)
- `std::cout << &porcupine_count << "\n";`

`int &sonny = songqiao`
- if the `&` operator is on the left side it creates a _reference variable_, which is an alias for another object
- read as "`sonny` is an **integer reference** initialized to `songqiao`"
- anything done to the reference also happens to the origianl (this is used in the Pass By Reference example)
- for a previously created `sonny` object, now `songqiao` points to the same address, thus now `sonny` and `songquiao` are inexplicably linked - updating one will update the other
- The main difference is that a pointer can be null, while a reference must point to a valid value.

> [!EXAMPLE]+ Example - Dereference a Pointer
> ```cpp
> int gum = 3;
> 
> // * on left side is a pointer
> int* pointer = &gum;
> 
> // * on right side is a dereference of that pointer
> int dereference = *pointer;
> ```

> [!EXAMPLE]+ **Example - Pass By Reference** ^[https://www.codecademy.com/learn/learn-c-plus-plus/modules/learn-cpp-references-and-pointers/cheatsheet]
> Passing by reference allows us to pass just the address, thus avoiding creating a copy in the heap.
> 
> ```cpp
> 
> void swap_num(int &i, int &j) {
> 
>   int temp = i;
>   i = j;
>   j = temp;
> 
> }
> ```

### More 
- [Pointers - Working with Strings](Pointers%20-%20Working%20with%20Strings.md)
- [Example - Writing to EEPROM](Example%20-%20Writing%20to%20EEPROM.md)