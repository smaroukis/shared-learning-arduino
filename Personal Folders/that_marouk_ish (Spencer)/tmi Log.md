> Reverse chronological log of my learnings on Arduino

More Raw in [tmi Lab Notes](tmi%20Lab%20Notes.md)

[2022-10-03](2022-10-03)
Nothing today except some reading about `millis()` vs `delay()` - basically just get comfortable with `millis()` since it allows you to do multiple things at (perceivable) the same time (see Notepad)

[2022-10-02](2022-10-02) - Day 1 - Unboxing  - a Mega?? and Blink

I thought I had ordered an (unofficial) Uno starter kit but when I opened it I found a Mega inside. Honestly I wanted an Uno, since I'm sure many tutorials are built off that, and if I want to use an Uno later I'll have to check and change the pin numbers in the code. 

 So I learned besides the main differences (more pins, more PWM, more storage, ATMega2560 vs 328P), another one is that the Mega has a USB to Serial driver chip built in, where-as the Uno's ATMEGA328P needs an external ATMega 16U2 USB-to-Serial converter. 

Well, then, after that rabbit hole I did follow the instructions to get it to blink the led, and changed it from 1s to 0.5s. Also changed the variable `LED_BUILTIN` to `13` to verify that is the correct LED pin for the Mega. 


[[2022-10-01]]
Started this Vault with [Arduino](Arduino.md). Learned that [Arduino - PWM](Arduino%20-%20PWM.md) outputs a square wave, specific values (steps) are determined by the ADC converter - [Uno](Uno.md) is 10 bit (so $2^{10}=1024$ steps). More advanced Arduinos have ADCs with higher resolution, but must use the `analogReadResolution()` function to set this. 

Also learned that `analogRead()` and `analogWrite()` functions have different bounds ( 0 to 1023 and 0 to 255 respectively).