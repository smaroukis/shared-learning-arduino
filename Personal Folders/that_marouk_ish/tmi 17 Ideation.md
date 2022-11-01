parent::[[tmi 17 Home Automation]]

Project Specs
- outdoor sensor
	- wireless / wifi or bluetooth (can go directly to another device)
	- temperature sensor
	- rain sensor? 
	- solar powered
	- air quality? 
- indoor display
	- would be nice to eventually control the lights and air filter from here (IR hacking)
	- could also add a cheap hepa filter to the bathroom, add timers

What do I need right now?
- a timer for the hepa filter

---

Steps
1. Get MQTT on edge device (e.g. wifi enabled arduino)
2. Setup RasPi local Server 
	- OS: node-red, home-assistant
	- as a MQTT broker - e.g. with Mosquitto
	- DB: influx-db (MQTT publishes to influx-db through node-red)
	- Graphical: Grafana, etc.
3. Compile C on edge device to send temperature data to the MQTT broker
4. Add a home controller

---

See https://www.youtube.com/watch?v=ZrkAWSemDC8&t=452s for using an ESP 8266 as a doorbell alarm notifier with Telegram (as fast as possible)

Also see Great Scotts series on[ DIY Home Intruder Automation](https://www.youtube.com/watch?v=IvI1RqYPO24)
- using ESPHome with RasPi and ESP8266 + home asistance software
- RasPi is used as the home server
- https://www.home-assistant.io/getting-started/
- https://esphome.io/index.html

ESPHome is a _tool_ which aims to make managing your ESP boards as simple as possible. It reads in a YAML configuration file and creates custom firmware which it installs on your ESP device. Devices or sensors added in ESPHome’s configuration will automatically show up in Home Assistant’s UI.
- see [getting started](https://esphome.io/guides/getting_started_hassio.html)

---

### MQTT
- [[../../MQTT]]
- Adafruit has their own MQTT broker - cloud hosted, free - https://learn.adafruit.com/mqtt-in-circuitpython/connecting-to-the-adafruit-io-mqtt-broker
	- https://github.com/adafruit/Adafruit_MQTT_Library 
- Mosquitto is popular for local and edge networks