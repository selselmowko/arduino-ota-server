# 🚀 Nexus Autonomous Wireless Dashboard

A smart, standalone multi-tool dashboard built on the **Arduino Uno R4 WiFi** architecture. This project uses a **1.3" I2C OLED (SH1106)** display and a custom-built Over-The-Air (OTA) firmware selection menu. 

Twisting a physical potentiometer dial allows you to browse multiple sensor profiles. Pressing the Enter key triggers the Arduino to autonomously pull, verify, download, and flash that specific `.bin` software application directly from this GitHub server completely wire-free!

---

## 🛠️ Hardware Component Wiring

### 1. 🎛️ Potentiometer (Menu Scroll Dial)
*   **Left Pin:** Connect to Arduino **GND**
*   **Middle Pin:** Connect to Arduino Analog Input **`A0`**
*   **Right Pin:** Connect to Arduino **`5V`**

### 2. 🟥 Physical Pushbutton (Enter / Flash Key)
*   **Leg 1:** Connect to Arduino Digital Pin **`D2`**
*   **Leg 2:** Connect to Arduino **GND** *(Uses internal `INPUT_PULLUP`)*

### 3. 📺 1.3" I2C OLED Display (128x64)
*   **VCC** ➡️ Arduino **3.3V** or **5V**
*   **GND** ➡️ Arduino **GND**
*   **SDA** ➡️ Arduino Analog Pin **`A4`**
*   **SCL** ➡️ Arduino Analog Pin **`A5`**

---

## 📂 Included Firmware Applications (.bin)

This repository hosts 4 independent sensor profiles divided across the potentiometer's rotation sweep (0 to 1023):

1.  **`dht22_weather.bin` (Zone: 0 - 255):** Tracks temperature and humidity using a DHT22 sensor on **Digital Pin D4**.
2.  **`sonar_radar.bin` (Zone: 256 - 511):** Displays physical distance metrics in centimeters using an HC-SR04 sonar sensor on **Pins D5 & D6**.
3.  **`ldr_light.bin` (Zone: 512 - 767):** Measures ambient room light percentage using an Analog LDR sensor on **Analog Pin A1**.
4.  **`soil_moisture.bin` (Zone: 768 - 1023):** Tracks plant soil saturation percentages using a moisture sensor on **Analog Pin A1**.

---

## 🔄 The Multi-Tool Navigation Workflow

1.  **Scroll:** Twist the potentiometer knob to slide 1-by-1 through the sensor profile cards displayed on the 1.3" OLED screen.
2.  **Flash:** Press the pushbutton on Pin D2. The screen displays a **0% to 100% loading progress bar**, downloads the matching `.bin` file from GitHub over Wi-Fi, and reboots into that sensor app.
3.  **Exit:** Twist the potentiometer dial out of that specific application's numeric zone. The code triggers a **Software Reset Exit (`SystemReset`)** to boot the Arduino instantly back into the main Master Selection Menu!

---

## ⚠️ Network Troubleshooting Guide

If your Arduino gets stuck or fails to download a firmware file over the travel router network, check these common fixes:

### 1. Stuck on "Connecting Wi-Fi..."
*   **Issue:** The Arduino cannot find your travel router.
*   **Fix:** Ensure your **GL-MT300N-V2-a01** travel router is powered on and within range. Double-check that your router's **2.4GHz** wireless band is active, as the Arduino Uno R4 does not support 5GHz networks.

### 2. Download Progress Bar Sticks at 0% or Fails
*   **Issue:** The Arduino connected to the router but cannot access the internet to download from GitHub.
*   **Fix:** Ensure your travel router actually has an active internet connection (e.g., via an ethernet cable or bridged to your phone's hotspot). If the router has no internet link, the Arduino cannot fetch the cloud files.
*   **Path Check:** Verify that the GitHub username and repository name inside your Master Menu code exactly match your live GitHub URL. A single typo will block the download.

### 3. Screen Flickers or Jumps Between Menus
*   **Issue:** Raw electrical noise or a loose wire on the potentiometer signal.
*   **Fix:** Ensure the middle leg of your potentiometer is firmly seated in Analog Pin **A0**. If it still jumps, check your ground (GND) wire connection to ensure clean voltage readings.
