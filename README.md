# servo-test-and-working
# 🤖 ESP32 Servo Motor Test

A clean, well-commented Arduino sketch to test and calibrate servo motors with an **ESP32** microcontroller. Includes three test modes: fixed positions, center calibration, and a smooth full-range sweep.

---

## 📋 Table of Contents

- [Features](#features)
- [Hardware Requirements](#hardware-requirements)
- [Wiring](#wiring)
- [Software Requirements](#software-requirements)
- [Installation](#installation)
- [Usage](#usage)
- [Test Modes](#test-modes)
- [Configuration](#configuration)
- [Troubleshooting](#troubleshooting)
- [License](#license)

---

## ✨ Features

- ✅ Smooth sweep from 0° → 180° → 0°
- ✅ Snap to fixed positions (0°, 45°, 90°, 135°, 180°)
- ✅ Center calibration mode (90°)
- ✅ Serial Monitor logging for real-time feedback
- ✅ Configurable pulse width (supports most hobby servos)
- ✅ Safety angle clamping to protect the servo

---

## 🛒 Hardware Requirements

| Component | Quantity |
|---|---|
| ESP32 Dev Board | 1 |
| Hobby Servo Motor (SG90, MG996R, etc.) | 1 |
| External 5V Power Supply *(recommended)* | 1 |
| Jumper Wires | 3 |
| Breadboard *(optional)* | 1 |

> ⚠️ **Power Note:** Servo motors can draw significant current (especially under load). Powering the servo directly from the ESP32's 5V/VIN pin may cause voltage drops and ESP32 resets. Use a dedicated 5V supply when possible.

---

## 🔌 Wiring

```
Servo Motor         ESP32
──────────────────────────────────────
Signal (Orange/Yellow)  →  GPIO 18
VCC    (Red)            →  5V (external supply recommended)
GND    (Brown/Black)    →  GND (shared with ESP32 GND)
```
<img width="474" height="458" alt="image" src="https://github.com/user-attachments/assets/e67953eb-0290-41b0-90d1-80b893e7a299" /> 

### Wiring Diagram
<img width="600" height="316" alt="image" src="https://github.com/user-attachments/assets/ce81415a-44c8-4d97-8d6c-6c0e01e2aee6" />


```
                    ┌──────────────────┐
                    │      ESP32       │
  ┌─────────────┐   │                  │
  │ Servo Motor │   │  GPIO 18 ────────┼──── Signal (Orange)
  │             │   │                  │
  │  VCC (Red)──┼───┼── 5V (Ext.)      │
  │  GND (Blk)──┼───┼── GND ───────────┼──── GND (shared)
  └─────────────┘   └──────────────────┘
```

---

## 💾 Software Requirements

- [Arduino IDE](https://www.arduino.cc/en/software) 1.8+ or 2.x
- **ESP32 Board Package** for Arduino IDE
- **ESP32Servo** library

---

## 🚀 Installation

### 1. Add ESP32 Board Support

In Arduino IDE, go to **File → Preferences** and add this URL to *Additional Board Manager URLs*:

```
https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
```

Then go to **Tools → Board → Boards Manager**, search for `esp32`, and install the package by Espressif Systems.

### 2. Install ESP32Servo Library

Go to **Tools → Manage Libraries**, search for **ESP32Servo**, and click Install.

### 3. Clone This Repository

```bash
git clone https://github.com/your-username/esp32-servo-test.git
cd esp32-servo-test
```

### 4. Open the Sketch

Open `servo_test.ino` in the Arduino IDE.

### 5. Select Your Board

Go to **Tools → Board** and select your ESP32 board (e.g., *ESP32 Dev Module*).

### 6. Upload

Connect your ESP32 via USB, select the correct **Port**, and click **Upload** (→).

---

## 🖥️ Usage

After uploading, open the **Serial Monitor** at **115200 baud** to watch the test output in real time:

```
=================================
  ESP32 Servo Motor Test
=================================
Servo attached to GPIO 18

[Test] Center Position (90°)
  Servo position set to: 90°

[Test] Fixed Positions
  -> Moving to: 0°
  Servo position set to: 0°
  -> Moving to: 45°
  Servo position set to: 45°
  ...

[Test] Full Sweep (0° → 180° → 0°)
  Sweeping forward...
  Sweeping backward...
  Sweep complete.

--- All tests complete. Restarting in 3s ---
```

---

## 🧪 Test Modes

The sketch has three test modes. You can enable or disable each one by **commenting/uncommenting** the `#define` lines near the top of the file:

```cpp
#define TEST_SWEEP           // Full 0°–180°–0° sweep
#define TEST_FIXED_POSITIONS // Snap to fixed positions
#define TEST_CENTER          // Center calibration (90°)
```

| Mode | Description |
|---|---|
| `TEST_CENTER` | Moves servo to exactly 90° — useful for calibrating horn/arm attachment |
| `TEST_FIXED_POSITIONS` | Snaps to 0°, 45°, 90°, 135°, 180° with a pause at each |
| `TEST_SWEEP` | Slowly sweeps the full range (0° → 180° → 0°) to check for jitter or binding |

---

## ⚙️ Configuration

All key parameters are defined at the top of the sketch for easy adjustment:

```cpp
#define SERVO_PIN      18    // GPIO pin (change if needed)
#define SERVO_MIN_US   500   // Pulse width for 0°  (microseconds)
#define SERVO_MAX_US  2400   // Pulse width for 180° (microseconds)
#define STEP_DELAY_MS   15   // Speed of sweep (lower = faster)
#define HOLD_DELAY_MS 1000   // Pause time at each fixed position (ms)
```

> 💡 **Tip:** Different servo brands have different pulse ranges. If your servo doesn't reach full travel or makes noise at extremes, adjust `SERVO_MIN_US` and `SERVO_MAX_US`.

### Common Servo Pulse Ranges

| Servo | Min (µs) | Max (µs) |
|---|---|---|
| SG90 (Tower Pro) | 500 | 2400 |
| MG996R | 600 | 2200 |
| DS3218 | 500 | 2500 |
| Standard (generic) | 1000 | 2000 |

---

## 🛠️ Troubleshooting

| Problem | Likely Cause | Solution |
|---|---|---|
| Servo jitters or twitches | Insufficient power | Use external 5V supply |
| Servo doesn't move at all | Wrong pin or library | Check pin number, reinstall ESP32Servo |
| Servo only moves partially | Wrong pulse range | Adjust `SERVO_MIN_US` / `SERVO_MAX_US` |
| ESP32 keeps resetting | Servo drawing too much current | Use external supply, add 100µF capacitor across servo power |
| No Serial Monitor output | Wrong baud rate | Set Serial Monitor to 115200 baud |
| Upload fails | Wrong board selected | Set Tools → Board → ESP32 Dev Module |

---

## 📁 Project Structure

```
esp32-servo-test/
│
├── servo_test.ino   # Main Arduino sketch
└── README.md        # This file
```

---

## 📄 License

This project is released under the [MIT License](https://opensource.org/licenses/MIT). Feel free to use, modify, and distribute it.

---

## 🙌 Contributing

Pull requests are welcome! If you find a bug or want to add a new test mode, feel free to open an issue or submit a PR.

---

*Built with ❤️ for the ESP32 maker community*
