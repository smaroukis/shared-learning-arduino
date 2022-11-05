parent::[[Arduino Variable Types]]

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
