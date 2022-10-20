parent:: [Arduino Software Concepts](Arduino%20Software%20Concepts.md)
previous::
next:: [Arduino Case Statements](Arduino%20Case%20Statements.md)
see-also:: [Arduino Memory Specifics](Arduino%20Memory%20Specifics.md)

### Fundamental

- initialize pin number variables as `const int` (e.g. `const int analogInPin = A0;`)
- for number variables that can get large, such as when using `millis()`, use `unsigned long` so it rolls over back to 0

---

#refactor below better as a table e.g. https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram

`boolean`
	`true` or `false`

`char`
- a single character (i.e. one letter or number) - but for numbers between 0-255 use `byte` (see below)
- occupies at least one byte of memory
- encoded by the [ASCII chart](https://web.archive.org/web/20171028220458/https://www.arduino.cc/en/Reference/ASCIIchart) (note `A` starts at `65`) thus `'A' + 1` evaluates to `66` :➡️[Table - ASCII Values](Table%20-%20ASCII%20Values.md)
- chars are single quotes (vs double quotes for strings)

`byte`
- 0 to 255
- 8-bit (1 byte) unsigned number

`int`
- -32,768 to 32,767
- occupies 2 bytes 

> Beware of Integer Math: When we do math with integers the decimals are truncated.  To force to float-precison use trailing decimals, e.g. `137./19.`

`unsigned int`
- 0 to 65,535
- occupies 2 bytes 

`long`
- approx. -2 million to 2million
- occupies 4 bytes

> Note for doing math with integers at least one must be of type `long`

`unsigned long`
- approx. 0 to 4 million

`float`
- uses 4 bytes
- functions that use them also use a lot of memory
- use only when need decimal precision

`double`
- double precision floating point, max value of approx $1.797 \times 10^{308}$

`array`
- list of variables 
- example array of integers: `int light[5] = {0, 20, 50, 75, 100};`
- example array of chars: `int char[6] = "hello"` ➡️ last character is ASCII null character `'\0'`

> Note the length and memory size is defined by the type of variable in the array. An array of chars (see cstrings) will have a length of $N_{chars} + 1$ and each item takes up 1 byte. For an array of `int`s, each item takes up 2 bytes from the definition of an `int`. 

strings (C-formatted array of `char`s and Arduino `String`)
- there is no "string" variable type, although there is a `String` variable type (defined in the Arduino language, not from the C-language)
- a string, in the C-programming sense, is just an array of ASCII `char`s plus the null character (integer value of `0` or as a char `\0`)
- total size is $N_{characters} + 1$ :➡️ uses 1 byte for each character in the string **plus a null character** (1 byte) at the end
	- e.g. `string array[4] = "ABC"` is the same as `string array[] = "ABC"`  note the size is `4`
- (!) literal strings are repeat memory offenders - they take up space both in flash and SRAM ^[https://learn.adafruit.com/memories-of-an-arduino/optimizing-sram], so watch out for using to0 many `Serial.println("Some text"); ` :➡️ [Memory](Memory.md)

---

**References**
- https://www.reddit.com/r/arduino/comments/y2tv7s/comment/isbs6kw/?utm_source=share&utm_medium=web2x&context=3


---

### Examples

**Example - multidimensional arrays (2x2)**

To create a _m-rows_ by _n-columns_ array:
```c
const int m = 4;
const int n = 4;
// initialized a fixed-size 4x4 array
int arrayName[m][n] = { {0, 0, 0, 0}, {0, 0, 0, 0} };
// rows are grouped by inner braces
```
- Rows are grouped by inner braces.
- The syntax to access a value is `arrayName[rowIndex][colIndex]` (0-indexed).
- To have a dynamically sized array initialize with `arrayName[][] = `


---

### Intermediate - Scope and More

We can use the `static` keyword to create "local" variables that are visible to only one function but **that persist beyond the function call**. This is helpful for storing indexes or counters used by helper functions without having to pass the counter back and forth between scopes. (see arduino.cc "random walk" function example)

```c
void helperFunction() {
	static int thisFunctionIndex; // only available to this function, but value persists between calls to this function
}
```




**Resources**
-



---
verbose #refactor 

**Numbers**
- Integers: `int` and `long`
	- by default variables are _signed_. 
		- for _n-bits_ of storage there is $2^n$ values; this includes 0, and we take away one possible value from the positive side, so we are left with a $2^{n-1}$ signed values and a range of $\text{int} \in [-2^{n-1}, 2^{n-1} - 1]$ since we take away one on the positive side. 
		- e.g. for 16 bits (the [word size](word%20size) of Arduino) it is $2^{16}=65,536$ values. For both positive and negative we have $32,768$ but since we want to include 0 as a positive number the range is $-32,768$ to $32,767$.
	- `int`: from -16,384 to 16,383
		- `unsigned int`: 0 to 32,768
	- `long`: 
		- for large numbers; stores 32 bits (4 bytes), from -2,147,483,648 to 2,147,483,647 (default unsigned)
		- `unsigned long`  from 0 to 4,294,967,295
		- note: for doing math with integers **at least one of them must be of type `long`**

[Integer Constants](https://www.arduino.cc/reference/en/language/variables/constants/integerconstants/) - `const int`
- are usually type `int` (unsigned) but can be other variable types using specific formatting e.g. `const int 10000L` (constant long integer) or `const int 33u` (constant unsigned integer) or `const int 32767UL` (constant unsigned long integer)
- [const int vs define macro](const%20int%20vs%20define%20macro.md)

Table of various types:
![](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221005161457.png)

- _U/L formatters (appends)_
	- `u|U`: to force the constant into an **unsigned** data format. Example: `33u`
	- `l|L`: to force the constant into a **long** data format. Example: `100000L`
	- `ul|UL`: to force the constant into an **unsigned** **long** constant. Example: `32767ul`

> If doing math with integers a**t least one of the values must be of type long**, either an integer constant followed by an L or a variable of type long, forcing it to be a long. See the [Integer Constants](https://www.arduino.cc/reference/en/language/variables/constants/integerconstants) page for details.


[1]: for hexadecimal, `A-F` is case _independent_