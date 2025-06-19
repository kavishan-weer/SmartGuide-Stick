# 👨‍🦯 Smart Guide Stick for the Visually Impaired

An IoT-based **Smart Guide Stick** built using **ESP32**, designed to assist visually impaired individuals in navigating obstacles and emergencies with real-time haptic feedback and GPS-based location sharing via **Telegram**.

## 🎯 Features

- 📡 **GPS Tracking** using TinyGPS++
- 📏 **Obstacle Detection** using 3 Ultrasonic Sensors
- 🤝 **Haptic Feedback** via Vibration Motors for Nearby Obstacles
- 🛎️ **Emergency Button** triggers:
  - 📍 Sends real-time **Google Maps location** via Telegram
  - 🔊 Audible **Buzzer alert**
- 🔐 Secure Wi-Fi + SSL communication with **Telegram Bot**

---

## 🧰 Hardware Components

| Component               | Purpose                              |
|------------------------|--------------------------------------|
| ESP32 Dev Module       | Microcontroller (Wi-Fi + BT + UART) |
| 3 × HC-SR04            | Obstacle detection (front/sides)     |
| 3 × Vibration Motors   | Haptic feedback                      |
| GPS Module (e.g., NEO-6M) | Location tracking                   |
| Push Button            | Emergency alert trigger              |
| Buzzer                 | Audio alert during SOS               |
| Jumper wires, Battery, Stick Mounting Hardware | Supportive components |

---

## ⚙️ Pin Configuration

| Function         | ESP32 Pin |
|------------------|-----------|
| GPS RX           | GPIO 16   |
| GPS TX           | GPIO 17   |
| Ultrasonic 1     | TRIG: 2, ECHO: 4  |
| Ultrasonic 2     | TRIG: 12, ECHO: 14 |
| Ultrasonic 3     | TRIG: 26, ECHO: 27 |
| Vibrator 1       | GPIO 5     |
| Vibrator 2       | GPIO 18    |
| Vibrator 3       | GPIO 19    |
| Push Button      | GPIO 21    |
| Buzzer           | GPIO 22    |

---

## 🔧 How It Works

- Each ultrasonic sensor measures the distance to nearby obstacles.
- If any object is detected within **30 cm**, the corresponding vibration motor is activated.
- GPS constantly tracks the location.
- When the emergency button is pressed:
  - A **Google Maps link** is sent to a predefined Telegram chat.
  - The buzzer emits an audible alert pattern.

---

## 📲 Telegram Integration

- Uses **UniversalTelegramBot** and **WiFiClientSecure**
- You must create a Telegram bot via [@BotFather](https://t.me/botfather)
- Get your **Bot Token** and use your **chat ID**

