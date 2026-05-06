/*
 * =====================================================
 *  STM32F103C8T6 (Blue Pill) + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> PA8   (Timer 1 CH1 — hardware PWM)
 *    SG90 VCC    (Red)    --> 5V    (from USB or external supply)
 *    SG90 GND    (Brown)  --> GND
 *
 *  Board: "Generic STM32F1 series" in Arduino IDE
 *  Core: STM32duino (https://github.com/stm32duino/Arduino_Core_STM32)
 *  Library: Built-in <Servo.h> from STM32duino core
 *
 *  Other usable PWM pins: PA0, PA1, PA2, PA3, PA6, PA7,
 *                         PB0, PB1, PB6, PB7, PB8, PB9
 *
 *  Note: STM32 GPIO is 3.3V — SG90 signal works fine at 3.3V.
 *        Do NOT power SG90 from the 3.3V pin; use 5V.
 * =====================================================
 */
#include <Servo.h>

Servo sg90;
#define SERVO_PIN  PA8

void setup() {
  Serial.begin(115200);
  sg90.attach(SERVO_PIN, 544, 2400);  // SG90 pulse range: 544µs – 2400µs
  Serial.println("SG90 Rapid Angle Test — STM32 Blue Pill");
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
