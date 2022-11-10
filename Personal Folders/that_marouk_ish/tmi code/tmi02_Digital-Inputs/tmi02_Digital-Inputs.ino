// Adapted from Elegoo Mega2560 Starter Kit Lesson 5  
// pushbutton switches are wired to ground and used in INPUT_PULLUP mode
// when pressed, it connects the input to GND (inverted logic)
// unlike pinMode(INPUT) a pull-down resistor isn't needed so it simplifies things
// c.f. tmi05 Pushbutton LED Fade where we need a pulldown resistor on the switch.

int LED = 9;
int BUTTON_A = 7;
int BUTTON_B = 6;

byte leds = 0;

void setup() 
{
  pinMode(LED, OUTPUT);
  pinMode(BUTTON_A, INPUT_PULLUP);  // pullup = normal HIGH or 5V   
  pinMode(BUTTON_B, INPUT_PULLUP);  // switches are connected to ground
}

void loop() 
{
  if (digitalRead(BUTTON_A) == LOW) // LOW = button press
  {
    digitalWrite(LED, HIGH);
  }
  if (digitalRead(BUTTON_B) == LOW)
  {
    digitalWrite(LED, LOW);
  }
}
