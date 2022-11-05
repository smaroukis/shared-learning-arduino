```cpp
const byte PUSHBUTTON = 7;
const byte LED = 12;

const int debounce_time = 50;
unsigned long debounce_timer;
byte state;
byte prev_state;

void setup() {
	pinMode(LED, OUTPUT);
	pinMode(PUSHBUTTON, INPUT_PULLUP);
	state = 0;
	prev_state = 0;
	Serial.begin(115200);
}

void loop() {
	state = digitalRead(PUSHBUTTON); 
	if (state != prev_state)
	{ // either button is pressed or it is noise
		debounce_timer = millis();     // reset debouncing timer
		prev_state = state;
	}
	else if (state == LOW && (millis() - debounce_timer > debounce_time))
	{ 
		digitalWrite(LED, !digitalRead(LED));
		//debounce_timer += debounce_time;
		debounce_timer = millis();
	}
}
```

#code 