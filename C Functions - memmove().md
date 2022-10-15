parent::[C Functions](C%20Functions.md)

Description:
- Copies **n** characters from **str2** to **str1**, but for overlapping memory blocks, memmove() is a safer approach than memcpy().
Declaration:
```c
void *memmove(void *array_dest, const void *array_source, size_t n)
```
Parameters:
-   **array_dest** − This is a pointer to the destination array where the content is to be copied, type-casted to a pointer of type void*.
-   **array_source** − This is a pointer to the source of data to be copied, type-casted to a pointer of type void*.
-   **n** − This is the number of bytes to be copied.
Return Value:
- a pointer to the destination, which is `dest`