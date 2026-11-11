# Hobby Servo Test Bench — SG90 and Compatible Servos

A collection of small firmware examples for checking hobby servo movement, pulse-width settings, and board-specific control. The primary sketch, `servo_test.ino`, targets an ESP32 and uses the ESP32Servo library. Other files provide board-specific variants and a separate SG90 demonstration.

## What is included

- Center positioning and fixed-angle tests
- A slow sweep through the commanded angle range
- A rapid angle-change sequence
- Board-specific examples for Arduino, ESP32/ESP8266, STM32, Teensy, ATtiny, and Raspberry Pi boards

A commanded angle is not a calibrated mechanical angle. Servo travel and pulse limits vary by unit; start conservatively and stop if the servo binds, buzzes continuously, or heats up.

## Hardware and power

For a basic ESP32 + SG90 test:

- ESP32 development board
- SG90 or compatible hobby servo
- Separate regulated 5 V supply with adequate current for the servo
- Three jumper wires
- USB data cable; breadboard optional

**Power rule:** Do not power a loaded servo from an ESP32 GPIO or 3.3 V pin. Use a suitable external servo supply and connect its ground to ESP32 GND so the signal has a shared reference. Size the supply for the servo's stall/current demand; larger servos such as MG996R need substantially more current than an SG90. Do not connect a supply's positive output to the ESP32 3V3 pin.

## Wiring — primary ESP32 sketch

| Servo lead | ESP32 / supply |
| --- | --- |
| Signal (often orange/yellow) | GPIO 18 |
| V+ (often red) | External regulated 5 V supply |
| GND (often brown/black) | Supply GND and ESP32 GND joined together |

Wire colors are common conventions, not a substitute for the servo's datasheet.

## Current prototype BOM

| Item | Quantity | Notes |
| --- | ---: | --- |
| ESP32 development board | 1 | Primary target of `servo_test.ino` |
| SG90 micro servo | 1 | Test one servo at a time |
| Regulated 5 V supply | 1 | Choose current capacity for the servo and load |
| Jumper wires | 3 | Signal, V+, and ground connections |
| USB data cable | 1 | Programming and Serial Monitor |
| 100–470 µF electrolytic capacitor | 1, optional | Across servo supply near the servo; observe polarity and voltage rating |
| Breadboard | 1, optional | Signal connections only; avoid routing high servo current through weak breadboard rails |

This is a bench-test BOM, not a complete robotics power system. If the servo stalls or resets the controller, improve the supply and wiring before changing software.

## Software setup

For the primary ESP32 sketch:

1. Install the [Arduino IDE](https://www.arduino.cc/en/software).
2. Install ESP32 board support using Espressif's package URL:
   `https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json`
3. Install **ESP32Servo** from Library Manager.
4. Open `servo_test.ino`, select the correct ESP32 board and port, then compile and upload.
5. Open Serial Monitor at **115200 baud**.

Other examples have different requirements. Read the header comments in the exact file before building: Python Raspberry Pi examples use GPIO libraries, Pico examples use MicroPython, and the ATtiny85 example uses Servo8Bit.

## Main sketch configuration

The ESP32 test sketch defines these defaults near the top of `servo_test.ino`:

```cpp
#define SERVO_PIN       18
#define SERVO_MIN_US   500
#define SERVO_MAX_US  2400
#define STEP_DELAY_MS   15
#define HOLD_DELAY_MS 1000
```

These pulse limits are not universal. Begin with a conservative range supported by the servo's documentation, then expand carefully if needed. Hitting mechanical end stops can damage gears or overheat the motor.

## Repository map

```text
servo-test-and-working/
├── servo_test.ino                         # Primary ESP32 test
├── rapid_angle_test.ino                   # ESP32 rapid movement sequence
├── happy_birthday_sg90.ino                # Separate servo demo
├── ATtiny85_SG90_RapidAngleTest.ino       # ATtiny85 / Servo8Bit
├── ArduinoUno_SG90_RapidAngleTest.ino     # Arduino Uno
├── ArduinoNano_SG90_RapidAngleTest.ino    # Arduino Nano
├── ArduinoMega2560_SG90_RapidAngleTest.ino# Arduino Mega 2560
├── ArduinoProMini_SG90_RapidAngleTest.ino # Arduino Pro Mini
├── ESP32-C3_SG90_RapidAngleTest.ino       # ESP32-C3
├── NodeMCU_ESP8266_SG90_RapidAngleTest.ino# ESP8266 NodeMCU
├── WemosD1Mini_SG90_RapidAngleTest.ino    # Wemos D1 mini
├── STM32BluePill_SG90_RapidAngleTest.ino  # STM32 Blue Pill
├── SeeedXIAO_ESP32S3_SG90_RapidAngleTest.ino # XIAO ESP32-S3
├── Teensy40_SG90_RapidAngleTest.ino       # Teensy 4.0
├── RaspberryPi4B_SG90_RapidAngleTest.py   # Raspberry Pi GPIO / Python
├── RaspberryPiPico_SG90_RapidAngleTest.py # Raspberry Pi Pico / MicroPython
├── RaspberryPiPicoW_SG90_RapidAngleTest.py# Raspberry Pi Pico W / MicroPython
└── README.md                              # Setup, power, file map, and limitations
```

Each Arduino sketch is a separate alternative. Before reorganizing these files into folders, place each sketch in a directory matching its primary `.ino` filename so it opens cleanly in Arduino IDE.

## Troubleshooting

| Symptom | Likely cause / check |
| --- | --- |
| Servo jitters or ESP32 resets | Supply current, shared ground, and wiring; use a separate servo supply |
| Servo does not move | Signal pin, board selection, correct library, and servo power |
| Servo buzzes at an endpoint | Pulse range exceeds the servo's mechanical travel; reduce min/max limits |
| Movement is reversed | Servo orientation or mechanical linkage; do not assume all assemblies are identical |
| Python example cannot access GPIO | Install the library for the exact Raspberry Pi OS/Python environment and check permissions |

## Limitations

- These sketches are open-loop tests; there is no position feedback from the servo.
- A reported angle is the commanded angle, not a measured shaft position.
- No universal pulse-width calibration is valid for every SG90 clone or other servo.
- Power and mechanical safety must be validated on the actual setup.

## Skills and technologies

`Embedded C++` · `MicroPython` · `ESP32` · `Arduino` · `PWM` · `Servo control` · `Power integrity`

## Maintenance & audit

- **Last updated:** 11 November 2026
- **Review scope:** File paths, primary entry point, setup steps, servo power safety, and current BOM.
- **Documentation changes:** Corrected the primary-sketch guidance, removed the placeholder clone URL, and made the external servo supply/common-ground requirements explicit.
- **Firmware status:** No firmware changes were made. The board variants have not been compiled or hardware-tested during this pass.
- **License:** No `LICENSE` file was found in the root listing; no specific reuse license is claimed here.
