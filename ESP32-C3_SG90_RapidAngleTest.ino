/*
 * =====================================================
 *  ESP32-C3 + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> GPIO 5
 *    SG90 VCC    (Red)    --> 5V  (external supply or VBUS)
 *    SG90 GND    (Brown)  --> GND
 *
 *  ESP32-C3 GPIO notes:
 *    • RISC-V single-core, 3.3V GPIO logic.
 *    • Available GPIO: 0–10 (11 total), plus 18–21 on some modules.
 *    • GPIO 8 has internal pull-up for boot mode — use carefully.
 *    • GPIO 9 = boot button on many dev boards (active LOW).
 *    • Safe PWM output pins: 0, 1, 2, 3, 4, 5, 6, 7, 10.
 *    • SG90 signal works fine at 3.3V logic.
 *    • Power SG90 VCC from 5V — NOT from 3.3V pin.
 *
 *  Board package: esp32 by Espressif (Board Manager)
 *    URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 *  Board selection: "ESP32C3 Dev Module"
 *  Library: ESP32Servo — install via Library Manager
 * =====================================================
 */
#include <ESP32Servo.h>

Servo sg90;

#define SERVO_PIN   5
#define SG90_MIN  544    // µs — minimum pulse width (0°)
#define SG90_MAX  2400   // µs — maximum pulse width (180°)

void setup() {
  Serial.begin(115200);
  ESP32PWM::allocateTimer(0);
  sg90.setPeriodHertz(50);
  sg90.attach(SERVO_PIN, SG90_MIN, SG90_MAX);
  Serial.println("SG90 Rapid Angle Test — ESP32-C3");
  sg90.write(90);
  delay(1000);
}

void loop() {
  // 0 → 180 in 1 second
  Serial.println("0 → 180");
  sg90.write(0);
  delay(1000);
  sg90.write(180);
  delay(1000);

  // 180 → 90
  Serial.println("180 → 90");
  sg90.write(90);
  delay(1000);

  // 90 → 0
  Serial.println("90 → 0");
  sg90.write(0);
  delay(1000);

  // 0 → 90 → 180 → 90 (bounce)
  Serial.println("Bounce: 0 → 90 → 180 → 90");
  sg90.write(0);   delay(500);
  sg90.write(90);  delay(500);
  sg90.write(180); delay(500);
  sg90.write(90);  delay(500);

  // Rapid snap: 0 ↔ 180 five times
  Serial.println("Rapid snap x5");
  for (int i = 0; i < 5; i++) {
    sg90.write(0);
    delay(200);
    sg90.write(180);
    delay(200);
  }

  // Back to center
  Serial.println("Center → pause");
  sg90.write(90);
  delay(2000);
}
