# Smart Plant Monitoring System using Arduino IoT Cloud

Smart plant monitoring and automatic watering system built on NodeMCU ESP8266 and Arduino IoT Cloud. It reads soil moisture, temperature, and humidity, uploads data to the cloud dashboard, and controls a relay‑driven water pump that can be toggled remotely.

---

## Overview

The system is designed to help home gardeners and small growers maintain healthy plants with minimal manual effort. It:

- Monitors **soil moisture**, **temperature**, and **humidity** in real time.
- Sends sensor data to **Arduino IoT Cloud**, where it can be viewed on a web or mobile dashboard.
- Lets the user control a **relay‑driven water pump** remotely via a cloud switch.
- Can be extended to automatically water plants based on soil moisture thresholds.

This turns the NodeMCU into an always‑connected “plant assistant” that provides live status and control from anywhere with internet access.

---

## Hardware

Main components:

- **NodeMCU ESP8266**  
  Microcontroller with built‑in Wi‑Fi, used to read sensors and connect to Arduino IoT Cloud.

- **Soil moisture sensor**  
  Analog output connected to `A0` of NodeMCU to measure water content in the soil.

- **DHT22 temperature and humidity sensor**  
  Digital sensor providing ambient temperature and humidity.

- **Relay module**  
  Acts as a switch between NodeMCU and the water pump’s power supply.

- **DC water pump**  
  Pumps water when the relay is activated to irrigate the plant.

- **Breadboard, jumper wires, USB cable, external pump power supply**  
  For prototyping and powering the system.

The NodeMCU powers the low‑power sensors, while the relay separates the NodeMCU from the higher‑current pump supply.

---

## How it works

### Hardware flow

1. The **soil moisture sensor** outputs an analog value (0–1023) representing soil wetness; drier soil → lower reading.  
2. The **DHT22** provides temperature and humidity readings periodically.  
3. The **NodeMCU** reads these sensors and is connected via Wi‑Fi to Arduino IoT Cloud.  
4. A **relay** connected to a digital pin (e.g. `D0`/`D1`) drives the pump’s power line, switching it on or off.

### Software / cloud flow

The Arduino sketch (in `src/plant-monitoring/`) uses:

- `ArduinoCloud.update()` in `loop()` to maintain connection and sync variables.
- A DHT library (e.g. `DHT.h`) to read temperature and humidity.
- `analogRead(A0)` to read soil moisture and map it into a percentage (e.g. 1–100 %).
- Cloud variables defined in `thingProperties.h`, including:
  - `humidity`, `temperature`, `soilMoisture`,
  - `relay` (CloudSwitch) to control the water pump.

When `relay` is toggled from the Arduino IoT Cloud dashboard, the generated `onRelayChange()` callback runs:

```cpp
void onRelayChange() {
  if (relay) {
    digitalWrite(D0, HIGH);  // turn pump ON
  } else {
    digitalWrite(D0, LOW);   // turn pump OFF
  }
}
```
---
AUTHORSHIP:
This project was developed by Kanchanamala P as part of BEEE102L at VIT Chennai; do not submit it as your own coursework.
