parent::[Preprocessing Directives](Preprocessing%20Directives.md)

`#define` is a [Preprocessing Directives](Preprocessing%20Directives.md) often used to define constants, to avoid storing them in program memory (stored in limited flash memory). The compiler will check and replace these at compile time.

For example, if we use `#define ledPin 13`, any reference to `ledPin` will be replaced with the number 13 at compile time. 

A `const` is stored in program memory and is generally preferred for defining constants

Drawbacks
- the `#define` doesn't specify a type, so we can't get typedef errors (errors thrown when using variable types incorrectly)
- if we use the variable name (`ledPin` above) anywhere else in the code, it is replaced with `13` at compile time - this could conflict with other variables for long lines of code

> [!CAUTION] Use very specific variable names for `#define <variable_name> <value>` to avoid having other variables overwritten


- macro/`#define`.  is a pre-processor directive - this gets more into [C - Programming](C%20-%20Programming.md) 
	- e.g. `#define var 80000L` vs `#define var 80000`  ([source](https://forum.arduino.cc/t/when-to-use-const-int-int-or-define/668071/6?u=that_marouk_ish))

**Answered Questions**
- #q/answered where is the `#macro #define LED_BUILTIN 13` coming from? 
	- it is like a const but defined in a macro (preprocessing directive) by Arduino - it comes from C++
- #q/answered when should we use a `#define` macro or a `const int`? 
	- tl;dr: if you know what you are doing you can use `#define` for e.g. pin numbers, otherwise just use `const` when starting out
	- since `#define`s won't tell you whether you are using a variable wrong (doesn't give type errors), it is usually better to use `const`  especially just starting out
	- it does not use any program memory - the compiler will replace references to the constant with the value at compile time
	- if a constant name that is `#define`d is included in any other variable name, it will overwrite that variable name with the value as defined


## References
- https://www.arduino.cc/reference/en/language/structure/further-syntax/define/
- https://www.arduino.cc/reference/en/language/variables/variable-scope-qualifiers/const/