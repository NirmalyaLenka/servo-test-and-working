/*
 * =====================================================
 *  ATtiny85 (Digispark / standalone) + SG90
 *  Rapid Angle Change Test
 *
 *  Wiring (ATtiny85 DIP-8 pin numbers):
 *    SG90 Signal (Orange) --> PB1  (Pin 6, physical pin 6)
 *    SG90 VCC    (Red)    --> VCC  (Pin 8, physical pin 8) — use 5V external
 *    SG90 GND    (Brown)  --> GND  (Pin 4, physical pin 4)
 *
 *  ATtiny85 DIP-8 Pinout:
 *    Pin 1 = PB5 (RESET)   Pin 8 = VCC
 *    Pin 2 = PB3           Pin 7 = PB2 (SCK/SCL)
 *    Pin 3 = PB4           Pin 6 = PB1 (MISO/PWM) ← SERVO
 *    Pin 4 = GND           Pin 5 = PB0 (MOSI/SDA/PWM)
 *
 *  Digispark board (if using): PB1 = "Pin 1" label on board.
 *
 *  IMPORTANT — ATtiny85 limitations:
 *    • No hardware Serial — Serial.print() calls are commented out.
 *    • Clock: 8 MHz internal (default) or 16.5 MHz (Digispark USB).
 *    • Only 512 bytes SRAM, 8KB Flash — very constrained.
 *    • PWM-capable pins: PB0 (OC0A), PB1 (OC0B), PB4 (OC1B).
 *
 *  Board package: ATTinyCore by Spence Konde (Board Manager)
 *    URL: https://raw.githubusercontent.com/SpenceKonde/ATTinyCore/v2.0.0-devThis/package_ATTinyCore_index.json
 *  Library: Servo8Bit — install via Library Manager
 *           OR use SoftwareServo for ATtiny
 *           (search "Servo8Bit" or "SoftwareServo")
 * =====================================================
 */
#include <Servo8Bit.h>   // Lightweight servo library for ATtiny85

Servo8Bit sg90;
#define SERVO_PIN  1     // PB1 (physical pin 6)

void setup() {
  sg90.attach(SERVO_PIN);
  sg90.write(90);
  delay(1000);
}

void loop() {
  // 0 → 180 in 1 second
  sg90.write(0);
  delay(1000);
  sg90.write(180);
  delay(1000);

  // 180 → 90
  sg90.write(90);
  delay(1000);

  // 90 → 0
  sg90.write(0);
  delay(1000);

  // 0 → 90 → 180 → 90 (bounce)
  sg90.write(0);   delay(500);
  sg90.write(90);  delay(500);
  sg90.write(180); delay(500);
  sg90.write(90);  delay(500);

  // Rapid snap: 0 ↔ 180 five times
  for (int i = 0; i < 5; i++) {
    sg90.write(0);
    delay(200);
    sg90.write(180);
    delay(200);
  }

  // Back to center
  sg90.write(90);
  delay(2000);
}
