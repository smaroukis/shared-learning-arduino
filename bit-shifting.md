parent::[Bitwise Operations](Bitwise%20Operations.md)
also see:: [Arduino Boolean and Arithmetic](Arduino%20Boolean%20and%20Arithmetic.md)

Bit shifting uses the bit shift operator `>>` (right shift) or `<<` (left shift), to shift all the bits in a variable left or right, which is a way to do [binary arithmetic](binary%20arithmetic.md).

This requires us to understand how the number is represented in memory. 

Because of binary arithmetic, the left operand is multiplied by 2 to the power of the right operand. 

For example
```cpp
int a = 5;      // binary: 0000000000000101
int b = a << 3; // binary: 0000000000101000, 5*2^3 or 40 in decimal
```

From https://www.arduino.cc/reference/en/language/structure/bitwise-operators/bitshiftleft/:
> The following example can be used to print out the value of a received byte to the serial monitor, using the left shift operator to move along the byte from bottom(LSB) to top (MSB), and print out its Binary value:

```cpp
// Prints out Binary value (1 or 0) of byte
void printOut1(int c) {
  for (int bits = 7; bits > -1; bits--) {
    // Compare bits 7-0 in byte
    if (c & (1 << bits)) {
      Serial.print("1");
    }
    else {
      Serial.print("0");
    }
  }
}
```

### References
- https://www.arduino.cc/reference/en/language/structure/bitwise-operators/bitshiftleft/
