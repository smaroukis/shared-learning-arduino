parent::[[Arduino Variable Types]]
sibling::[[const int vs define macro]]

Integer Constants - e.g. `const int`
- are usually type `int` (unsigned) but can be other variable types using specific formatting e.g. `const int 10000L` (constant long integer) or `const int 33u` (constant unsigned integer) or `const int 32767UL` (constant unsigned long integer)

Table of various types:
![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221005161457.png]]

- _U/L formatters (appends)_
	- `u|U`: to force the constant into an **unsigned** data format. Example: `33u`
	- `l|L`: to force the constant into a **long** data format. Example: `100000L`
	- `ul|UL`: to force the constant into an **unsigned** **long** constant. Example: `32767ul`

> If doing math with integers a**t least one of the values must be of type long**, either an integer constant followed by an L or a variable of type long, forcing it to be a long. See the [Integer Constants](https://www.arduino.cc/reference/en/language/variables/constants/integerconstants) page for details.