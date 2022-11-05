parent::[[Arduino Software Concepts]]

We can use the `static` keyword to create "local" variables that are visible to only one function but **that persist beyond the function call**. This is helpful for storing indexes or counters used by helper functions without having to pass the counter back and forth between scopes. (see arduino.cc "random walk" function example)

```c
void helperFunction() {
	static int thisFunctionIndex; // only available to this function, but value persists between calls to this function
}
```
