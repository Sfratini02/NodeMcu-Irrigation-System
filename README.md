
<h3 align="center">
Automatic Irrigation Project 🌱💧
</h3>

<h2 align="center">
Automate your irrigation system with an ESP32 microcontroller!
</h2> 

The system monitors soil moisture levels and controls a water pump and servos to irrigate plants as needed. Data is logged to an SD card for monitoring and analysis.

## Features

- Monitors soil moisture levels using sensors
- Activates a water pump to irrigate when soil moisture is low
- Positions servos to direct water to the correct plant
- Logs all data to an SD card in CSV format
- Connects to WiFi to synchronize time using NTP

## Hardware Requirements

- ESP32 Development Board
- Soil Moisture Sensors
- Water Pump
- Servos
- SD Card Module
- Relay or Transistor (for the pump)
- Connecting wires and a breadboard

## Software Requirements

- Arduino IDE
- Arduino Libraries: WiFi, NTPClient, SPI, SD, Servo, TimeLib, WiFiManager

## Project Structure

AutomaticIrrigationProject/
│
├── AutomaticIrrigationProject.ino
├── WiFiSetup.h
├── WiFiSetup.cpp
├── NTPClientSetup.h
├── NTPClientSetup.cpp
├── SensorsActuators.h
├── SensorsActuators.cpp
├── SDCard.h
├── SDCard.cpp
└── Utilities.h
└── Utilities.cpp



## Installation

1. **Clone the Repository**
    ```bash
    git clone https://github.com/yourusername/AutomaticIrrigationProject.git
    cd AutomaticIrrigationProject
    ```

2. **Open the Project in Arduino IDE**
    - Open the `AutomaticIrrigationProject.ino` file in the Arduino IDE.

3. **Add the Required Libraries**
    - Ensure you have the following libraries installed in the Arduino IDE:
        - WiFi
        - NTPClient
        - SPI
        - SD
        - Servo
        - TimeLib
        - WiFiManager

4. **Upload the Code to ESP32**
    - Connect your ESP32 to your computer via USB.
    - Select the correct board and port in the Arduino IDE.
    - Upload the code.

## Usage

1. **Connect the Hardware**
    - Connect the soil moisture sensors, servos, water pump, and SD card module to the ESP32 according to the pin configurations in the code.

2. **Power On the ESP32**
    - The ESP32 will start and attempt to connect to a WiFi network.
    - If it cannot connect, it will create an access point named "ConfigESP" where you can configure the WiFi credentials.

3. **Monitoring and Logging**
    - The system will read soil moisture levels, activate the pump if necessary, and log the data to the SD card.
    - You can monitor the output via the Serial Monitor in the Arduino IDE.

## Code Overview

### `AutomaticIrrigationProject.ino`
- Contains the `setup()` and `loop()` functions which initialize the system and handle the main logic loop.

### `WiFiSetup.h` and `WiFiSetup.cpp`
- Functions to manage WiFi connection using WiFiManager.

### `NTPClientSetup.h` and `NTPClientSetup.cpp`
- Functions to initialize and update the NTP client for time synchronization.

### `SensorsActuators.h` and `SensorsActuators.cpp`
- Functions to read soil moisture sensors, position servos, and control the water pump.

### `SDCard.h` and `SDCard.cpp`
- Functions to initialize the SD card and log data in CSV format.

### `Utilities.h` and `Utilities.cpp`
- Utility functions such as date formatting.

## Contributions

Contributions are welcome! Please fork the repository and submit a pull request for any enhancements or bug fixes.

## License

See the LICENSE file for details.


