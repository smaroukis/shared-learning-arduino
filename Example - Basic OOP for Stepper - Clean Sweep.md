garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md)
previous::[Example - A Basic OOP Class for Multitasking](Example%20-%20A%20Basic%20OOP%20Class%20for%20Multitasking.md)
next::[Example - Arduino Timer Interrupts](Example%20-%20Arduino%20Timer%20Interrupts.md)
#code

> Source: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-clean-sweep

Description
- each LED is a `Flasher` object
- each Servo is a `Sweeper` object
- we handle the button press in the main `loop()` (this could also be a class)

Drawbacks
- no debounce (a `Button` class would be useful)

```cpp
#include <Servo.h> 


class Flasher
{
	// Class Member Variables
	// These are initialized at startup
	int ledPin;      // the number of the LED pin
	long OnTime;     // milliseconds of on-time
	long OffTime;    // milliseconds of off-time

	// These maintain the current state
	int ledState;             		// ledState used to set the LED
	unsigned long previousMillis;  	// will store last time LED was updated

  // Constructor - creates a Flasher 
  // and initializes the member variables and state
  public:
  Flasher(int pin, long on, long off)
  {
	ledPin = pin;
	pinMode(ledPin, OUTPUT);     
	  
	OnTime = on;
	OffTime = off;
	
	ledState = LOW; 
	previousMillis = 0;
  }

  void Update()
  {
    // check to see if it's time to change the state of the LED
    unsigned long currentMillis = millis();
     
    if((ledState == HIGH) && (currentMillis - previousMillis >= OnTime))
    {
    	ledState = LOW;  // Turn it off
      previousMillis = currentMillis;  // Remember the time
      digitalWrite(ledPin, ledState);  // Update the actual LED
    }
    else if ((ledState == LOW) && (currentMillis - previousMillis >= OffTime))
    {
      ledState = HIGH;  // turn it on
      previousMillis = currentMillis;   // Remember the time
      digitalWrite(ledPin, ledState);	  // Update the actual LED
    }
  }
};

class Sweeper
{
  Servo servo;              // the servo
  int pos;              // current servo position 
  int increment;        // increment to move for each interval
  int  updateInterval;      // interval between updates
  unsigned long lastUpdate; // last update of position

public: 
  Sweeper(int interval)
  {
    updateInterval = interval;
    increment = 1;
  }
  
  void Attach(int pin)
  {
    servo.attach(pin);
  }
  
  void Detach()
  {
    servo.detach();
  }
  
  void Update()
  {
    if((millis() - lastUpdate) > updateInterval)  // time to update
    {
      lastUpdate = millis();
      pos += increment;
      servo.write(pos);
      Serial.println(pos);
      if ((pos >= 180) || (pos <= 0)) // end of sweep
      {
        // reverse direction
        increment = -increment;
      }
    }
  }
};
 
 
Flasher led1(11, 123, 400);
Flasher led2(12, 350, 350);
Flasher led3(13, 200, 222);

Sweeper sweeper1(15);
Sweeper sweeper2(25);
 
void setup() 
{ 
  Serial.begin(9600);
  pinMode(2, INPUT_PULLUP); 
  sweeper1.Attach(9);
  sweeper2.Attach(10);
} 
 
 
void loop() 
{ 
  sweeper1.Update();
  
  if(digitalRead(2) == HIGH)
  {
     sweeper2.Update();
     led1.Update();
  }
  
  led2.Update();
  led3.Update();
}
```
