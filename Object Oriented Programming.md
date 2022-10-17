parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)

[Example - A Basic OOP Class for Multitasking](Example%20-%20A%20Basic%20OOP%20Class%20for%20Multitasking.md)

Single leading underscores are usually used for defining _internal_ or _private_ attributes of a class, they shouldn't need to be accessed from outside the class. Commonly they are used for internal calculations done by that classes member functions.

**Inheritance**
```cpp
class Rectangle: public Shape {
   public:
      int getArea() { 
         return (width * height); 
      }
};
```

**Resources**
- on extending classes in C++
	- arduino example: https://forum.arduino.cc/t/class-inheritance-and-polyphormism/93778/3
	- https://www.tutorialspoint.com/cplusplus/cpp_inheritance.htm