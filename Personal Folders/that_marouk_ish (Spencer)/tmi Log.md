> Reverse chronological log of my learnings on Arduino

[2022-10-02](2022-10-02)
Uploaded this vault to Github. 



[[2022-10-01]]
Started this Vault with [Arduino](Arduino.md). Learned that [Arduino - PWM](Arduino%20-%20PWM.md) outputs a square wave, specific values (steps) are determined by the ADC converter - [[Uno]] is 10 bit (so $2^{10}=1024$ steps). More advanced Arduinos have ADCs with higher resolution, but must use the `analogReadResolution()` function to set this. 

Also learned that `analogRead()` and `analogWrite()` functions have different bounds ( 0 to 1023 and 0 to 255 respectively).