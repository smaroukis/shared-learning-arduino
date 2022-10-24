garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md)
previous::[Example - A Basic OOP Class for Multitasking](Example%20-%20A%20Basic%20OOP%20Class%20for%20Multitasking.md)

> Source: https://forum.arduino.cc/t/buttons-an-object-oriented-approach/279724/9

Note: Author comes from a C background so a heavy use of `uint8_t` instead of `byte`s, and `uint16_t` instead of `int`s is used here.

**Latching Button Requirements**

We have a `Button::wasPressed()` value that is set when the button **has been debounced and is pressed.**

Note, to make a "latch" we have to have a way to reset the latch. This is through the `Button::reset()` function.

#q  wont the `button1.wasPressed() -> digitalWrite()` code be executed for every loop - we don't really need to

```cpp
  if(button1.wasPressed()) {
    digitalWrite(pinLed1, HIGH);
    if(!startResetTime1) startResetTime1 = now;
    if(now - startResetTime1 > resetTime1) {
      startResetTime1 = 0;
      digitalWrite(pinLed1, LOW);
      button1.reset();
    }
  }
```

### Full Code

```cpp
/*
    An object oriented approach to a latched button
    Jan 2015, for the Arduino forum, by MattS-UK

    Compiled and tested on a Mega 2560 R3

    Do with it what you will.
*/

/*  
  Hardware wiring
  Required:  
   2 x momentary tac switch, normally open
   2 x Led
   2 x current limiting resistor ~220 Ohm to ~1K Ohm   
   1 x breadboard

  pin2 ->--/ ------->gnd
  pin3 ->--/ ------->gnd
  pin4 ->--/\/\/---->gnd
  pin5 ->--/\/\/---->gnd
*/


//Button classs, encapsulate the functionality of a latched button
class Button {
    protected:
        uint8_t _pin;                  //hardware pin number
        boolean _state;                //current pin state
        boolean _wasPressed;           //button latch
        uint16_t _startDebounce;       //start of debounce time
        
    public:
        uint16_t debounceMs;            //period before button latches
        
        Button(uint8_t pin);
        void poll(uint16_t now);                            //call periodically to refresh the button state
        boolean wasPressed(void) { return _wasPressed; }    //return the latch state
        void reset(void);                                   //reset the latch
};

//constructor
Button::Button(uint8_t pin) {
  _pin = pin;
  _state = false;
  _startDebounce = false;
  _wasPressed = false;
  
  debounceMs = 500;
  pinMode(_pin, INPUT_PULLUP);
}

//refresh the button state
void Button::poll(uint16_t now){
  
  //pullup resistors cause the 
  // button to be HIGH when open 
  // so we invert the hardware state
  _state = !digitalRead(_pin);
  
  //when the button state is false, reset the debounce time
  if(!_state){
    _startDebounce = 0;
  }
  else {
    //start debounce time
    if(!_startDebounce) {
      _startDebounce = now;
    }
    else {
      //latch the button if it is still pressed when the debounce time expires
      if(now - _startDebounce > debounceMs) {
        _wasPressed = true;
      }    
    }
  } 
}

//reset the button
void Button::reset(void) {
  _wasPressed = false;
  _startDebounce = 0;
}


const uint8_t pinButton1 = 2;
const uint8_t pinButton2 = 3;
const uint8_t pinLed1 = 4;
const uint8_t pinLed2 = 5;

Button button1(pinButton1);
Button button2(pinButton2);

void setup(void) {
  
  pinMode(pinLed1, OUTPUT);
  pinMode(pinLed2, OUTPUT);
  
  button1.debounceMs = 1000;  //set the button1 latch to 1 second
  button2.debounceMs = 2000;  //set the button2 latch to 2 seconds
}

uint16_t resetTime1 = 5000;    //led1 will latch for 5 seconds
uint16_t resetTime2 = 10000;   //led2 will latch for 10 seconds
uint16_t startResetTime1 = 0;  //we need a counter for led1
uint16_t startResetTime2 = 0;  //we need a counter for led2 

void loop(void) {
  uint16_t now = millis();
  button1.poll(now);        //refresh button1
  button2.poll(now);        //refresh button2


  if(button1.wasPressed()) {
    digitalWrite(pinLed1, HIGH);
    if(!startResetTime1) startResetTime1 = now;
    if(now - startResetTime1 > resetTime1) {
      startResetTime1 = 0;
      digitalWrite(pinLed1, LOW);
      button1.reset();
    }
  }
  
  if(button2.wasPressed()) {
    digitalWrite(pinLed2, HIGH);
    if(!startResetTime2) startResetTime2 = now;
    if(now - startResetTime2 > resetTime2) {
      startResetTime2 = 0;
      digitalWrite(pinLed2, LOW);
      button2.reset();
    }
  }
}
```