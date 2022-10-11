


// Matrix Keypad Pins (Right to Left)
// columns: 1-4 
// rows: 5-8

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

// Code remixed from baldengineer.com & Elegoo Lesson 11
// CC BY-SA 4.0

byte rows[] = {8, 9, 10, 11};
const int rowCount = sizeof(rows);

byte cols[] = {2, 3, 4, 5};
const int colCount = sizeof(cols);

byte keys[rowCount][colCount]; 

void setup() {
    Serial.begin(115200);

    for (int x = 0; x < rowCount; x++) {
      // Set Rows as Input (high Z / floating)
      Serial.print(rows[x]); Serial.println(" as input");
      pinMode(rows[x], INPUT); 
    }

    for (int x = 0; x < colCount; x++) {
      // Set Cols as INPUT_PULLUP 5V VCC
      Serial.print(cols[x]); Serial.println(" as input-pullup");
      pinMode(cols[x], INPUT_PULLUP); 
  }
} 

void readMatrix() {
  // iterate the columns
  for (int i = 0; i < colCount; i++) {
    // set a column pin as Output and Bring Low
    byte thisCol = cols[i];
    pinMode(thisCol, OUTPUT); 
    digitalWrite(thisCol, LOW); // provide ground path from row INPUT_PULLUP

    // iterate the rows
    // 0-indexed so use less than
    for (int j = 0; j < rowCount; j++) {
      // set a row pin as INPUT_PULLUP
      // read and store the key's value (inverted logic)
      byte thisRow = rows[j];
      pinMode(thisRow, INPUT_PULLUP); // setting Vcc
      keys[j][i] = digitalRead(thisRow); // store the value (inverted logic: LOW is pressed)
      pinMode(thisRow, INPUT); // reset it to high impedance floating 
    }

    // disable the column
    pinMode(thisCol, INPUT);
  }
}

void printMatrix() {
  // iterate over rows
  // HERE
  for (int j = 0; j < rowCount; j++) {
    // print row index number
    if (j < 10)
      Serial.print(F("0"));
    Serial.print(j); Serial.print(F(": ")); // F("") uses flash based memory (vs. RAM)

    // iterate of cols
    for (int k = 0; k < colCount; k++) {
      // print value
      Serial.print(keys[j][k]);
      if (k < colCount)
        Serial.print(F(", "));
      }

    Serial.println("");

  }
}

void loop() {
  readMatrix();
  delay(200);
  if (Serial.read() == "!")
    printMatrix();
}