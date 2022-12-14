// remixed from https://forum.arduino.cc/t/keypad-without-keypad-library/656198/7
// added pullup inputs and re-defined keys

// Matrix Keypad Pins (Right to Left)
// columns: 1-4 (right to left)
// rows: 5-8 (bottom to top)

// Arduino Pins <- Matrix Keypad
// Matrix Columns
// 2 <- 1 (rightmost pin, rightmost col "ABCD")
// 3 <- 2 
// 4 <- 3
// 5 <- 4 (leftmost col "147*")

// Matrix Rows
// 8 <- 5 (bottom row "*0#D")
// 9 <- 6
// 10 <- 7
// 11 <- 8 (top row "123A")

const int pinCols[4]={5, 4, 3, 2}; // reverse order array is needed to access and print correctly
const int pinRows[4]={11, 10, 9, 8};

char keys[4][4]={
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

void setup() {
  Serial.begin(9600);
  
  for(int i=0; i<4; i++) {
    // set Rows as Input (high Z floating)
    pinMode(pinCols[i], INPUT);
    // set Cols as Pullup Input (normal  +VCC)
    pinMode(pinRows[i], INPUT_PULLUP);
    // digitalWrite(pinCols[i], HIGH);
  }
}

void loop() {
  readKey();
  delay(100);
}

void readKey(){
  // Columns 
  for (int c=0; c<4; c++) {
    // provide ground path from a rows' Internal Pullup Resistor (see below)
    pinMode(pinCols[c], OUTPUT);
    digitalWrite(pinCols[c], LOW);
    // Rows 
    for(int r=0; r<4; r++){
      // set the row as HIGH with an INPUT_PULLUP 
      // a button press will provide a path to ground since the column pin is set LOW
      // logic is inverted so if we read a pin LOW then the button is pressed
      pinMode(pinRows[r], INPUT_PULLUP);
      if (digitalRead(pinRows[r]) == LOW) { 
        // display the right symbol
        // make sure to define keys in correct order when initializing
        // i.e. the index is reversed from the pin order
        Serial.println(keys[r][c]); 
      }

      // reset row pin to high impedance floating
      pinMode(pinRows[r], INPUT); 
    }

    // reset col pin
    pinMode(pinCols[c], INPUT); 
  }
}