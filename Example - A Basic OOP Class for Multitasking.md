garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md)
next:: [Example - Basic OOP for Stepper - Clean Sweep](Example%20-%20Basic%20OOP%20for%20Stepper%20-%20Clean%20Sweep.md), [Example - Even Better OOP - Header Files](Example%20-%20Even%20Better%20OOP%20-%20Header%20Files.md)
#code 

> Source: https://learn.adafruit.com/multi-tasking-the-arduino-part-1/a-classy-solution

We can break them down into the following:

Member variables
- (constant/init. only)
	- Pin #
	- On time
	- Off time
- (variable/maintain current state)
	- State
	- Time Previously Updated

Class function
- 1) stores the current time
- 2) checks if `condition1 && (time_now - time_previous >= time1)`
	- change/increment the state variable to the next state
	- store the current time into `time_previous`
	- update the physical state as desired (e.g. `digitalWrite()`)
- 3) same as (2) for other desired states 

```c
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
};
```

And the main class function:

```c
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
```

Then the final main loop, with initialization is:

```c
Flasher led1(12, 100, 400);
Flasher led2(13, 350, 350);

void setup()
{
}

void loop()
{
	led1.Update();
	led2.Update();
}
```