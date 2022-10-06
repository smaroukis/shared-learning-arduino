// Adapted from Elegoo Mega2560 Starter Kit Lesson 5  
// Pressing pushbutton switches light on and off
// added debounce and timing to the tmi02 case
// using Blink Without Delay techniques for debouncing

// Inputs
int LED = 9;
int BUTTON = 7;

// Others
byte state;
byte old_state;
byte led_state = 0;

void setup(){
  pinMode(LED, OUTPUT);
  pinMode(BUTTON, INPUT_PULLUP);  // pullup = normal HIGH or 5V   
}

void loop(){
  old_state = state; // save the previous state
  state = digitalRead(BUTTON);

  if ((state != old_state)){ // if the button is being pressed
    // debounce 
    delay(20); 

    if (state != old_state){ // if still being pressed
      if (led_state == 0){
          digitalWrite(LED, HIGH);
          led_state = 1;
      } else {
        digitalWrite(LED, LOW);
        led_state = 0;
      }
        state = 1 - state; // switch the pushbutton state
    }
    
  }
}
