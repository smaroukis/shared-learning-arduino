parent::[[Arduino Software Concepts]]

The compiler takes the Arduino code and turns it into assembly and loads it into the program memory, based on the type of microprocessor being used.

The important thing to note is how the compiler optimizes the memory storage and handles our variable types. 

This is one reason it is better to use `const int PIN = 13;` rather than `#define PIN 13` - the compiler will throw an error if we try to do something that we can't with an `int` in the first cast but not the second. :➡️[[Preprocessing Directives]]

Also we can see that although we may declare variables in a certain order, that does not mean they are placed in memory in that order - the compiler tries to optimize the placement of the variables. ➡️ [[Arduino Memory Specifics]]