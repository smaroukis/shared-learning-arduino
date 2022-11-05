parent::[C - Programming](C%20-%20Programming.md), [Arduino Software Concepts](Arduino%20Software%20Concepts.md)

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

> Note `#include <file.h>` directs the preprocessor to search the standard place for header files on your system, typ. `/usr/include`

> `#include "file.h" ` searches in order 1) the current directory 2) the directories named with -I options, if any, and 3) the /usr/include directory (or other standard header file locations?)


## Resources
- https://stackoverflow.com/questions/344317/where-does-gcc-look-for-c-and-c-header-files
- https://stackoverflow.com/questions/46975843/cannot-access-header-files-in-separate-folders
- https://docs.oracle.com/cd/E19205-01/819-5265/bjadq/index.html