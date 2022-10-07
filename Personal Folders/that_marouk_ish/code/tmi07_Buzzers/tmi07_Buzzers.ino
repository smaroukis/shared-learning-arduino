// Globals
int BUZZER = 3;//the pin of the Active Buzzer
int BUTTON = 6; // pushbutton
int buttonState = 0; // unpressed

// ----------------------
// 07A - Simple Active Buzzer
// ----------------------

/* 
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
*/

// ----------------------
// 07B - Active Buzzer w Modulation
// ----------------------
// from www.elegoo.com Lesson 7
// note this code loops, to stop just unplug from GND
/*
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
*/

// ----------------------
// 07C - Passive Buzzer
// ----------------------
// from www.elegoo.com Mega Ultimate Kit Lesson 7
//  and https://www.arduino.cc/en/Tutorial/BuiltInExamples/toneMelody

#include "pitches.h" // needed for passive buzzer
 
// notes in the melody:
int melody[] = {
  NOTE_C5, NOTE_D5, NOTE_E5, NOTE_F5, NOTE_G5, NOTE_A5, NOTE_B5, NOTE_C6};
int duration = 500;  // 500 miliseconds

// the tone() library allows us to output a 
// square wave on ANY pin even digital ones  
int BUZZER_PASSIVE = 3; 
 
void setup() {
 
  for (int thisNote = 0; thisNote < 8; thisNote++) {
    // pin8 output the voice, every scale is 0.5 sencond
    tone(8, melody[thisNote], duration);
  
    // Output the voice after several minutes
    delay(1000);
  }

  noTone(BUZZER_PASSIVE);

}
 
void loop() {  
  // no need to play it more than once
} 