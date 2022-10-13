parent::[C - Programming](C%20-%20Programming), [Arduino Software Concepts](Arduino%20Software%20Concepts.md)

Preprocessing directive keywords are preceded by `#`, common ones are:
- `#include`
- `#define`

For example, use the preprocessing directive `#include` to use a header file in your code.

``` src/main.c
#include "header.h" // file is in include/header.h

int main (void)
{
 ...
}
```

> Note header files will be first searched as defined by the c-preprocessor (first the current folder and then a standard list of preprocessing folders)


## Resources
- https://stackoverflow.com/questions/344317/where-does-gcc-look-for-c-and-c-header-files