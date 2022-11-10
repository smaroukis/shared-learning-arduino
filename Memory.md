parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)

> If not mentioned, we are talking about AVR and Harvard Based memory structures, keep in mind that memory allocation differs in both architectures

## Memory Architectures

> The Harvard model turns out to be a good match for embedded applications and the Atmega 328 used in the Arduino UNO use a relatively pure Harvard architecture. Programs are stored in Flash memory and data is stored in SRAM.

## Types of Memory

3 types:
- Flash: non-volatile _program_ memory, manage at the block level
- SRAM: reserved space for global and static variables (volatile) - see more at [Read Access Memory (RAM)](Read%20Access%20Memory%20(RAM).md)
- EEPROM: more non-volatile memory, managed at the byte level

Flash (non-volatile)
- stores program and initializes data (used when uploading a program to the board)
- can't modify data in flash memory from executing your code
- to modify the data it must first be copied into SRAM
- finite lifetime 100,000 write cycles
- can only be modified at the block level (vs. EEPROM which can be managed at the byte level)

SRAM, Static Random Access Memory (volatile)
- is dynamic, changes as we enter and exit function calls (use the `freeMemory()` function as a way to see the change as the program runs)
- can be read and written from the executing program
- **Static Data**: a block of reserved space for global and static variables; if we initialize a variable with a value, the runtime system copies the initial value from Flash when the program starts
- **Heap**: for dynamically allocated data items, grows "up" from the top of the static data
- **Stack**: for local variables, interrupts and function calls, grows "down" from the top of the memory down toward the heap; each interrupt, function call, and local variable causes the stack to grow; space is reclaimed when functions return

> [!NOTE]- SRAM: Memory Diagram
> ![Pasted image 20221019124618](attachments/Pasted%20image%2020221019124618.png) ^[https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram]

EEPROM (non-volatile)
- like Flash it is non-volatile
- but it can be read and written from the executing program  :➡️knowledge of [Pointers](Pointers.md) is vital
- have to read byte-by-byte
- slower than SRAM
- finite lifetime around 100k _write_ cycles

From the table below we can see the Uno has only a measly 2kB of SRAM for the static and global variables.

> [!Example]- Example - Arduino Memory Amounts
> 
> ![Table - Arduino Memory Amounts](Table%20-%20Arduino%20Memory%20Amounts.md)


**Further**
- note that although the HEAP is dynamic, de-allocating space of previously used variables **does not necessarily cause the heap to shrink**, since if there is other dynamic data above it in the heap, the top of the heap will not move - leading to a [fragmented heap](fragmented%20heap.md). 
- strings are especially notorious memory hogs, see [Arduino Intermediate Memory Techniques](Arduino%20Intermediate%20Memory%20Techniques.md) for more


**References**
- https://docs.arduino.cc/learn/programming/memory-guide
- https://www.arnabkumardas.com/arduino-tutorial/avr-memory-architecture/
- https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram
