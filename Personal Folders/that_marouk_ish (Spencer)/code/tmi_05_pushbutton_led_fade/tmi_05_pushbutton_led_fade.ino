// from Massimo - Getting Started with Arduino

// Constants
const int LED = 13;
const int BUTTON = 7; 

// Inputs
int val = 0;

// Other
int old_val = 0; // stores previous value of "val" (input)
int state = 0; // 0 = LED off and 1 = LED on
int brightness = 128; // out of 255 (1 byte for analogWrite())
unsigned long t_start = 0; // unsigned long is 0 to ~4.2 million

void setup(){
  pinMode(LED, OUTPUT); // do we need this for the built in one? 
  pinMode(BUTTON, INPUT);
}

void loop(){
  
  val = digitalREAD(BUTTON);

  //check for a button press (tranisition LOW->HIGH)
  if ((val == HIGH) && (old_val == LOW)){
    state = 1 - state; // change the state from ON to OFF or vice-versa
    t_start = millis(); record time
    delay(10); // for debouncing
  }

  // check if the button is being held down
  if ((val == 
}
