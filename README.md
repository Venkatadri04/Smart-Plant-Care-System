**ESP32 Blynk Smart Plant Monitoring and Automatic Watering System 🌱💧🤖**

**Project Overview**

This project is an ESP32-based smart plant monitoring and automatic watering system integrated with the Blynk IoT platform. It uses sensors to measure environmental parameters such as temperature 🌡️, humidity 💧, light intensity 💡, and soil moisture 🌿. Based on sensor readings or manual user control through the Blynk app 📱, the system automatically controls a water pump (motor) to water the plant. Real-time sensor data and alerts 🚨 are sent to the Blynk app, and plant status is displayed on a 16x2 I2C LCD 🖥️.

**Features ✨**

Connects ESP32 to WiFi 📶 and Blynk cloud platform for remote monitoring and control.

Measures temperature and humidity using a DHT11 sensor 🌡️💧.

Monitors ambient light intensity via an LDR sensor 💡.

Measures soil moisture levels with an analog soil moisture sensor 🌿.

Automatically controls a water pump motor based on sensor thresholds 🤖.

Allows manual override of watering motor from the Blynk app 🔄.

Sends alerts 🚨 to the Blynk app for critical conditions:

High temperature (>30°C) 🔥

Low humidity (<40%) 🥵

Low light intensity 🌑

Dry soil condition 🌵

Displays sensor readings and motor status on a 16x2 I2C LCD 🖥️.

Serial debug logging for development and troubleshooting 🛠️.

Hardware Components 🧰
ESP32 development board 🏁

DHT11 temperature and humidity sensor 🌡️💧

LDR (light-dependent resistor) sensor 💡

Analog soil moisture sensor 🌿

Motor driver module or relay module to control water pump 🤖

Water pump motor 💦

16x2 I2C LCD display 🖥️

Connecting wires and power supply 🔌

Pin Configuration 🔌
DHT11 Sensor: GPIO 15 (Data pin for temperature and humidity) 🌡️💧

LDR Sensor: GPIO 33 (Analog input for light sensor) 💡

Soil Moisture Sensor: GPIO 32 (Analog input for soil moisture) 🌿

Motor Control IN1: GPIO 14 (Motor driver input 1) 🤖

Motor Control IN2: GPIO 27 (Motor driver input 2) 🤖

LCD I2C: Default I2C address 0x27 connected to SDA and SCL pins 🖥️Libraries:

Blynk ESP32 library 📱

DHT sensor library 🌡️💧

LiquidCrystal_I2C library 🖥️

Blynk account with project created using template ID and authentication token 🔑.

Installation and Usage 🚀
Connect the hardware components as per the pin configuration above 🔌.

Open the Arduino IDE and install required libraries 💻.

Copy the provided code into the IDE 📋.

Update WiFi SSID and password in the code (ssid and pass variables) 🔐.

Ensure Blynk template ID and authentication token are correctly set 🔑.

Upload the code to the ESP32 board ⬆️.

Open the Serial Monitor at 115200 baud to view debug messages 🛠️.

Open the Blynk app on your mobile device to monitor sensor data, control watering manually, and receive alerts 📱.

The LCD will display live readings and motor status 🖥️.

**How It Works ⚙️**

The ESP32 connects to WiFi and Blynk cloud ☁️.

Sensors measure temperature, humidity, light, and soil moisture 🌡️💧💡🌿.

Sensor values are sent to the Blynk app virtual pins for visualization 📊.

If any environmental conditions are unsuitable (high temp, low humidity, low light, dry soil), the motor will turn ON automatically to water the plant 🤖💦.

The user can manually override motor control through a toggle switch in the Blynk app 🔄.

Alerts are logged to Blynk only once per condition breach until restored 🚨.

The 16x2 LCD displays current environmental data and motor ON/OFF state 🖥️.

Serial prints provide detailed runtime info for debugging 🛠️.

**Customization 🔧**

Adjust threshold values in the code (temp > 30, hum < 40, ldrValue < 3000, soilMoistureValue > 2000) as per plant and environment needs 🌿.

Modify manual control virtual pin allocation (currently V8) 🔄.

Extend functionality by adding more sensors or actuators 🤖.

**Troubleshooting 🛠️**

Ensure sensor wiring is correct and pins match code definitions 🔌.

Confirm WiFi credentials are accurate and the network is accessible 📶.

Check Blynk authentication token and template ID correctness 🔑.

Monitor serial output to identify sensor read errors 🛠️.

Restart device if it fails to connect to WiFi or Blynk 🔄.

**License 📄**

This project is open source and free to use for educational and personal purposes.

This smart irrigation and monitoring system helps maintain optimal plant health using automated control and IoT connectivity with Blynk 🌱📱💧.

For any help or enhancements, please ask!



