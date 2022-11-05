parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)
previous:: [Arduino Variable Types](Arduino%20Variable%20Types.md)
next:: [Arduino Boolean and Arithmetic](Arduino%20Boolean%20and%20Arithmetic.md)

**If**
``` c 
if (val == 1) { 
	// do something; 
	}`
```

**For**
``` c
for (int i = 0; i < 10; i++) {
	// do someting;
}
```

**Switch Case**
``` c
switch (sensorValue) {
	case 23:
		// do something
		break;
	case 46:
		// do something
		break;
	default:
		// do something
}
```

**While**
``` c
while (condition) {
	// do something;
}
```

**Do While**
> The code is run before the condition is evaluated

``` c
do {
	// something;
} while (condition);
```

**Break/Continue**
`break;` breaks out of a `while` or `for` loop
`continue;` skips the rest of the code inside the loop and tests the condition again