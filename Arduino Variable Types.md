parent:: [Arduino Software Concepts](Arduino%20Software%20Concepts.md)
previous:: [Intro to Arduino - Software](Intro%20to%20Arduino%20-%20Software.md)
next:: [Arduino Case Statements](Arduino%20Case%20Statements.md)
see-also:: [Arduino Memory Specifics](Arduino%20Memory%20Specifics.md)

- initialize pin number variables as `const int` (e.g. `const int analogInPin = A0;`)
- for number variables that can get large, such as when using `millis()`, use `unsigned long` so it rolls over back to 0

- By default number variables are unsigned, thus when a number "overflows" (becomes bigger than the value that it can hold), it will turn negative
- for _n-bits_ of storage there is $2^n$ values; this includes 0, and we take away one possible value from the positive side, so we are left with a $2^{n-1}$ *signed* values and a range of $\text{int} \in [-2^{n-1}, 2^{n-1} - 1]$ since we take away one on the positive side. 
		- e.g. for 16 bits (the [word size](word%20size.md) of Arduino) it is $2^{16}=65,536$ values. For both positive and negative we have $32,768$ but since we want to include 0 as a positive number the range is $-32,768$ to $32,767$.

`boolean`
	`true` or `false`

`char`
- a single character (i.e. one letter or number) - but for numbers between 0-255 use `byte` or  (see below)
- occupies at least one byte of memory
- encoded by the [ASCII chart](https://web.archive.org/web/20171028220458/https://www.arduino.cc/en/Reference/ASCIIchart) (note `A` starts at `65`) thus `'A' + 1` evaluates to `66` :➡️[Table - ASCII Values](Table%20-%20ASCII%20Values.md)
- chars are single quotes (vs double quotes for strings)

`byte`
- 0 to 255
- 8-bit (1 byte) unsigned number
- preferred usage over an `unsigned char` which also encodes 0 to 255

`int`
- -32,768 to 32,767
- typ. occupies 2 bytes (Uno, Mega, Nano)
- aside: if the highest bit is "1" the number is interpreted as a negative number -> see [Counting - Hexadecimal Binary and Decimal](Counting%20-%20Hexadecimal%20Binary%20and%20Decimal.md)

> [!NOTE] Numbers (e.g. `int` and `long`) are by default _unsigned_

> [!CAUTION] Beware of Integer Math: When we do math with integers the decimals are truncated.  To force to float precision use trailing decimals, e.g. `137./19.`

> [!NOTE] For the syntax for declaring constant numbers, see [Integer Constants](Integer%20Constants.md)

`unsigned int`
- 0 to 65,535
- typ. occupies 2 bytes 

`word`
- typ. an unsigned number from 0 to 65535
- the range depends on the microprocessor (see [word size](word%20size.md)) - for Arduino the word size is 16

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

> [!CAUTION] Literal strings are repeat memory offenders - they take up space both in flash and SRAM (see [Memory](Memory.md))


**References**
- https://www.reddit.com/r/arduino/comments/y2tv7s/comment/isbs6kw/?utm_source=share&utm_medium=web2x&context=3
- 

---

### Intermediate - Scope and More

