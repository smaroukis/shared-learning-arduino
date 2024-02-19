> Note: I thought this was working but it might not be - didn't work when I ported it to another project 

Example using a debounced "updateFunction" function with required variables as `static` (static means that the variable and its value persist between function calls but is only available to the scope of the function, great for incrementing a variable that doesn't need to be exposed to any other function).

Requires an `INPUT_PULLUP` type digital input, with wiring as shown:

_Figure: Wiring for the pushbutton as an `INPUT_PULLUP` digital input_
![[Screenshot 2023-08-20 at 12.49.07 PM.png]]


```cpp
const int BUTTON = 3;
const int LED = LED_BUILTIN;

// Description: Non blocking debounce function that returns 1 on a Unpressed → Pressed debounced transition
// Requires: BUTTON pin configured as an INPUT_PULLUP
int updateButton() {
    static int lastButtonState = 1; // unpressed is HIGH (INPUT_PULLUP)
    static unsigned long lastDebounceTime = 0;
    const int debounceDelay = 30;  // Adjust as needed
    int buttonState = digitalRead(BUTTON);

    // Reset debounce timer if state change
    // Hold onto lastButtonState
    if (buttonState != lastButtonState) {
        lastDebounceTime = millis();
        Serial.print("Starting debounce, lastButtonState =");
        Serial.print(lastButtonState);
        Serial.print(", Current State = ");
        Serial.println(buttonState);
    }

  // Timer is done, accept the current buttonState and compare to previously stored state
    if (millis() - lastDebounceTime >= debounceDelay) {
        if (buttonState != lastButtonState) { // State change detected
            Serial.println("...State change detected");
            lastButtonState = buttonState;
            if (buttonState == 0) {
              Serial.println("......Unpressed → Pressed Transition Detected, Returning 1");
              return 1; // only return 1 on Unpressed → Pressed transition
            }
        }
      }
    else {
      // fall through
    }

    lastButtonState = buttonState; // why do we need this? otherwise the readnig won't update
    return 0;  // No button state change Unpressed → Pressed detected or debounce timer not complete
}

void setup() {
  pinMode(BUTTON, INPUT_PULLUP);
  pinMode(LED, OUTPUT);
  digitalWrite(LED, LOW);

  Serial.begin(9600);
  Serial.println("Started Serial Monitor");
}

void loop() {
  int buttonPressed = updateButton();

  if (buttonPressed) {
    digitalWrite(LED, !digitalRead(LED)); // toggle LED
  }
}
```

#code 