# BLINDASSIST
### Smart Assistive Helmet for the Visually Impaired

**BLINDASSIST** is an ESP32-based smart assistive helmet designed to help visually impaired individuals detect nearby obstacles and become aware of environmental conditions through intelligent audio feedback.

The system uses three ultrasonic sensors to detect obstacles from the front, left, and right directions. A DFPlayer Mini provides prerecorded voice alerts to inform the wearer about obstacle directions. Additionally, a rain sensor detects rainfall and triggers a dedicated voice warning. An active buzzer provides extra warning signals.

All electronic components are integrated into a wearable helmet, creating a portable assistive technology solution.

**Tagline:** Empowering Independence Through Intelligent Technology.

---

## 🚀 Key Features

- **Front Obstacle Detection:** Detects obstacles in front of the wearer.
- **Left Obstacle Detection:** Monitors obstacles on the left side.
- **Right Obstacle Detection:** Monitors obstacles on the right side.
- **Voice Alerts:** Provides direction-based voice notifications.
- **Rain Detection:** Detects rainfall and plays a dedicated audio warning.
- **Buzzer Alert:** Generates intermittent warning signals.
- **Smart Alert Priority:** Handles multiple detection events according to predefined priorities.
- **Wearable Design:** Integrates all electronic components into a helmet.
- **ESP32-Based Control:** Uses an ESP32 microcontroller to manage all sensors and output devices.

---

## 🛠️ Hardware Components

| Component | Quantity | Purpose |
|---|---:|---|
| ESP32 Development Board | 1 | Main controller |
| HC-SR04 Ultrasonic Sensor | 3 | Obstacle detection |
| Rain Sensor Module | 1 | Rain detection |
| DFPlayer Mini | 1 | Voice playback |
| MicroSD Card | 1 | Audio storage |
| Speaker | 1 | Voice output |
| Active Buzzer | 1 | Warning alerts |
| Smart Helmet | 1 | Wearable platform |
| Rechargeable Battery | 1 | Power supply |
| Connecting Wires | As required | Circuit connections |

---

## 🔌 ESP32 Pin Configuration

| Component | ESP32 GPIO |
|---|---|
| Front Ultrasonic TRIG | GPIO 5 |
| Front Ultrasonic ECHO | GPIO 18 |
| Left Ultrasonic TRIG | GPIO 19 |
| Left Ultrasonic ECHO | GPIO 21 |
| Right Ultrasonic TRIG | GPIO 22 |
| Right Ultrasonic ECHO | GPIO 23 |
| Rain Sensor Digital Output | GPIO 26 |
| Buzzer | GPIO 25 |
| DFPlayer RX | GPIO 17 (ESP32 TX2) |
| DFPlayer TX | GPIO 16 (ESP32 RX2) |

**Important:** HC-SR04 Echo pins typically output 5V. Use voltage dividers or logic-level converters to protect ESP32 GPIO pins.

---

## 🔊 Audio Configuration

BLINDASSIST uses a DFPlayer Mini with a microSD card to play prerecorded voice messages.

Create a folder named `MP3` in the root directory of the microSD card.

Store the following audio files inside it:

| Audio File | Function |
|---|---|
| 0001.mp3 | Front Obstacle Alert |
| 0002.mp3 | Left Obstacle Alert |
| 0003.mp3 | Right Obstacle Alert |
| 0004.mp3 | Rain Detection Alert |

The system plays the corresponding audio file when a new detection event occurs.

---

## ⚙️ Working Principle

### 1. Obstacle Detection

Three ultrasonic sensors continuously measure the distance between the wearer and nearby obstacles.

The default obstacle detection threshold is **20 cm**.

- Front obstacle detected → Front voice alert.
- Left obstacle detected → Left voice alert.
- Right obstacle detected → Right voice alert.

### 2. Rain Detection

The rain sensor monitors environmental conditions.

When rainfall is detected, the system plays the dedicated rain warning audio.

### 3. Voice Alert System

The DFPlayer Mini plays prerecorded voice messages through a connected speaker, helping the wearer identify the direction of detected obstacles.

### 4. Buzzer Warning

An intermittent buzzer alert is activated whenever an obstacle or rain detection event is active.

### 5. Alert Priority System

When multiple sensors detect objects simultaneously, the system follows this priority:

1. Rain Detection
2. Front Obstacle
3. Left Obstacle
4. Right Obstacle

This ensures that the system processes one alert at a time.

---

## 🧠 System Architecture

```text
              BLINDASSIST
                   |
                 ESP32
                   |
       +-----------+-----------+
       |           |           |
    FRONT        LEFT        RIGHT
   HC-SR04      HC-SR04      HC-SR04
       |           |           |
       +-----------+-----------+
                   |
              Sensor Data
                   |
          +--------+--------+
          |                 |
      Rain Sensor      Alert Priority
          |                 |
          +--------+--------+
                   |
          +--------+--------+
          |                 |
      DFPlayer Mini       Buzzer
          |
        Speaker
          |
     Voice Alerts
```

---

## 💻 Software Requirements

- Arduino IDE
- ESP32 Board Package
- DFRobotDFPlayerMini Library

### Required Libraries

```cpp
#include <Arduino.h>
#include <DFRobotDFPlayerMini.h>
```

---

## 📂 Repository Structure

```text
BLINDASSIST/
│
├── README.md
│
├── firmware/
│   └── BLINDASSIST_ESP32.ino
│
├── audio/
│   ├── 0001.mp3
│   ├── 0002.mp3
│   ├── 0003.mp3
│   └── 0004.mp3
│
├── images/
│   ├── helmet_front.jpg
│   ├── helmet_side.jpg
│   └── circuit_diagram.png
│
└── LICENSE
```

---

## 🔋 Future Development

Planned improvements for future versions:

- GPS-based location tracking.
- GSM-based emergency SOS notifications.
- Emergency assistance button.
- Voice-based navigation assistance.
- Improved obstacle detection range.
- Rechargeable battery management.
- Waterproof electronic enclosure.
- Additional environmental sensors.
- Advanced obstacle recognition using AI and computer vision.

---

## 🎯 Project Objective

The primary objective of BLINDASSIST is to develop an affordable and wearable assistive technology system that helps visually impaired individuals detect nearby obstacles and identify environmental conditions through audio feedback.

The project aims to improve environmental awareness, mobility assistance, and independence through embedded systems and IoT technology.

---

## Safety Disclaimer

BLINDASSIST is an experimental assistive technology prototype. It is not a replacement for a white cane, guide dog, or other established mobility aids.

Ultrasonic sensors have detection limitations and may fail to identify certain obstacles. The system should be tested carefully in controlled environments before real-world use.

---

##  Developed By

### Basirul Hasin Bitto

**Robotics | Embedded Systems | IoT | Assistive Technology**



---

**Project Name:** BLINDASSIST  
**Project Category:** Assistive Technology  
**Controller:** ESP32  
**Development Platform:** Arduino IDE

*Empowering Independence Through Intelligent Technology.*
