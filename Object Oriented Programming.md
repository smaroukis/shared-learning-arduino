parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)

[Example - A Basic OOP Class for Multitasking](Example%20-%20A%20Basic%20OOP%20Class%20for%20Multitasking.md)
[[Example - Even Better OOP - Header Files]]
[Example - Professional Grade OOP - Inheritance and Composition](Example%20-%20Professional%20Grade%20OOP%20-%20Inheritance%20and%20Composition.md)

## General Theory

**Use Private Member Variables**

Single leading underscores are usually used for defining _internal_ or _private_ attributes of a class, they shouldn't need to be accessed from outside the class. Commonly they are used for internal calculations done by that classes member functions.

> We can (and should) make our member variables private, since we use the relevant constructors to initialize them, and use a public accessor to get the values.^[https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/]

**Create Classes**

Base classes are useful when we have the same variables for multiple objects. In the Arduino case it would be like defining a Pushbutton. See [Example - Better OOP - Private Functions](Example%20-%20Better%20OOP%20-%20Private%20Functions.md)

**Inheritance - Extend Classes From a Base Class**

If we have some common variables and member functions but also want to define more specialized functions, we can extend a base class and add on new functions and member variables.

## Examples

**Class Definition Syntax**
```cpp
class Base {
	// member variables initalizer list
	int _foo; // leading underscore means "this is member variable"
	int _bar;

	public: // or `private:` 
		// constructor example 1
		Base(int foo, int bar) : 
			_foo(foo), 
			_bar(bar) {
			// other things for the initialization
			}
	
		// public member functions
}
```

Another way, alternate assignment syntax.. 
```cpp
class Base {
	int foo; // note change here to naming
	int bar;

	public: // or `private:` 
		// constructor example 2
		Base(int foo, int bar)  
			{
			this->foo = foo; // alternate assignment syntax
			this->bar = bar;
			}
	
		// public member functions
}
```

**Inheritance**
```cpp
class Rectangle: public Shape {
   public:
      int getArea() { 
         return (width * height); 
      }
};
```

**Inheritance - Modifying Base Class Member Variables**

> However, C++ prevents classes from initializing inherited member variables in the member initializer list of a constructor. In other words, the value of a member variable can only be set in a member initializer list of a constructor belonging to the same class as the variable.^[https://www.learncpp.com/cpp-tutorial/constructors-and-initialization-of-derived-classes/]

To correctly do this we can call and initialize the `Base` class within the `Derived` constructor

```cpp
class Derived: public Base
{
public:
    double m_cost {};

    Derived(double cost=0.0, int id=0)
        : Base{ id } // HERE <- Call Base(int) constructor with value id!
        , m_cost{ cost }
    {
    }

    double getCost() const { return m_cost; }
};
```

## Resources
- arduino forum example for a latching pushbutton, simple but powerful (goes over protected vs private, access functions, syntax ++) https://forum.arduino.cc/t/buttons-an-object-oriented-approach/279724/9 -> [Example - OOP for a Latching Pushbutton](Example%20-%20OOP%20for%20a%20Latching%20Pushbutton.md)
- on extending classes in C++
	- arduino example: https://forum.arduino.cc/t/class-inheritance-and-polyphormism/93778/3
	- https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm
- look at example libraries
	- https://forum.arduino.cc/t/best-practices-for-making-a-header-library/613209/3