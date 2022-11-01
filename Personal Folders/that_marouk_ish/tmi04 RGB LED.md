parent::[[tmi Examples]]
previous:: [[tmi03 Digital Inputs Debounce w Millis]]
next:: [[tmi05 Pushbutton LED Fade]]
level:: #beginner

>  Elegoo Ultimate Starter Kit Project 4

Desired Goal:
- By using three different PWM outputs, one for each LED color, we can make almost any color by varying the intensity of each channel (the colors are "combined" by being close in space to each other)

Concepts:
- [[../../RGB LEDs]] - forward drop of each color is different; by mixing colors with PWM we can make any color
- [[../../Arduino - PWM]]

Physical Setup:
![[attachments/img04-RGB-led.JPG]]


Code:


``` c
//adapted from www.elegoo.com for Mega 2560 Starter Kit

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

Improvements:
- find the optimal resistor for each LED based on its individual analog characteristics
