parent::[[James A. Langbridge - Arduino Sketches]], [[Examples]]
garden-topic::[[I2C]], [[Interrupts, Timers and Callbacks]]

### `Secondary Sketch`
- Runs on the Arduino acting as a Secondary (peripheral)
```cpp
1   #include <Wire.h>
2
3   #define SECONDARY_ADDRESS 0x08
4   int data = 0;
5   int state = 0;
6
7   void setup()
8   {
9     pinMode(13, OUTPUT); // Internal LED
10    Serial.begin(9600);
11    Wire.begin(SECONDARY_ADDRESS); // Initialize as I2C slave
12
13    // Register I2C callbacks
14    Wire.onReceive(receiveData);
15    Wire.onRequest(sendData);
16  }
17
18  void loop()
19  {
20    // Nothing to do
21    delay(100);
22  }
23
24  // Callback for data reception
25  void receiveData(int byteCount)
26  {
27    while(Wire.available())
28    {
29      data = Wire.read();
30      Serial.print("Data received: ");
31      Serial.println(data);
32
33      if (data == 1)
34      {
35        digitalWrite(13, HIGH); // Turn the LED on
36        state = 1;
37      }
38      else
39      {
40        digitalWrite(13, LOW); // Turn the LED off
41        state = 0;
42      }
43    }
44  }
45
46  // Callback for sending data
47  void sendData()
48  {
49      Wire.write(state); // Send the LED state
50  }
```

### Main Sketch

```cpp
1   #include <Wire.h>
2
3   #define SECONDARY_ADDRESS 0x08
4   int data = 0;
5   int state = 0;
6
7   void setup()
8   {
9     pinMode(13, OUTPUT); // Internal LED
10    Serial.begin(9600);
11    Wire.begin(); // Initialize as I2C main 
12  }
13
14  void loop()
15  {
16    Wire.beginTransmission(SECONDARY_ADDRESS); // Prepare message to slave
17    Wire.write(1); // Send one byte, LED ON
18    Wire.endTransmission(); // End message, transmit
19    digitalWrite(13, HIGH); // Turn the LED on
20
21    delay(10); // Give the slave time to react
22    printLight(); // What is the slave's status?
23
24    delay(1000);
25
26    Wire.beginTransmission(SECONDARY_ADDRESS); // Prepare message to slave
27    Wire.write(0); // Send one byte, LED OFF
28    Wire.endTransmission(); // End message, transmit
29    digitalWrite(13, LOW); // Turn the LED off
30
31    delay(10); // Give the slave time to react
32    printLight(); // What is the slave's status?
33
34    delay(200);
35  }
36
37  void printLight()
38  {
39    Wire.requestFrom(SECONDARY_ADDRESS, 1); // Request 1 byte from slave
40
41    data = Wire.read(); // Receive a byte af data
42    switch (data)
43    {
44      case 0:
45        Serial.println("LED is OFF");
46        break;
47      case 1:
48        Serial.println("LED is ON");
49        break;
50      default:
51        Serial.println("Unknown status detected");
52        break;
53    }
54  }
```

Further
- we could send several bytes to power multiple leds