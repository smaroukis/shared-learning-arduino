//adapted from www.elegoo.com for Mega 2560 Starter Kit

// Define Pins
const int BLUE = 6;
const int GREEN = 5;
const int RED = 3;

void setup(){
  pinMode(RED, OUTPUT);
  pinMode(GREEN, OUTPUT);
  pinMode(BLUE, OUTPUT);
  digitalWrite(RED, HIGH);
  digitalWrite(GREEN, LOW);
  digitalWrite(BLUE, LOW);
}

int redVal;
int greenVal;
int blueVal;

void loop(){
  const int tDelay = 10;

  redVal = 255;
  greenVal = 0;
  blueVal = 0;

// fade out red, bring green in
  for(int i = 0; i < 255; i += 1){
    redVal -= 1; // was set to 255 previously
    greenVal += 1; // 

    analogWrite(RED, redVal);
    analogWrite(GREEN, greenVal);
    delay(tDelay);
  } 

  redVal = 0;
  greenVal = 0;
  blueVal = 255;

// fade out blue, bring in blue
  for(int i = 0; i < 255; i += 1){
    greenVal -= 1;
    blueVal += 1;
    analogWrite(GREEN, greenVal);
    analogWrite(BLUE, blueVal);
    delay(tDelay);
  }

  redVal = 0;
  greenVal = 0;
  blueVal =255;

  // fade out blue, bring red in
  for(int i = 0; i < 255; i += 1){
    analogWrite(BLUE, blueVal);
    analogWrite(RED, redVal);
    delay(tDelay);
  }

}