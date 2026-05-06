/*
 * =====================================================
 *  Seeed Studio XIAO ESP32S3 + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> D9   (GPIO9, right side pin 5)
 *    SG90 VCC    (Red)    --> 5V   (back pad "5V" or VBUS)
 *    SG90 GND    (Brown)  --> GND
 *
 *  XIAO ESP32S3 pinout (left = USB side):
 *    Left row  : D0(GPIO1), D1(GPIO2), D2(GPIO3), D3(GPIO4), D4(GPIO5), D5(GPIO6), GND
 *    Right row : 5V, 3V3, D10(GPIO10), D9(GPIO9), D8(GPIO8), D7(GPIO44), D6(GPIO43)
 *
 *  Safe servo signal pins: D0–D10 (all support PWM via LEDC)
 *  Avoid: GPIO 19/20 (USB D+/D−), GPIO 39–42 (JTAG)
 *
 *  Board package: esp32 by Espressif (Board Manager)
 *    URL: https://raw.githubusercontent.com/espressif/arduino-esp32/gh-pages/package_esp32_index.json
 *  Board selection: "XIAO_ESP32S3"
 *  Library: ESP32Servo — install via Library Manager
 * =====================================================
 */
#include <ESP32Servo.h>

Servo sg90;

#define SERVO_PIN  D9    // GPIO9
#define SG90_MIN   544   // µs — minimum pulse width (0°)
#define SG90_MAX  2400   // µs — maximum pulse width (180°)

void setup() {
  Serial.begin(115200);
  ESP32PWM::allocateTimer(0);
  sg90.setPeriodHertz(50);
  sg90.attach(SERVO_PIN, SG90_MIN, SG90_MAX);
  Serial.println("SG90 Rapid Angle Test — Seeed XIAO ESP32S3");
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
