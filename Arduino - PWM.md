parent::[Arduino Software Concepts](Arduino%20Software%20Concepts.md)

Pulse-width-modulation, or PWM, is a technique to create a quasi-analog voltage from the normal 0 or 5V that an Arduino can output. By outputting 5V, and then 0V, for a fixed duration and repeating this at regular intervals, the output functions like a voltage somewhere between 0 and 5V. 

The result depends on the component connected to the output, but for LEDs this results in brightness corresponding to the duty cycle of the PWM wave. 

![Pasted image 20221103213229](Personal%20Folders/that_marouk_ish/attachments/Pasted%20image%2020221103213229.png)
Source: https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm

The PWM-capable digital output pins can output a PWM square-wave when using the `analogWrite()` function. This can be combined with an RC [Low Pass RC Filter](Low%20Pass%20RC%20Filter.md) to create a DC voltage (e.g. 1K and 100uF) other than the normal 0 and 5V. 

Note often we need to convert between 8-bit and 16-bit sizes since `analogRead()` returns a value between 0 and 1023 but `analogWrite()` can only write between 0 and 255.
	
The easiest way is to just divide by 4 when writing e.g.: 
``` c
analogWrite(LED, analogRead(PIN)/4));
```

Another way is to use `map()`:
``` c
void loop() {
int val = analogRead(0);
val = map(val, 0, 1023, 0, 255);
analogWrite(9, val);
}
```

> Note `map()` uses integer math - for decimal precision you will need to write your own function

### Further
- Advanced PWM techniques in https://docs.arduino.cc/tutorials/generic/secrets-of-arduino-pwm