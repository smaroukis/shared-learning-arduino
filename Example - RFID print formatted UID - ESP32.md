> ESP32 example with the [[ESP32 DOIT Devkit]] - note the pins are set by default by the `SPI.begin()` call

## Notes

Since the UID of the RFID is a series of bytes stored as hexadecimal values, each byte can be be represented with up to 2 hex digits from `0x0` to `0xFF` (0 to 255 in decimal). (→ [[Counting - Hexadecimal Binary and Decimal]])

If we printed out the value of `0x0` in hex we would get `0` in decimal (i.e. a single digit). Like wise we get single digits until we reach decimal `10` (`0x10` in hex). So the trick below is to check the byte value and insert (concat) a leading zero for values less than `10`, then insert the byte value as before.

So if the byte value is `0x9`  the string becomes a literal `09`. This way the actual string prints out **two-digit hex values** for each byte, and so all UIDs of the same size in memory will be of the same length in string.

```cpp
for (byte i = 0; i < mfrc522.uid.size; i++) {
  uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "")); // formatting for 
  uid.concat(String(mfrc522.uid.uidByte[i], HEX));
}
```


## Code 

```cpp

#include <Arduino.h>
#include <SPI.h>
#include <MFRC522.h>
#define RST_PIN         34          // Reset pin for RFID sensor
#define SS_PIN           5        // Connect to SDA on RFID reader
// SCK → GPIO18
// MOSI → GPIO23
// MISO → GPIO19


// Uno Reset Pin = 9 , ESP 32 =? 
// Uno SS Pin = 10, ESP32 = 5, 17 or 16

MFRC522 mfrc522(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600); // Initialize serial communication
  SPI.begin(); // Initialize SPI bus default: (SCK: GPIO18, MOSI: GPIO23, MISO: GPIO19).
  mfrc522.PCD_Init(); // Initialize MFRC522 RFID reader
}

void loop() {
  // Look for new cards
  if (mfrc522.PICC_IsNewCardPresent() && mfrc522.PICC_ReadCardSerial()) {
    // Get UID of the card
    String uid = "";
    for (byte i = 0; i < mfrc522.uid.size; i++) {
      // Format with leading zero for single digit numbers (i.e. <10)  e.g. 0x9 → '09'
      uid.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? "0" : "")); 
      uid.concat(String(mfrc522.uid.uidByte[i], HEX));
    }

    // Print UID to serial monitor
    Serial.println("UID tag : " + uid);

    // Halt PICC
    mfrc522.PICC_HaltA();
    // Stop encryption on PCD
    mfrc522.PCD_StopCrypto1();
  }
}
```