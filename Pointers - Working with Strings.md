parent::[[Pointers]]

Pointers are often used to create strings. You'll commonly see 

```cpp
const char* ptr = "Some literal string";
```

Here we have created a _mutable_ pointer to an _immutable_ character. The address held by the pointer is not the whole address of the string, but rather just the address of the first char, which takes up 1 byte. (see [[Arduino Variable Types]]). We can then increment the pointer (address) to access the next char in the string.

![[Personal Folders/that_marouk_ish/attachments/IMG_7672.jpeg]]

The syntax can get tricky depending on where the asterisk and `const` key word is:

![[Personal Folders/that_marouk_ish/attachments/Pasted image 20221021121626.png]]

### Examples
- Used in [[Personal Folders/that_marouk_ish/tmi 16 Object Oriented Programming]] to `Serial.print()` from within a custom class.