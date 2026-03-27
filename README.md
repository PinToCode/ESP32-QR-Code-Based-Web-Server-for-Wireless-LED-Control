# ESP32 QR Web Server LED Control

## Overview

This project uses an ESP32 to host a local web server for controlling an LED.
A QR code is displayed on an OLED screen, which contains the ESP32's IP address.
By scanning the QR code, users can instantly open the control webpage on their smartphone.

---

## Features

*  WiFi-based control
*  Local web server (no internet required)
*  QR code for quick access
*  OLED display (SH1106)
*  LED ON/OFF control from browser

---

## Hardware Required

* ESP32
* OLED Display (SH1106, I2C)
* LED
* 220Ω Resistor
* Breadboard & jumper wires

---

##  Connections

| Component | ESP32 Pin |
| --------- | --------- |
| OLED SDA  | GPIO 21   |
| OLED SCL  | GPIO 22   |
| LED       | GPIO 13   |

---

##  QR Code Library Setup

To generate the QR code, you need to manually include the required library files:

* Copy the following files from the QR code library:

  * `qrcode.c`
  * `qrcode.h`

* Keep the file names exactly as:

  * `qr_gen.c`
  * `qr_gen.h`

* Place both files inside your Arduino project folder
  (same location as your `.ino` file)

 **Important:**
These files are not installed via the Arduino Library Manager, so they must be added manually.

---

##  Working

1. ESP32 connects to WiFi
2. A web server is started on the ESP32
3. The device IP address is converted into a QR code
4. QR code is displayed on the OLED screen
5. Scan the QR code using your phone
6. Webpage opens → Control LED instantly

---

##  Output

(Add images inside `/images` folder)

* OLED showing QR code
* Circuit setup
* Web control page

---

##  Setup Instructions

1. Install Arduino IDE

2. Install required libraries:

   * WiFi (built-in)
   * WebServer (built-in)
   * Adafruit GFX
   * Adafruit SH110X

3. Add QR files (`qr_gen.c` and `qr_gen.h`) to project folder

4. Update WiFi credentials in code:

   ```cpp
   const char* ssid = "YOUR_SSID";
   const char* password = "YOUR_PASSWORD";
   ```

5. Upload code to ESP32

6. Open Serial Monitor (115200 baud)

7. Scan QR code displayed on OLED

8. Control LED from your browser 

---

##  Future Improvements

* Control multiple devices
* Add sensor monitoring dashboard
* Add authentication/login system
* Remote access using MQTT or cloud

---

##  Author

Jerit Jose

---
