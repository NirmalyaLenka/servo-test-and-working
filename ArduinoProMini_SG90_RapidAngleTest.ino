/*
 * =====================================================
 *  Arduino Pro Mini (3.3V / 5V) + SG90 — Rapid Angle Change Test
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> Pin 9  (PWM ~)
 *    SG90 VCC    (Red)    --> VCC    (use 5V version of Pro Mini)
 *    SG90 GND    (Brown)  --> GND
 *
 *  PWM-capable pins: 3, 5, 6, 9, 10, 11
 *
 *  IMPORTANT — Power notes:
 *    • Use the 5V/16MHz Pro Mini variant for best servo torque.
 *    • On 3.3V/8MHz variant: SG90 signal works but VCC (3.3V)
 *      may not provide enough current — use an external 5V supply
 *      for SG90 VCC and share only GND with the board.
 *    • Pro Mini has NO USB; program via FTDI/USB-to-Serial adapter:
 *        FTDI TX  --> Pro Mini RX
 *        FTDI RX  --> Pro Mini TX
 *        FTDI GND --> Pro Mini GND
 *        FTDI VCC --> Pro Mini VCC  (match voltages!)
 *        FTDI DTR --> Pro Mini DTR (auto-reset)
 *
 *  Board: "Arduino Pro or Pro Mini" in Arduino IDE
 *  Library: Built-in <Servo.h> (no install needed)
 * =====================================================
 */
#include <Servo.h>

Servo sg90;
#define SERVO_PIN  9

void setup() {
  Serial.begin(9600);
  sg90.attach(SERVO_PIN, 544, 2400);  // SG90 pulse range: 544µs – 2400µs
  Serial.println("SG90 Rapid Angle Test — Arduino Pro Mini");
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
