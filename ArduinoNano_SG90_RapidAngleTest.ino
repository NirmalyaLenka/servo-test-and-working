/*
 * =====================================================
 *  Arduino Nano + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> D9  (PWM ~)
 *    SG90 VCC    (Red)    --> 5V  (or VIN if USB-powered)
 *    SG90 GND    (Brown)  --> GND
 *
 *  PWM-capable pins on Nano: D3, D5, D6, D9, D10, D11
 *  Library: Built-in <Servo.h> (no install needed)
 *
 *  WARNING: Nano's 5V pin from USB (~500mA max) may
 *  brownout under servo load. Use external 5V if needed.
 * =====================================================
 */
#include <Servo.h>

Servo sg90;
#define SERVO_PIN  9

void setup() {
  Serial.begin(9600);
  sg90.attach(SERVO_PIN, 544, 2400);  // SG90 pulse range: 544µs – 2400µs
  Serial.println("SG90 Rapid Angle Test — Arduino Nano");
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
