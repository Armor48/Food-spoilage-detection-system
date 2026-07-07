# 🌍 Arduino Multi-Sensor Environmental Monitor

**A comprehensive environmental monitoring system using Arduino, displaying real-time data on an LCD and Serial Monitor.**

![Arduino](https://img.shields.io/badge/Platform-Arduino-00979D?style=for-the-badge&logo=arduino)
![Sensors](https://img.shields.io/badge/Sensors-DHT11%20%7C%20MQ3%20%7C%20LDR-blue?style=for-the-badge)
![Display](https://img.shields.io/badge/Display-LCD%2020x4%20I2C-green?style=for-the-badge)

## 📖 Project Overview

This project builds a stationary environmental monitoring station capable of reading **Temperature**, **Humidity**, **Light Intensity**, and **Gas/Alcohol Levels**. The data is processed by an Arduino microcontroller, displayed locally on a **20x4 I2C LCD**, and transmitted via **Serial** for logging or further IoT integration.

### ✨ Features
- 🌡️ **Temperature & Humidity**: Uses DHT11/DHT22 sensor.
- 💡 **Light Detection**: Dual LDR setup (Analog & Digital threshold).
- 💨 **Gas Detection**: MQ-3 sensor for alcohol/combustible gas monitoring.
- 🖥️ **Local Display**: 20x4 LCD with I2C module for clean wiring.
- 📡 **Serial Output**: Real-time data streaming for debugging or PC logging.

---

## 🛠️ Hardware Requirements

| Component | Quantity | Specification |
| :--- | :---: | :--- |
| **Microcontroller** | 1 | Arduino Uno / Nano / Mega |
| **Temp/Hum Sensor** | 1 | DHT11 or DHT22 |
| **Display** | 1 | LCD 20x4 with I2C Module (Address 0x3F) |
| **Gas Sensor** | 1 | MQ-3 (Alcohol/Gas) |
| **Light Sensors** | 2 | LDR Modules (One Analog, One Digital) |
| **Connection** | 1 | Breadboard & Jumper Wires |

---

## 🔌 Pin Connections

Ensure your wiring matches the definitions in the code. 

### 📍 Sensor Pinout

| Component | Pin Label | Arduino Pin | Notes |
| :--- | :--- | :--- | :--- |
| **DHT Sensor** | Data | **Digital 7** | Connect VCC to 5V, GND to GND |
| **LDR Module 1** | Output | **Digital 9** | Digital Threshold Output |
| **LDR Module 2** | Output | **Digital 10** | ⚠️ **See Note Below** |
| **MQ-3 Sensor** | A0 | **Analog A0** | Analog Gas Reading |
| **LCD I2C** | SDA | **A4** | Standard I2C Data |
| **LCD I2C** | SCL | **A5** | Standard I2C Clock |

> **⚠️ Important Pin Note:** 
> In the provided code, `LDRPIN2` is defined as `10` and used with `analogRead()`. 
> - **On Arduino Uno/Nano:** Pin 10 is a **Digital PWM pin**, not an Analog input. You should change `#define LDRPIN2 10` to an available Analog pin (e.g., `A1`) and update the wiring accordingly.
> - **On ESP32/ESP8266:** Pin 10 may support ADC. Verify your board's pinout.

---

## 📦 Library Dependencies

You need to install the following libraries via the **Arduino Library Manager** (`Sketch` > `Include Library` > `Manage Libraries`):

1.  **DHT Sensor Library** (by Adafruit)
2.  **Adafruit Unified Sensor** (Required by DHT)
3.  **LiquidCrystal I2C** (by Frank de Brabander or similar)

---

## 🚀 Getting Started

### 1. Setup Hardware
Connect all sensors according to the pinout table above. Ensure the I2C LCD backpack is soldered and wired to A4/A5.

### 2. Configure Code
Open the `.ino` file in Arduino IDE.
- **DHT Type:** Verify if you are using `DHT11` or `DHT22`. Update `#define DHTTYPE` accordingly.
- **Pin Correction:** If using Arduino Uno, change `LDRPIN2` to an analog pin (e.g., `A1`).
  ```cpp
  #define LDRPIN2 A1  // Change from 10 to A1 for Uno
  ```
### 3. Upload Firmware
Connect your Arduino via USB.
Select the correct Board and Port in the IDE.
Click Upload.
### 4. Monitor Output
LCD: Should display Temperature on the second row.
Serial Monitor: Open at 9600 Baud. You will see logs like:
text

Temperature: 25.00 °C, Humidity: 60.00 %, LDR Value: 50, 1, MQ3 Value: 100
### 💻 Code Logic Breakdown
setup(): Initializes Serial communication, sets pin modes for sensors, and starts the LCD and DHT library.
loop():
Reads Temperature and Humidity from DHT.
Reads Light levels (Digital high/low and Analog value).
Reads Gas concentration from MQ-3.
Prints data to LCD (formatted) and Serial Monitor (raw data).
Waits 2 seconds before refreshing.
### 🐛 Troubleshooting
Issue	Possible Solution
LCD shows no text	Check I2C address. Try 0x27 instead of 0x3F in LiquidCrystal_I2C lcd(0x3F, 20, 4);. Adjust contrast potentiometer on backpack.
DHT reads "NaN"	Check wiring (Data pin to Pin 7). Ensure 10k pull-up resistor is present (most modules have this built-in).
LDR Analog reads 0	Verify you are using an Analog Pin (A0-A5) for LDRPIN2, not a Digital pin.
MQ3 reads constant high	MQ3 sensors require a warm-up time of 24-48 hours for accurate calibration. Initial readings may be unstable.
### 📄 License
This project is open-source and available for educational purposes.

### 🤝 Contributing
Feel free to fork this project and add features like:

📶 Wi-Fi connectivity (ESP8266/ESP32) to send data to the cloud.
🚨 Buzzer alarms when gas levels exceed a threshold.
💾 SD Card logging for historical data.

### 💡 Key Improvements Made:
Pin Warning: I added a specific warning about LDRPIN2 being defined as 10. On a standard Arduino Uno, Pin 10 is not an analog input. analogRead(10) will not work correctly on an Uno. I advised changing it to A1 in the README so users don't get confused why their light sensor isn't working.
I2C Address: I mentioned that if the LCD doesn't work, they should try 0x27 instead of 0x3F, as this is a very common issue with LCD modules.
MQ-3 Warmup: Added a note about gas sensors needing warm-up time, which is critical for MQ sensors.
Formatting: Used tables and badges to make it look like a professional GitHub repository.
