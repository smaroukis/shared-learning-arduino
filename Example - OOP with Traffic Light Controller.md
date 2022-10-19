garden-topic::[Object Oriented Programming](Object%20Oriented%20Programming.md)
previous::[Example - Better OOP - Private Functions](Example%20-%20Better%20OOP%20-%20Private%20Functions.md)

> Source: https://rayantonius.com/tech/classes-in-arduino-creating-a-traffic-light/

- Example of using `enum`
- Here TrafficLight is the only class, pretty simple since it doesn't interface with any other classes

`TrafficLight.h`:
```cpp
#ifndef TrafficLights_h
#define TrafficLights_h

// enumerate the color names to be more readable
enum color {GREEN, YELLOW, RED};

class TrafficLight {
  public:
    TrafficLight(byte redPin, byte yellowPin, byte greenPin);
    void Toggle(int color);
    void TurnOff(int color);
    void TurnOn(int color);
    void Go();
    void Careful();
    void Stop();
    bool GetState(int color);
    bool* GetStates();
  private:
    byte pins[3];
    bool states[3]={0}; 
    void init();
};
#endif
```

``TrafficLight.cpp``
```  cpp
#include "Arduino.h"
#include "TrafficLight.h"

void TrafficLight::init() {
   for(int i=0; i<3; i++) {     
     pinMode(this->pins[i], OUTPUT);
   }
 }

TrafficLight::TrafficLight(byte redPin, byte yellowPin, byte greenPin) {
   this->pins[RED] = redPin
   this->pins[YELLOW] = yellowPin;
   this->pins[GREEN] = greenPin;
   this->init();
 }
 
bool TrafficLight::GetState(int color) {
   return this->states[color];
 }

bool* TrafficLight::GetStates() {
   return this->states;
 }
 
void TrafficLight::Toggle(int color) {
   this->states[color] = !this->states[color];
   if(this->states[color]) {
     digitalWrite(this->pins[color], HIGH);
   } else {
     digitalWrite(this->pins[color], LOW);
   }
 }
 
void TrafficLight::TurnOn(int color) {
   if(!this->states[color]) {
     this->Toggle(color);
   }
 }
 
void TrafficLight::TurnOff(int color) {
   if(this->states[color]) {
     this->Toggle(color);
   }
 }
 
void TrafficLight::Go() {
   this->TurnOff(YELLOW);
   this->TurnOff(RED);
   this->TurnOn(GREEN);
 }
 
void TrafficLight::Careful() {
   this->TurnOff(RED);
   this->TurnOff(GREEN);
   this->TurnOn(YELLOW);
 }
 
void TrafficLight::Stop() {
   this->TurnOff(YELLOW);
   this->TurnOff(GREEN);
   this->TurnOn(RED);
 }
```

`Main.cpp`
```cpp
#include "TrafficLight.h"
#include <Arudino.h>

int redPin = 11;
int yellowPin = 10;
int greenPin = 9;

TrafficLight tl(redPin,yellowPin,greenPin);

void setup() {
}

void loop() {
  tl.Stop();
  delay(1000);
  tl.Careful();
  delay(300);
  tl.Go();
  delay(1000);
  tl.Careful();
  delay(300);
}
```