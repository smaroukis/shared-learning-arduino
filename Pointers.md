parent::[[Arduino Software Concepts]]
previous::[[Scope]], [[Counting - Hexadecimal Binary and Decimal]]

Pointers are variables that instead of holding a character or number, hold an address in memory. This way they “point” to a place in memory - the catch is that the place in memory can function as normal, holding a character, integer or anything else. 

Whats the point? Pointers provide us a way to work with stored data by passing around the reference to the address, instead of having to copy the data between various scopes of the program.

Here are some use cases:
- access data from different scopes, e.g. "pass by reference"
- efficiently use memory
- point to the first character in a string (commonly: `const char* ptr = <address>`)

### Syntax 

#### Pointers - `*`

Declaration syntax: `<type> *<variable_name> = <address>`

`int *ptr = 0xFF;`
- creates a variable of type pointer named `ptr` that stores the `address of an `int` (e.g. 16 bits) - here the address is 0xFF` Note the pointer variable itself typically takes up a [[word size]] (2 bytes in Arduino) to store the address.

#inbox/writing 

`int `

`int dereference = *ptr`: 
- if the `*` used on the right side of the equal sign it is a _dereference operator_
- this dereferences the pointer and returns the value stored at the address

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

> [!EXAMPLE]- Example Code - Writing to EEPROM ^[https://learn.adafruit.com/memories-of-an-arduino/measuring-free-memory]
> ```cpp
> // ************************************************
> // Write floating point values to EEPROM
> // ************************************************
> void EEPROM_writeDouble(int address, double value)
> {
>    byte* p = (byte*)(void*)&value;
> // ************************************************
> // write floating point values to eeprom
> // ************************************************
> void eeprom_writedouble(int address, double value)
> {
>    byte* p = (byte*)(void*)&value;
>    for (int i = 0; i < sizeof(value); i++)
>    {
>       eeprom.write(address++, *p++);
>    }
> }
> 
> // ************************************************
> // read floating point values from eeprom
> // ************************************************
> double eeprom_readdouble(int address)
> {
>    double value = 0.0;
>    byte* p = (byte*)(void*)&value;
>    for (int i = 0; i < sizeof(value); i++)
>    {
>       *p++ = EEPROM.read(address++);
>    }
>    return value;
> }

More: 
![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221021121626.png]]