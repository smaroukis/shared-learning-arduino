> source: https://mypractic.com/lesson-7-classes-in-c-language-for-arduino-button-as-an-object/

Goal: 

```cpp
#define LED_PIN 13 // the LED is connected to pin 13
#define BUTTON_PIN 12 // button is connected to pin 12

// Description of the button signal processing class
class Button {
  public:
    boolean flagPress; // flag - the button is pressed
    boolean flagClick; // flag - the button was clicked
    void scanState(); // method for checking the signal state
    void setPinTime(byte pin, byte timeButton); // method of setting the pin number and time (number) of state acknowledgments
  private:
    byte _buttonCount; // counter of button state acknowledgments
    byte _timeButton; // time of button state acknowledgments
    byte _pin; // pin number
};

boolean ledState; // LED state variable

Button button1; // create a Button object named button1

void setup() {
  pinMode(LED_PIN, OUTPUT); // set pin 13 (LED) as output
  button1.setPinTime (BUTTON_PIN, 15); // call the method for setting the   button1 object with the parameters: pin number 12, the number of acknowledgments 15
}

// an infinite loop with a period of 2 ms
void loop () {

  button1.scanState(); // call the method of scanning the button signal

  // LED control unit
  if ( button1.flagClick == true ) {
    // there was a click of a button
    button1.flagClick = false; // reset the click flag
    ledState = ! ledState; // inversion of the LED state
    digitalWrite(LED_PIN, ledState); // output the LED status
  }

  delay(2); // 2 ms delay
}

// method for checking the status of the button
// flagPress = true - pressed
// flagPress = false - free
// flagClick = true - was clicked
void Button::scanState() {
// requires: 
// modifies: 
	// _buttonCount acknowledgement counter
	// _timeButton timer
	// flagPress
	// flagClick

  if (flagPress == (! digitalRead (_pin)) ) {
  // signal state remains the same
    _buttonCount = 0; // reset counter of acknowledgments
  }
  else {
    // signal state changed
    _buttonCount++; // +1 to the acknowledg counter

    if ( _buttonCount >= _timeButton ) {
      // signal state did not change for the specified time
      // the signal state became stable
      flagPress = ! flagPress; // inversion of the state sign
      _buttonCount = 0; // reset the counter of acknowledgments

      if ( flagPress == true ) flagClick = true; // sign of click
    }
  }
}

// method of setting the output number and time of acknowledgments
void Button::setPinTime(byte pin, byte timeButton) {
  _pin = pin;
  _timeButton = timeButton;
  pinMode(_pin, INPUT_PULLUP); // set pin as input
}
```