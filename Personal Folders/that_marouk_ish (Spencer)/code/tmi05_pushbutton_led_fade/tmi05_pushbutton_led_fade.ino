// from Massimo - Getting Started with Arduino

// Constants
const int LED = 9;
const int BUTTON = 7; 

// Inputs
int val = 0;

// Other
int old_val = 0; // stores previous value of "val" (input)
int state = 0; // 0 = LED off and 1 = LED on
int brightness = 128; // out of 255 (1 byte for analogWrite())
unsigned long t_start = 0; // unsigned long is 0 to ~4.2 million

void setup(){
  pinMode(LED, OUTPUT); 
  pinMode(BUTTON, INPUT);
}

void loop(){
  
  val = digitalRead(BUTTON);

  //check for a button press (tranisition LOW->HIGH)
  if ((val == HIGH) && (old_val == LOW)){
    state = 1 - state; // change the state from ON to OFF or vice-versa
    t_start = millis(); // record time
    delay(10); // for debouncing
  }

  // check if the button is being held down
  if ((state == 1) && (millis() - t_start > 500)){
    brightness++;
    delay(20); // otherwise the brightness shoots up too quickly

    if (brightness > 255){
      brightness = 0; // reset to zero if over the analogWrite() max val of 255
      // further: could map unsigned int values to 0, 255 and not have to reset
    }
  }

  old_val = val; // don't forget to store the old value for the next loop

  if (state == 1) {
    analogWrite(LED, brightness); // turn LED ON at the brightness level
  } else {
    analogWrite(LED, 0); // turn LED OFF
  }
}
