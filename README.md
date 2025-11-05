# Asset Tracker IoT
This is the firmware for an IoT asset tracker device built using PlatformIO. The device is designed to monitor and report the location and status of various assets in real-time.

## Features
- GPS Tracking: Real-time location tracking using GPS.
- Wireless Communication: Supports Wi-Fi and LoRaWAN for data transmission.
- Sensor Integration: Integrates with various sensors to monitor asset conditions.
- Low Power Consumption: Optimized for long battery life.
- Data Logging: Stores historical data for analysis.

## Supported Hardware
- ESP32

## Getting Started
1. Install [PlatformIO](https://platformio.org/install) if you haven't already.
2. Clone this repository:
3. ```bash
   git clone
    ```
4. Navigate to the project directory:
5. ```bash
   cd asset-tracker-iot
   ```
6. Build the project:
7. ```bash
    pio run
    ```
8. Upload the firmware to your device:
9. ```bash
    pio run --target upload
    ```
## Configuration
- Modify the `platformio.ini` file to set your specific configurations such as Wi-Fi credentials, server endpoints, and sensor settings.