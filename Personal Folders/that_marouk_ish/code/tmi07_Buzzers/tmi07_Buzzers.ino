// Globals
int BUZZER = 3;//the pin of the Active Buzzer
int BUTTON = 6; // pushbutton
int 


// 07A - Simple Active Buzzer
void setup(){
  pinMode(BUZZER, OUTPUT); // digital output (DC HIGH/LOW) since it is an active buzzer
  pinMode(BUTTON, INPUT_PULLUP);
}

void loop(){
  // read the button state

  // if button is pressed, play the piezo

  // else don't play the piezo

}


// ----------------------

//07B - Active Buzzer Modulation frmo www.elegoo.com Lesson 7
/* 
void setup()
{
 pinMode(BUZZER ,OUTPUT);//initialize the BUZZER pin as an output
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

/* 
Passive BUZZER Code Here


*/ 