


// Matrix Keypad Pins (Right to Left)
// columns: 1-4 
// rows: 5-8

// Arduino Pins
// columns 1-4 -> 2, 3, 4, 5
// rows 5-8 -> 6, 7, 8, 9


// Code remixed from baldengineer.com & Elegoo Lesson 11
// CC BY-SA 4.0

byte rows[] = {5, 6, 7, 8};
const int rowCount = sizeof(rows);

byte cols[] = {1, 2, 3, 4};
const int colCount = sizeof(cols)/sizeof(cols[0]);

byte keys[colCount][rowCount];

void setup(){
  Serial.begin(115200);

  for (int x = 0; x < rowCount; x++) {
    Serial.print(rows[x]; Serial.println(" as input");;
    pinMode(rows[x], INPUT); // setting rows as Input eg high Z
  }

  for (int x = 0; x < colCount; x++) {
    Serial.print(cols[x]; Serial.println(" as input-pullup");
    pinMode(cols[x], INPUT_PULLUP); // setting columns as INPUT_PULLUP - our Vcc
  }
}

void readMatrix() {
  // iterate the columns
  for (int i = 0; i < colCount; i++) {
    // set cols output to low
    byte thisCol = cols[i];
    pinMode(thisCol, OUTPUT); 
    digitalWrite(thisCol, LOW); // provide ground path from row INPUT_PULLUP

    // iterate the rows
    // 0-indexed so use less than
    for (int j = 0; j < rowCount; j++) {
      byte thisRow = rows[j];
      pinMode(thisRow, INPUT_PULLUP); // setting Vcc
      keys[i][j] = digitalRead(thisRow); // store the value (inverted logic: LOW is pressed)
      pinMode(thisRow, INPUT); // reset it to high impedance floating 
    }

    // disable the column
    pinMode(thisCol, INPUT);
  }
}

void printMatrix() {
  // iterate over rows
  for (int j = 0; j < rowCount; j++) {
    if (j < 10)
      Serial.print(F("0"));
    Serial.print(j); Serial.Print(F(": ")); // F("") uses flash based memory (vs. RAM)
  }

    // iterate of cols
    for (int k = 0; k < colCount; k++) {
      Serial.print(keys[k][j]);
      if (k < colCount)
        Serial.print(F(", "));
    }

    Serial.println("");
}

void loop() {
  readMatrix();
  if (Serial.read() == "!")
    printMatrix();
}