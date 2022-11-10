parent::[tmi Examples](tmi%20Examples.md)
previous:: [tmi06 LDR analogWrite to LED](tmi06%20LDR%20analogWrite%20to%20LED.md)
next:: [tmi08 Micro Servo](tmi08%20Micro%20Servo.md)
garden-topic:: [Buzzers - Active and Passive](../../Buzzers%20-%20Active%20and%20Passive.md)
level:: #beginner

> Inspired by www.elegoo.com Mega Ultimate Kit Lesson 7 and https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

Desired Goal:
- Play a sound on active and passive buzzer elements.
- 3 different code are included in the same file, the first (07A) simply plays an active buzzer every time the pushbutton is pressed. The second (07B) also uses the active buzzer but uses a `delay()` to vary the frequency, thus tone, of the buzzer. The third (07C) switches the active buzzer out for a passive buzzer and uses the `tone()` function included by Arduino to play a tone on the passive buzzer (it implements the frequency modulation behind the scenes, which is needed for the passive buzzer). 

Concepts:
- [Buzzers - Active and Passive](../../Buzzers%20-%20Active%20and%20Passive.md)
- PWM vs frequency modulation
- Including C Header Code (e.g. `pitches.h` for defining musical notes)

Physical Setup:

> We are using 16Ohm magnetic buzzers from the elegoo Mega Ultimate Starter Kit

07A - Active Buzzer
![img07-setup](tmi%20attachments/img07-setup.JPG)

07C - Passive Buzzer
- same physical setup as above (note we can use a digital pin even though we are doing _frequency modulation_, as opposed to _PWM_, per the `tone()` function included in the Arduino library)

Code:
- note there are 3 examples, two for the active buzzer and one for the passive buzzer (using the `tone()` function and a `.h` C header file that must be included at the same level of the code). 

``` c
// Globals
int BUZZER = 3;//the pin of the Active Buzzer
int BUTTON = 6; // pushbutton
int buttonState = 0; // unpressed

// ----------------------
// 07A - Simple Active Buzzer
// ----------------------


void setup(){
  pinMode(BUZZER, OUTPUT); // digital output (DC HIGH/LOW) since it is an active buzzer
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop(){
  // read the button state
  buttonState = !digitalRead(BUTTON); // due to pullup (unpressed = 5V), logic is reversed

  // if button is pressed, set the buzzer HIGH (DC)
  if (buttonState == 1){
    digitalWrite(BUZZER, HIGH);
  } else {
    digitalWrite(BUZZER, LOW);
  }

  delay(20); // give it some time
}


// ----------------------
// 07B - Active Buzzer w Modulation
// ----------------------
// from www.elegoo.com Lesson 7
// note this code loops, to stop just unplug from GND

void setup()
{
 pinMode(BUZZER,OUTPUT);//initialize the BUZZER pin as an output
}
void loop()
{
 unsigned char i;
 while(1)
 {
   //output a frequency
   for(i=0;i<80;i++)
   {
    digitalWrite(BUZZER,HIGH);
    delay(1);//wait for 1ms
    digitalWrite(BUZZER,LOW);
    delay(1);//wait for 1ms
    }
    //output another frequency
     for(i=0;i<100;i++)
      {
        digitalWrite(BUZZER,HIGH);
        delay(2);//wait for 2ms
        digitalWrite(BUZZER,LOW);
        delay(2);//wait for 2ms
      }
  }
} 

// ----------------------
// 07C - Passive Buzzer
// ----------------------
// from www.elegoo.com Mega Ultimate Kit Lesson 7
//  and https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

#include "pitches.h" // needed for passive buzzer
 
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};

// the tone() library allows us to output a 
// square wave on ANY pin  
int BUZZER_PASSIVE = 3; 
 
void setup() {
 
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    //  output the voice, every scale is 0.5 sencond
    tone(BUZZER_PASSIVE, melody[thisNote], 500);
  
    // Output the voice after several minutes
    delay(1000);
  }

  noTone(BUZZER_PASSIVE);
}

void loop() {  
  // no need to play it more than once
} 
```

Improvements:
- see https://itp.nyu.edu/physcomp/labs/labs-arduino-digital-and-analog/tone-output-using-an-arduino/ for ideas

Resources
- See the "References" section of the [Buzzers - Active and Passive](../../Buzzers%20-%20Active%20and%20Passive.md) page
- https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody - built in `tone()` example
- https://itp.nyu.edu/physcomp/labs/labs-arduino-digital-and-analog/tone-output-using-an-arduino/ - more on `tone()` and music theory