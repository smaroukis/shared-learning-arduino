> Reverse chronological log of my learnings on Arduino

More Raw in [tmi Lab Notes](tmi%20Lab%20Notes.md)

[[2022-10-04]] Day 2 - Party Time - RGB LEDs 
So today I was onto the first interesting project that I learned more than I expected from. Mostly on the analog side.

First, it is relatively simple.
The RGB LED is three seperate LEDs with a common node, and we can make "any" llight color by varying the intensities of each channel - the LEDs are close enough in space that we see the combination as a singular color. The intensity of each channel is varied by PWM. 

But then I thought I could  just use one resistor on the cathode instead of three separate resistors on the anodes. I quickly learned that due to the difference in forward voltage for the different colors, this wouldn't work. Basically, the red LED will turn on before the others. Also, the total current will change based on how intense each channel shines, so the light will change intensity based on the color, which we don't want. 

Here is the code, for my fellow n00bs: 

```
//adapted from www.elegoo.com 
// note pins are for Mega 2560; for UNO PWM pins may be different

// Define Pins
const int BLUE = 6;
const int GREEN = 5;
const int RED = 3;

void setup(){
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

int redVal;
int greenVal;
int blueVal;

void loop(){
  const int tDelay = 10;

  redVal = 255;
  greenVal = 0;
  blueVal = 0;

// fade out red, bring green in
  for(int i = 0; i < 255; i += 1){
    redVal -= 1; // was set to 255 previously
    greenVal += 1; // 

    analogWrite(RED, redVal);
    analogWrite(GREEN, greenVal);
    delay(tDelay);
  } 

  redVal = 0;
  greenVal = 0;
  blueVal = 255;

// fade out blue, bring in blue
  for(int i = 0; i < 255; i += 1){
    greenVal -= 1;
    blueVal += 1;
    analogWrite(GREEN, greenVal);
    analogWrite(BLUE, blueVal);
    delay(tDelay);
  }

  redVal = 0;
  greenVal = 0;
  blueVal =255;

  // fade out blue, bring red in
  for(int i = 0; i < 255; i += 1){
    analogWrite(BLUE, blueVal);
    analogWrite(RED, redVal);
    delay(tDelay);
  }

}
```

I changed elegoo's `define`s to `const int` - another thing I learned (define's are from the C language but const int is generally better for beginners)



[2022-10-03](2022-10-03)
Nothing today except some reading about `millis()` vs `delay()` - basically just get comfortable with `millis()` since it allows you to do multiple things at (perceivable) the same time (see Notepad)

[2022-10-02](2022-10-02) - Day 1 - Unboxing  - a Mega?? and Blink

I thought I had ordered an (unofficial) Uno starter kit but when I opened it I found a Mega inside. Honestly I wanted an Uno, since I'm sure many tutorials are built off that, and if I want to use an Uno later I'll have to check and change the pin numbers in the code. 

 So I learned besides the main differences (more pins, more PWM, more storage, ATMega2560 vs 328P), another one is that the Mega has a USB to Serial driver chip built in, where-as the Uno's ATMEGA328P needs an external ATMega 16U2 USB-to-Serial converter. 

Well, then, after that rabbit hole I did follow the instructions to get it to blink the led, and changed it from 1s to 0.5s. Also changed the variable `LED_BUILTIN` to `13` to verify that is the correct LED pin for the Mega. 


[[2022-10-01]]
Started this Vault with [Arduino](Arduino.md). Learned that [Arduino - PWM](Arduino%20-%20PWM.md) outputs a square wave, specific values (steps) are determined by the ADC converter - [Uno](Uno.md) is 10 bit (so $2^{10}=1024$ steps). More advanced Arduinos have ADCs with higher resolution, but must use the `analogReadResolution()` function to set this. 

Also learned that `analogRead()` and `analogWrite()` functions have different bounds ( 0 to 1023 and 0 to 255 respectively).