/*
 * =====================================================
 *  NodeMCU ESP8266 (v1/v2/v3) + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> D4  (GPIO2, PWM)
 *    SG90 VCC    (Red)    --> VIN (5V from USB)  ← NOT 3.3V
 *    SG90 GND    (Brown)  --> GND
 *
 *  ESP8266 NodeMCU D-pin → GPIO mapping:
 *    D0=GPIO16, D1=GPIO5,  D2=GPIO4,  D3=GPIO0
 *    D4=GPIO2,  D5=GPIO14, D6=GPIO12, D7=GPIO13, D8=GPIO15
 *
 *  Board package: esp8266 by ESP8266 Community (Board Manager)
 *  Library: ESP8266 Servo  →  install via Library Manager
 *           (search "ESP8266Servo" by Kevin Harrington)
 *
 *  Note: All ESP8266 GPIO are 3.3V. SG90 signal is fine at 3.3V.
 *        Avoid GPIO0, GPIO2, GPIO15 during boot (used for boot mode).
 *        D5 (GPIO14) is a safer choice if D4 causes boot issues.
 * =====================================================
 */
#include <ESP8266Servo.h>

Servo sg90;
#define SERVO_PIN  D4   // GPIO2

void setup() {
  Serial.begin(115200);
  sg90.attach(SERVO_PIN, 544, 2400);  // SG90 pulse range: 544µs – 2400µs
  Serial.println("SG90 Rapid Angle Test — NodeMCU ESP8266");
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
