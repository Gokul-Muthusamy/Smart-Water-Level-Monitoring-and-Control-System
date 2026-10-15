# Smart Water Level Monitoring and Control System

An Arduino-based system that monitors the water level in a tank in real time and automatically controls the water pump. An HC-SR04 ultrasonic sensor measures the distance between the sensor and the water surface. The Arduino calculates the approximate water level and switches the pump through a relay according to predefined level thresholds.

**Developed by:** Gokul Nathan. M

## Project Overview

The system is designed to reduce manual tank-level checking and help prevent water overflow. The ultrasonic sensor is mounted at the top of the tank. The Arduino reads the sensor, estimates the water level as a percentage of the configured tank height, and controls the pump through a relay. LEDs show the approximate level, while a buzzer and alert LED indicate a full tank.

## Key Features

- Real-time water-level measurement using an HC-SR04 ultrasonic sensor
- Water-level calculation in centimetres and percentage
- Automatic water pump control through a relay
- LED indicators for 25%, 50%, 75%, and 100% levels
- Buzzer and alert LED when the tank is full
- Serial Monitor output for distance and water-level readings
- Configurable tank height and relay activation logic

## Components Required

| Component | Quantity |
|---|---:|
| Arduino UNO (or compatible board) | 1 |
| HC-SR04 ultrasonic sensor | 1 |
| Relay module suitable for the pump | 1 |
| Water pump | 1 |
| LEDs for level indication | 4 |
| Full-level alert LED | 1 |
| Buzzer | 1 |
| Resistors, jumper wires and suitable power supplies | As required |
| Water tank | 1 |

## Connections

| Arduino pin | Component | Purpose |
|---|---|---|
| D2 | LED | 25% level indicator |
| D3 | LED | 50% level indicator |
| D4 | LED | 75% level indicator |
| D5 | LED | 100% level indicator |
| D6 | Buzzer | Full-tank sound alert |
| D7 | Alert LED | Full-tank visual alert |
| D8 | HC-SR04 TRIG | Trigger signal |
| D9 | HC-SR04 ECHO | Echo signal |
| D10 | Relay module input | Pump control |

Check your specific relay module and board voltage requirements before wiring. Do not connect a pump directly to an Arduino pin.

## How It Works

1. The ultrasonic sensor sends a sound pulse toward the water surface.
2. The sensor's echo time is used to estimate the distance to the water.
3. The Arduino calculates the water height using the configured tank height.
4. The water level is converted into a percentage and printed to the Serial Monitor.
5. LEDs indicate the measured level, and the relay switches the pump according to the program's thresholds.
6. At full level, the pump is switched off and the buzzer and alert LED are activated.

### Calculation

- **Distance (cm):** echo duration in microseconds / 58.82
- **Water level (cm):** tank height - measured distance
- **Water level (%):** (water level / tank height) × 100

The calculations assume the sensor is mounted at the top of the tank and the configured tank height is measured from the sensor reference point to the tank bottom.

## Pump Control Logic

The current Arduino program uses these thresholds:

| Measured water level | Pump action | Indicator / alert |
|---|---|---|
| Below 25% | ON | 25% LED (when level is above 0%) |
| 25% to below 50% | ON | 25% and 50% LEDs |
| 50% to below 75% | OFF | 25%, 50%, and 75% LEDs |
| 75% to below 100% | OFF | All four level LEDs |
| 100% or above | OFF | All level LEDs, alert LED, and buzzer |

These are the thresholds implemented in the supplied code. Adjust them to suit the tank and pump requirements, and test the system safely before use.

## Configuration

Open `Smart_Water_Level_Monitoring_and_Control_System.ino` in the Arduino IDE.

### Tank height

Set `TANK_HEIGHT` to the measured tank height in centimetres:

```cpp
const float TANK_HEIGHT = 30.0;
```

The value `30.0` is an example; change it to match your tank.

### Relay logic

The code includes a setting for the relay module:

```cpp
#define RELAY_ACTIVE_HIGH 1
```

Use `1` for an active-HIGH relay input or `0` for an active-LOW relay input, according to the relay module's specifications. Verify the pump's ON/OFF behaviour with a safe test setup before connecting the actual pump.

## Upload and Test

1. Install the Arduino IDE.
2. Connect the Arduino board to your computer using USB.
3. Open the `.ino` file in the Arduino IDE and select the correct board and port.
4. Check the wiring and update the tank height and relay logic if required.
5. Upload the program.
6. Open the Serial Monitor at **9600 baud** to view distance and water-level readings.
7. Test sensor readings and relay operation with the pump safely disconnected before running the complete setup.

## Safety Notes

- Never power a water pump directly from an Arduino GPIO pin.
- Use a relay or driver rated for the pump and its supply voltage/current.
- Use a separate, suitable pump power supply when required.
- Keep electronics dry and protected from splashes.
- Use appropriate electrical isolation, fuses, grounding, and an enclosure, especially for mains-powered pumps.
- This project is intended as an educational prototype; have mains-powered wiring checked by a qualified person.

## Project Structure

```text
Smart_Water_Level_Monitoring_and_Control_System/
├── README.md
├── Smart_Water_Level_Monitoring_and_Control_System.ino
├── SmartTank.PNG
└── Structure.png
```

## Possible Future Improvements

- Add hysteresis to reduce frequent pump switching
- Add an LCD/OLED display
- Add Wi-Fi monitoring using an ESP8266 or ESP32
- Add mobile notifications and data logging
- Add dry-run protection and pump fault detection

## License and Use

This project is intended for learning, demonstration, and personal development. Review the repository's original license terms before redistributing or publishing modified versions.
