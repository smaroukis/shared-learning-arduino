---
alias: "Getting Started With Arduino"
author: "Massimo  Banzi"
format: Book
tags: [n/reference]
cover: https://img1.od-cdn.com/ImageType-100/2858-1/{99227FF1-1BD5-4F09-BF71-848EA4675E77}Img100.jpg
date: 2022-09-17
---
# Getting Started With Arduino
> Note: See Learning Arduino Vault for updates

![rw-book-cover](https://img1.od-cdn.com/ImageType-100/2858-1/{99227FF1-1BD5-4F09-BF71-848EA4675E77}Img100.jpg)

## Metadata
- Author:: [[Massimo  Banzi]]
- Title:: Getting Started With Arduino
- garden-topic::[[../../Arduino]]
- status:: #library/🟢 

## Notes

### Ch 1 Introduction
- #book rec Low Tech Sensors and Actuators - Haque, Somlai-Fischer - see http://lowtech.propositions.org.uk/ -- this also remidns me of 100 Makerspace Projects which also uses easy to access low tech stuff like cheap motors found in toys to make moving robots
	- what if we did a "Daiso" day where you have a contest and have to make something just from buying things from Daiso
	- haque did a artist in residence at International Academy of Media arts an Sciences in Japan
- Arduino was born to teach Interaction Design "the creation of meaningful expreiences between humans and objects"- look for art/media/design programs etc , specifically Physical Interaction Design
- don't spend time learning how to build everything from scratch - this is a waste of time an energy - [[opportunistic prototyping]] is taking ready-made devices, hacking them in order to exploit the hard work done by others
- tinkering - it is essential to play with technology, sometimes without a defined goal
- reduce the amount of interruptions of the flow is important momentum for  [[Creativity]]  
	- see Robert Moog and synthesizers
- "Don’t let the experts in one field tell you that you’ll never be one of them. Ignore them and surprise them" #quote


### Ch 4 Debouncing
- use 22AWG solid core as breadboard hookup wire
- [[../../Memory]]
	- **variables** are stored in RAM; programs stored in **flash**
- neat #software-trick to change the state of a boolean `state = 1 - state`
- debounce for 10-50ms ->  [[../../Debouncing in Software]]

### Ch 5 

## Highlights
**Intro**
- Getting cheap toys or old discarded equipment and hacking them to make them do something new is one of the best ways to get to great results.
- it is essential to play with technology, exploring different possibilities directly on hardware and software—sometimes without a very defined goal.
- James Dyson, who made 5127 prototypes of his vacuum cleaner before he was satisfied that he’d gotten it right.
- This is a waste of energy: what you want is to be able to confirm that something’s working very quickly so that you can motivate yourself to take the next step or maybe even motivate somebody else to give you a lot of cash to do it.
- Reducing the number of interruptions to the
- Robert Moog and his analogue synthesizers
- flow is very important for creativity
- Don’t let the experts in one field tell you that you’ll never be one of them. Ignore them and surprise them
- Learning about keyboard hacking is a key building block of prototyping and physical computing.
- Accumulate junk and go through it before starting to build something from scratch.
- One of my favourite resources is the booklet “Low Tech Sensors and Actuators” by Usman Haque and Adam Somlai-Fischer. I think they have perfectly described this technique in that handbook, and I have been using it ever since.
- The board can be powered from your computer’s USB port, most USB chargers, or an AC adapter (9 volts recommended, 2.1 mm barrel tip, center positive).
- use a simple device called a light-dependent resistor (LDR), also known as a photoresistor, that can measure the amount of light that hits it
- This preinstalled LED is connected to pin number 13
- digitalWrite(LED, HIGH
- pinMode(LED, OUTPUT);
- const int LED = 13;
- Arduino is not like your regular computer—it cannot run multiple programs at the same time, and programs can’t quit
- Arduino always expects that you’ve created two functions: one called setup() and one called loop().
- On the Arduino, HIGH means that the pin will be set to 5 V, while LOW means the pin will be set to 0 V
- Instead of buying precut jumper wire, you can also buy 22 AWG solid-core hookup wire in small
- Your programs themselves are stored in flash memory—this is the same type used by your mobile phone to store phone numbers—which retains its content even when the board is off.
- Notice that variables use a type of memory called RAM. It is quite fast, but when you turn off your board, all data stored in RAM is lost
- change the state if (val == HIGH) { state = 1 - state
- Arduino is really fast; it executes its own internal instructions at a rate of 16 million per second—
- store the value of val before we read a new one; this allows you to compare the current position of the button with the previous one and change state only when the button changes from LOW to HIGH.
- check if there was a transition if ((val == HIGH) && (old_val == LOW)){ state = 1 - state
- debouncing, but in this simple piece of code, it’s usually enough to add a 10- to 50-millisecond delay when the code detects a transition
- analogWrite()
- On the Uno, this hardware is implemented on pins 3, 5, 6, 9, 10, and 11, and on the Leonardo, on pins 3, 5, 6, 9, 10, 11, and 13.
- analogWrite() takes a number between 0 and 255, where 255 means full brightness and 0 means off.
- build an interface in which a press-and-release action switches the light on and off, and a press-and-hold action changes brightness.
- you’ll see six pins marked Analog In; these are special pins that not only can tell you whether there is a voltage applied to them, but also can measure the amount of that voltage, by using the analogRead() function. The analogRead() function returns a number between 0 and 1023, which represents voltages between 0 and 5 volts
- to send messages to or receive them from your computer. The way we do this from a sketch is to use the serial object.
- The Serial Monitor button is near the top-right corner of the Arduino IDE
- the current going through an Arduino I/O pin should be limited to 20 milliamps.
- VIN connector on the Arduino board, which is intended for a voltage between 7 and 12 volts
- If the motor randomly turns on during upload, place a 10 K ohm resistor between pin 9 and GND.
- Tom Igoe’s Making Things Talk (O’Reilly) has extensive coverage of complex sensors
- the ATmega328 can’t process USB connections, while the ATmega16U2 doesn’t have enough of the features to make a useful Arduino
- there is actually a second microcontroller on the Uno, an ATmega16U2, which is responsible for handling the USB interface
- the heart of the Arduino Uno is a microcontroller called the ATmega328
- combined the Arduino features of the ATmega328 with the USB features of the ATmega16U2 to give us the ATmega32U4.
- Arduino Uno has only 6 analogue inputs, A0–A5, which are all grouped together. The Leonardo has 12 analogue inputs, labeled A0 through A11. Inputs A0–A5 appear in the same locations as on the Uno, while inputs A6–A11 are on digital pins 4, 6, 8, 9, 10, and 12, respectively.
- Because the Arduino Leonardo creates the USB port in the sketch, resetting the Arduino Leonardo causes the USB serial connection to be broken and reestablished
- The Arduino Leonardo uses a Micro-B USB cable.
- Example 6-1 is pretending to be a keyboard, and so the serial monitor is not needed
- When you send a string to the serial monitor by using Serial.println(), Arduino sends a special code for each letter (called the ASCII code, see “Variables”).
- special way to program brand-new microcontrollers (for example, in case you have to replace the microcontroller). This is done using another special port called ICSP.
- libraries and examples take advantage of this, but because the Leonardo does not reset when the serial monitor is opened, those libraries may not work properly.
- From now on, libraries and examples should always use the analogue name of the pin, even when being used in digital modes, e.g.:
- Processing is where Arduino came from. We love this language and use it to teach programming to beginners as well as to build beautiful code
- Hexadecimal numbers are handy, because each 8-bit number is stored in exactly two characters; with decimal numbers this varies from one to three characters.
- you’re on a Mac, there’s a good chance your Arduino will be on the last serial port in the list. If so, you can replace the 0 in Serial.list()[0] with Serial.list().length -1. This
- The Arduino sketch is designed to work with a common cathode RGB LED (one where the long lead goes to ground). If you’re getting the wrong output, you might have a common anode
- Add a PIR sensor to detect when somebody is around, and turn it off when nobody is there to watch.
- MOSFETs can control only direct current (DC).
- The main part of an RTC is the chip itself. The most common one is the DS1307, which requires a crystal for correct timekeeping and a battery to keep it running when the rest of the system is switched off.
- This device uses an interface called I2C, sometimes also called the Two Wire Interface (TWI) or simply Wire
- On an Uno, SCL is A5 and SDA is A4. In addition to these two interface pins, we need to connect VCC and GND to any other I/O pins to provide 5V and GND
- the I2C signals (SDA and SCL) could be on different pins. For this reason
- If you search for the current used by this relay in the data sheet, you won’t find
- avoid the MOSFET gates from floating, add three 10 K ohm resistors to your shopping list, one for each relay.
- 10 K ohm between the I/O pin and ground prevents this. 10 K ohms is a low enough resistance to make sure the gate doesn’t “float”, but it’s also a large enough resistance that it won’t get in our way when we want to turn on the water.
- it will be left floating, which means that the MOSFET could easily turn on, causing the water to come on briefly.
- When you turn on or reset an Arduino, all the digital pins start off as inputs
- When possible, I like to put the LED on the farthest point, to verify as much as possible
- Most LEDs use about 2 volts and are safe below 30 mA
- The DHT11 is a popular Temperature and Humidity Sensor. Like the RTC, it is inexpensive and easy to use with Arduino
- [[2022-10-05]] copied to anotehr vault

