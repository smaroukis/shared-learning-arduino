> Reverse chronological log of my learnings on Arduino

[2022-10-02](2022-10-02) - Day 1 - Unboxing  - a Mega?? and Blink

I thought I had ordered an (unofficial) Uno starter kit but when I opened it I found a Mega inside. Honestly I wanted an Uno, since I'm sure many tutorials are built off that, and if I want to use an Uno later I'll have to check and change the pin numbers in the code. 

 So I learned besides the main things (more pins, more PWM, more storage, ATMega2560 vs 328P), is that the Mega has a USB to Serial driver chip built in, where-as the ATMEGA328P needs an external ATMega 16U2 USB-to-Serial converter. 

Well, then, after forgetting to set my 


[[2022-10-01]]
Started this Vault with [Arduino](Arduino.md). Learned that [Arduino - PWM](Arduino%20-%20PWM.md) outputs a square wave, specific values (steps) are determined by the ADC converter - [[Uno]] is 10 bit (so $2^{10}=1024$ steps). More advanced Arduinos have ADCs with higher resolution, but must use the `analogReadResolution()` function to set this. 

Also learned that `analogRead()` and `analogWrite()` functions have different bounds ( 0 to 1023 and 0 to 255 respectively).