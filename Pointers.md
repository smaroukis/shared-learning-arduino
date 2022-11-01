parent::[[Arduino Software Concepts]]

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

`int* ptr = &val`
- if the `*` is on the left side, it creates a _pointer_
- this creates a pointer to the address of `val` which stores an `int` type

`int dereference = *ptr`: 
- if the `*` used on the right side of the equal sign it is a _dereference operator_
- this dereferences the pointer and returns the value stored at the address


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