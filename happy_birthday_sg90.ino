/*
 * =====================================================
 *  ESP32 + SG90 Servo — Happy Birthday To You
 *  Perfectly tuned for SG90 gear noise music
 *
 *  Wiring:
 *    SG90 Signal (Orange) --> GPIO 18
 *    SG90 VCC    (Red)    --> 5V external supply
 *    SG90 GND    (Brown)  --> GND (common with ESP32)
 *
 *  Library: ESP32Servo
 *    Arduino IDE -> Library Manager -> "ESP32Servo"
 * =====================================================
 */

#include <ESP32Servo.h>

Servo sg90;

#define SERVO_PIN   18
#define BPM         80       // Slower = cleaner gear articulation

// SG90 safe pulse range
#define SG90_MIN   544
#define SG90_MAX  2400

// Toggle amplitude — SG90 sounds best at 5-7
// Too high = servo strain, too low = inaudible
#define AMP  6

// Note durations based on BPM
#define WHOLE        (60000 / BPM * 4)
#define HALF         (WHOLE / 2)
#define QUARTER      (WHOLE / 4)
#define EIGHTH       (WHOLE / 8)
#define D_QUARTER    (QUARTER + EIGHTH)   // dotted quarter
#define D_EIGHTH     (EIGHTH  + (EIGHTH/2)) // dotted eighth

// Musical note frequencies (Hz)
#define C4  262
#define D4  294
#define E4  330
#define F4  349
#define G4  392
#define A4  440
#define B4  494
#define C5  523
#define REST  0

// ─────────────────────────────────────────────────────
// Happy Birthday to You — full song, correct melody
// {note, duration_ms}
// ─────────────────────────────────────────────────────
int song[][2] = {
  // "Happy birth-day to you"
  {C4, D_EIGHTH}, {C4, EIGHTH/2}, {D4, QUARTER}, {C4, QUARTER}, {F4, QUARTER}, {E4, HALF},

  // "Happy birth-day to you"
  {C4, D_EIGHTH}, {C4, EIGHTH/2}, {D4, QUARTER}, {C4, QUARTER}, {G4, QUARTER}, {F4, HALF},

  // "Happy birth-day dear [name]"
  {C4, D_EIGHTH}, {C4, EIGHTH/2}, {C5, QUARTER}, {A4, QUARTER}, {F4, QUARTER}, {E4, QUARTER}, {D4, HALF},

  // "Happy birth-day to you"
  {A4, D_EIGHTH}, {A4, EIGHTH/2}, {A4, QUARTER}, {F4, QUARTER}, {G4, QUARTER}, {F4, WHOLE},
};

int noteCount = sizeof(song) / sizeof(song[0]);

// ─────────────────────────────────────────────────────
// Play one note by toggling servo at the note frequency
// ─────────────────────────────────────────────────────
void playNote(int freq, int durationMs) {
  if (freq == REST) {
    sg90.write(90);
    delay(durationMs);
    return;
  }

  int hi = 90 + AMP;
  int lo = 90 - AMP;

  // Half-period in microseconds
  unsigned long halfUs = 500000UL / freq;

  unsigned long endMs = millis() + (unsigned long)durationMs;
  while (millis() < endMs) {
    sg90.write(hi);
    delayMicroseconds(halfUs);
    sg90.write(lo);
    delayMicroseconds(halfUs);
  }
}

// ─────────────────────────────────────────────────────
void setup() {
  Serial.begin(115200);

  ESP32PWM::allocateTimer(0);
  sg90.setPeriodHertz(50);
  sg90.attach(SERVO_PIN, SG90_MIN, SG90_MAX);

  // Center servo and settle
  sg90.write(90);
  delay(800);

  Serial.println("Playing: Happy Birthday To You");
}

// ─────────────────────────────────────────────────────
void loop() {
  for (int i = 0; i < noteCount; i++) {
    int freq     = song[i][0];
    int duration = song[i][1];

    // Play note at 88% duration, 12% gap for note separation
    playNote(freq, duration * 0.88);
    sg90.write(90);
    delay(duration * 0.12);
  }

  // Return to center, pause, then repeat
  sg90.write(90);
  delay(4000);
}
