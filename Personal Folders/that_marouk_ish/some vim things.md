also see [Vim Cheatsheet](Vim%20Cheatsheet.md)

**Macros**
- record a macro with `q<key>` where we assign the macro to key `<key>`
- stop recording with `q`
- run the macro with `@<key>` (run `3` times with `3@<key>`)
- e.g. the following will insert a `.` on at the beginning of the next 3 lines
```
qa.jq3@a@@
```

**Regex**
- see http://vimregex.com/

**Quantifiers, Greedy**
- `*`: match 0 or more of the preceding characters, ranges or metacharacters
- `\+` match 1 or more
- `\=` match 0 or 1
- `\{n,m}` match n to m of the preceding characters
- `\{n}` exactly n times
- `\{,m}` at most m matches (from 0)
- `{n,}` at least n matches

**Quantifiers, Non Greedy**
- prepend with dash
- `\{-}` 0 or more, non greedy
- `\{-n,m}` one or more, non greedy

**Character Ranges**
- `[0123]` will match any of the numbers 0-3 inside the brackets, but only representing **one** character
- `[0-9]` will match any numbers between 0 and 9
- to include a dash in the range include it first `/[-0-9]`
- all metacharacters lose their meta meaning (except for `^` used at the beginning)
- `\.\s\+[a-z]` will match a period followed by one or more blanks and a lowercase word

**Backreferences**
- group with `\(` and `\)`
- then reference with `\1`, `\2`, etc. (counting from the left)
- `s:\(\w\+\)\(\s\+\)\(\w\+\):\3\2\1:`  will swap the first two words of the line
	- `\1` holds the first word (e.g. `\w\+`)
	- `\2` holds any number of spaces or tabs between the first and second word (`\s\+`)
	- `\3` holds the second word `\w\+`
- 