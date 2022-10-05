[Arduino](Arduino.md) #inbox

The Arduino's without an [ADCs - Analog Digital Converters](ADCs%20-%20Analog%20Digital%20Converters.md) output a PWM square-wave when using the `analogWrite()` function. This can be combined with an RC [Low Pass RC Filter](Low%20Pass%20RC%20Filter.md) to create a DC voltage (e.g. 1K and 100uF). 

Note often we need to convert between 8-bit and 16-bit sizes since `analogRead()` returns a value between 0 and 1023 but `analogWrite()` can only write between 0 and 255.

> note `map()` uses integer math - for decimal precision you will need to write your own

Example `map()` code:
```arduino
void loop() {
int val = analogRead(0);
val = map(val, 0, 1023, 0, 255);
analogWrite(9, val);
}
```
