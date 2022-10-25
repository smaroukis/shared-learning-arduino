garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md)
previous::[Example - Even Better OOP - Header Files](Example%20-%20Even%20Better%20OOP%20-%20Header%20Files.md)

> Source: https://paulmurraycbr.github.io/ArduinoTheOOWay.html

> Note: Comments are my own

**New Constructor Syntax**

Example - we want to initialize a "ClickQueue" object inside a "Headlamp" class:

The ClickQueue object constructor here just assigns `pin = attachTo`. 

```cpp
class ClickQueue {
	const byte pin;
	// other member vars excluded for conciseness

  public:
    ClickQueue(byte attachTo) :
      pin(attachTo) {
    }
};
```
Note we can also do this in two other ways (`this->pin = attachTo` or `pin = attachTo`), but the colon syntax used here since it has another feature:

>  The colon syntax for constructors allows you to initialize things inside the class *that themselves have constructors*
```cpp
class Headlamp {
    const byte powerOutPin;
	ClickQueue brightnessClicker; // this is another class, we can initialize it in the Headlamp constructor below
    int brightness;

  public:
	// public member variables
	boolean isOn;

	// constructor - note colon syntax
	// initialize a ClickQueue object with the brightnessOutAttach value
    Headlamp(byte powerOutAttach, byte brightnessOutAttach) :
      powerOutPin(powerOutAttach),
      brightnessClicker(brightnessOutAttach) // *** <-- HERE *** 
	      // we initialize the ClickQueue object with the pin passed in to the function call 
	      // note Headlamp itself does not have the brightnesss pin as a member variable
    {
    }

	// ... other member functions
};
```


**Enum State Syntax**
```cpp
enum State {
  NOT_CLICKING = 0,
  CLICK_DOWN = 1,
  CLICK_PAUSE = 2
} state;
```

**Passing an Object to a Controller with Pass by Reference**

For controllers we want to act on LEDs and other things. We can create a control class and pass the controllee (e.g. LED) class by reference - then we can use the controllee's public methods, as in the `Headlamp::brightnessClick()` below.

Note how we don't have to assign the pins to the headlamp - since we are passing a reference, those are taken care of when we create the headlamp in `Headlamp headlamp(PIN_1, PIN_2)`

All we have to do is tell the class that it can expect to have a reference to a `Headlamp` class, and that reference's name is lamp. Then we can just assign it in the constructor, and pass it along in the declaration - `HeadlampControlButton button(PIN_3, headlamp)`. 

```cpp
class HeadlampControlButton : Button {
	Headlamp& lamp; // lamp is a Headlamp reference (we will pass by reference in the constructor)

	public: 
		HeadlampControlButton(Headlamp& lampAttach) :
			lamp(lampAttach)
			{}

	protected: // this class is a derived class of Button, we overwrite the protected click functions
		void shortClick() {
			// short click
			lamp.brightnessClick(); // here we are accessing the Headlamp object
		}
};


// declarations
Headlamp headlamp(PIN_1, PIN_2);
HeadlampControlButton button(PIN_3, headlamp); 
```

### Full Code
#code

```cpp
class Runnable { // a class that just holds the setup() and loop() functions
// for the more specific classes
    static Runnable *headRunnable;
    Runnable *nextRunnable;

  public:
    Runnable() {
      nextRunnable = headRunnable;
      headRunnable = this;
    }

    virtual void setup() = 0;
    virtual void loop() = 0;

    static void setupAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        r->setup();
    }

    static void loopAll() {
      for (Runnable *r = headRunnable; r; r = r->nextRunnable)
        r->loop();
    }

};

Runnable *Runnable::headRunnable = NULL;

class ClickQueue: public Runnable {
// main state machine
// the loop() checks and increments the State value
// performs the digitalWrite on the passed pin
// a ClickQueue object is used by the Headlamp class to access the
// addClick() and addAClick() functions
// during e.g. a power toggle or cancel button press
    const byte pin;
    // make these slow for testing
    const unsigned CLICK_DOWN_MS = 250;
    const unsigned CLICK_TOTAL_MS = 1000;

    enum State {
      NOT_CLICKING = 0,
      CLICK_DOWN = 1,
      CLICK_PAUSE = 2
    } state;

    unsigned long clickStartMs;
    int pendingClicks;

  public:
    ClickQueue(byte attachTo) :
      pin(attachTo) {
    }

    void setup() {
      pinMode(pin, OUTPUT);
      state = NOT_CLICKING;
      pendingClicks = 0;
    }

    void loop() { 
      switch (state) { // always increment to the next state if condition is met
        case NOT_CLICKING:
          if (pendingClicks > 0) {
            pendingClicks --;
            digitalWrite(pin, HIGH);
            clickStartMs = millis();
            state = CLICK_DOWN;
          }
          break;
        case CLICK_DOWN:
          if (millis() - clickStartMs > CLICK_DOWN_MS) {
            digitalWrite(pin, LOW);
            state = CLICK_PAUSE;
          }
          break;
        case CLICK_PAUSE:
          if (millis() - clickStartMs > CLICK_TOTAL_MS) {
            state = NOT_CLICKING;
          }
          break;
      }
    }

    void addAClick() { // this allows us to add a click from other objects
      pendingClicks++;
    }

    void addClicks(int clicks) {
      pendingClicks += clicks;
    }

    void cancel() {
      pendingClicks = 0;
      digitalWrite(pin, LOW);
      state = NOT_CLICKING;
    }
};

class Headlamp: public Runnable {
// The Headlamp object writes to the power and brightness pins
// has an "isOn" state variable
// also increments brightness
// we use "composition" here and create a ClickQueue brightnessClicker inside
    const byte powerOutPin;
	ClickQueue brightnessClicker; // composition here
    int brightness;

  public:
    boolean isOn;

    Headlamp(byte powerOutAttach, byte brightnessOutAttach) :
      powerOutPin(powerOutAttach),
      brightnessClicker(brightnessOutAttach)
    {
    }

    void setup() {
      pinMode(powerOutPin, OUTPUT);
      isOn = false;
      digitalWrite(powerOutPin, LOW);
      brightness = 0;
    }

    void loop() {
    }

    void powerToggle() {
      if (isOn) {
        brightnessClicker.cancel();
        digitalWrite(powerOutPin, LOW); // the Headlamp object writes the pins
        isOn = false;
      }
      else {
        digitalWrite(powerOutPin, HIGH);
        delay(50);
        brightnessClicker.addClicks(brightness);
        isOn = true;
      }
    }

    void brightnessClick() {
      if (isOn) {
        brightnessClicker.addAClick();
        brightness = (brightness + 1 ) % 5;
      }
    }

} ;

class Button: public Runnable {
// this is our base Button class
// implements debounced short and long clicks
// an extended HeadlampControl class below will
// call the actual brightness and power objects to perform the actin
    const byte pin;
    int state;
    unsigned long buttonDownMs;

  protected:
    virtual void shortClick() = 0; // protected means an inherited class can use and overwrite this function; it is used in the the HeadlampControl class
    virtual void longClick() = 0;

  public:
    Button(byte attachTo) :
      pin(attachTo)
    {
    }


    void setup() {
      pinMode(pin, INPUT_PULLUP);
      state = HIGH;
    }

    void loop() {
      int prevState = state;
      state = digitalRead(pin);
      if (prevState == HIGH && state == LOW) {
        buttonDownMs = millis();
      }
      else if (prevState == LOW && state == HIGH) {
        if (millis() - buttonDownMs < 50) {
          // ignore this for debounce
        }
        else if (millis() - buttonDownMs < 250) {
          shortClick(); 
        }
        else  {
          longClick();
        }
      }
    }

};

class HeadlampControlButton: public Button {
    Headlamp &lamp; // lamp is a headlamp reference

  public:
    HeadlampControlButton(byte attachToPin, Headlamp &attachToHeadlamp) :
      Button(attachToPin),
      lamp(attachToHeadlamp) {
    }
  protected: // this class is a derived class of Button, we overwrite the protected click functions
    void shortClick() {
      // short click
      lamp.brightnessClick(); // composition: the 
    }

    void longClick() {
      // long click
      lamp.powerToggle();
    }
};

class Taillight: public Runnable {
    const byte brakeSensePin;
    const byte ledOutPin;
    Headlamp &headlamp;

  public:
    Taillight(byte attachToBrakeSense, Headlamp &attachToHeadlamp, byte attachToLedPin) :
      brakeSensePin(attachToBrakeSense),
      ledOutPin(attachToLedPin),
      headlamp(attachToHeadlamp) {
    }

    void setup() {
      pinMode(brakeSensePin, INPUT_PULLUP);
      pinMode(ledOutPin, OUTPUT);
      digitalWrite(ledOutPin, LOW);
    }

    void loop() {
      if (digitalRead(brakeSensePin) == LOW) {
        digitalWrite(ledOutPin, HIGH);
      }
      else if (!headlamp.isOn) {
        digitalWrite(ledOutPin, LOW);
      }
      else {
        digitalWrite(ledOutPin, (millis() & 0b1110000000) == 0 ? HIGH : LOW);
      }
    }
};

Headlamp headlamp(10, 11);
HeadlampControlButton button(7, headlamp); 
Taillight taillight(6, headlamp, 12);


void setup() {
  Runnable::setupAll();
}

void loop() {
  Runnable::loopAll();
}
```