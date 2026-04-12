/*
 * =====================================================
 *  ESP32 Servo Motor Test
 *  Microcontroller: ESP32
 *  Library: ESP32Servo
 * =====================================================
 *
 *  Wiring:
 *    Servo Signal (Orange/Yellow) --> GPIO 18
 *    Servo VCC    (Red)           --> 5V (external supply recommended)
 *    Servo GND    (Brown/Black)   --> GND (common ground with ESP32)
 *
 *  Install Library:
 *    Arduino IDE -> Library Manager -> Search "ESP32Servo" -> Install
 * =====================================================
 */

#include <ESP32Servo.h>

// ── Pin Configuration ─────────────────────────────────
#define SERVO_PIN   18        // GPIO pin connected to servo signal wire

// ── Servo Parameters ──────────────────────────────────
#define SERVO_MIN_US   500    // Minimum pulse width in microseconds (0°)
#define SERVO_MAX_US  2400    // Maximum pulse width in microseconds (180°)
#define STEP_DELAY_MS   15   // Delay between each degree step (ms)
#define HOLD_DELAY_MS  1000  // Hold time at endpoints (ms)

// ── Servo Object ──────────────────────────────────────
Servo myServo;

// ── Test Modes ────────────────────────────────────────
// Comment/uncomment to select which tests run
#define TEST_SWEEP          // Full 0°–180°–0° sweep
#define TEST_FIXED_POSITIONS // Snap to fixed positions
#define TEST_CENTER         // Center calibration (90°)


// ─────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);
  delay(500);

  Serial.println("=================================");
  Serial.println("  ESP32 Servo Motor Test");
  Serial.println("=================================");

  // Allocate a timer for the servo
  ESP32PWM::allocateTimer(0);

  // Attach servo with custom pulse width range
  myServo.setPeriodHertz(50);                    // Standard 50Hz servo
  myServo.attach(SERVO_PIN, SERVO_MIN_US, SERVO_MAX_US);

  Serial.print("Servo attached to GPIO ");
  Serial.println(SERVO_PIN);
  Serial.println();
}


// ─────────────────────────────────────────────────────
void loop() {

#ifdef TEST_CENTER
  testCenter();
#endif

#ifdef TEST_FIXED_POSITIONS
  testFixedPositions();
#endif

#ifdef TEST_SWEEP
  testSweep();
#endif

  Serial.println("\n--- All tests complete. Restarting in 3s ---\n");
  delay(3000);
}


// ─────────────────────────────────────────────────────
// TEST 1: Move to center (90°) — good for calibration
// ─────────────────────────────────────────────────────
void testCenter() {
  Serial.println("[Test] Center Position (90°)");
  moveToAngle(90);
  delay(HOLD_DELAY_MS);
}


// ─────────────────────────────────────────────────────
// TEST 2: Snap to fixed positions
// ─────────────────────────────────────────────────────
void testFixedPositions() {
  Serial.println("[Test] Fixed Positions");

  int positions[] = {0, 45, 90, 135, 180};
  int count = sizeof(positions) / sizeof(positions[0]);

  for (int i = 0; i < count; i++) {
    Serial.print("  -> Moving to: ");
    Serial.print(positions[i]);
    Serial.println("°");
    moveToAngle(positions[i]);
    delay(HOLD_DELAY_MS);
  }
}


// ─────────────────────────────────────────────────────
// TEST 3: Smooth sweep 0° → 180° → 0°
// ─────────────────────────────────────────────────────
void testSweep() {
  Serial.println("[Test] Full Sweep (0° → 180° → 0°)");

  // Sweep forward
  Serial.println("  Sweeping forward...");
  for (int angle = 0; angle <= 180; angle++) {
    myServo.write(angle);
    delay(STEP_DELAY_MS);
  }

  delay(HOLD_DELAY_MS);

  // Sweep backward
  Serial.println("  Sweeping backward...");
  for (int angle = 180; angle >= 0; angle--) {
    myServo.write(angle);
    delay(STEP_DELAY_MS);
  }

  delay(HOLD_DELAY_MS);
  Serial.println("  Sweep complete.");
}


// ─────────────────────────────────────────────────────
// Helper: Move to a specific angle and log it
// ─────────────────────────────────────────────────────
void moveToAngle(int angle) {
  angle = constrain(angle, 0, 180);   // Safety clamp
  myServo.write(angle);
  Serial.print("  Servo position set to: ");
  Serial.print(angle);
  Serial.println("°");
  delay(500);   // Allow servo time to physically reach position
}
