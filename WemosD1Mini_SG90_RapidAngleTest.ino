/*
 * =====================================================
 *  Wemos D1 Mini (ESP8266) + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> D6  (GPIO12)
 *    SG90 VCC    (Red)    --> 5V  (top-left pin, from USB)
 *    SG90 GND    (Brown)  --> G   (GND)
 *
 *  D1 Mini D-pin → GPIO mapping:
 *    D0 = GPIO16  D1 = GPIO5   D2 = GPIO4   D3 = GPIO0*
 *    D4 = GPIO2*  D5 = GPIO14  D6 = GPIO12  D7 = GPIO13
 *    D8 = GPIO15*
 *    (* = boot-mode sensitive — avoid for servo signal)
 *
 *  Recommended servo pins: D5 (GPIO14), D6 (GPIO12), D7 (GPIO13)
 *
 *  Board package: esp8266 by ESP8266 Community (Board Manager)
 *    URL: https://arduino.esp8266.com/stable/package_esp8266com_index.json
 *  Board selection: "LOLIN(WEMOS) D1 R2 & mini"
 *  Library: ESP8266Servo — install via Library Manager
 *           (search "ESP8266Servo" by Kevin Harrington)
 *
 *  Note: All GPIO are 3.3V logic — SG90 signal works fine.
 *        Do NOT power SG90 from 3V3 pin; use 5V pin.
 * =====================================================
 */
#include <ESP8266Servo.h>

Servo sg90;
#define SERVO_PIN  D6   // GPIO12

void setup() {
  Serial.begin(115200);
  sg90.attach(SERVO_PIN, 544, 2400);  // SG90 pulse range: 544µs – 2400µs
  Serial.println("SG90 Rapid Angle Test — Wemos D1 Mini");
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
