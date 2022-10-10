parent:: [Intro to Arduino - Software](Intro%20to%20Arduino%20-%20Software.md)
previous::
next:: [Arduino Case Statements](Arduino%20Case%20Statements.md)

- initialize pin number variables as `const int` (e.g. `const int analogInPin = A0;`)
- for number variables that can get large, such as when using `millis()`, use `unsigned long` so it rolls over back to 0

`boolean`
	`true` or `false`

`char`
- a single character (i.e. one letter or number)
- occupies one byte of memory

`int`
- -32,768 to 32,767
- occupies 2 bytes 

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

`string`
- set of ASCII characters 
- uses 1 byte for each character in the string plus a null character (1 byte) at the end

`array`
- list of variables 
- example `int light[6] = {0, 20, 50, 75, 100};`




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