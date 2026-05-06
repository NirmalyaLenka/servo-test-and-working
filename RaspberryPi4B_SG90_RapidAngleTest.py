#!/usr/bin/env python3
# =====================================================
#  Raspberry Pi (3B / 4B / Zero 2W) + SG90
#  Rapid Angle Change Test
#  Language: Python 3 + RPi.GPIO (hardware PWM via pigpio optional)
#
#  Wiring:
#    SG90 Signal (Orange) --> GPIO 18  (Pin 12, hardware PWM0)
#    SG90 VCC    (Red)    --> Pin 2 or Pin 4  (5V supply)
#    SG90 GND    (Brown)  --> Pin 6 (or any GND pin)
#
#  RPi GPIO header (BCM numbering):
#    Pin 12 = GPIO 18 (PWM0) ← recommended for servo
#    Pin  2 = 5V
#    Pin  6 = GND
#
#  Install dependencies (once):
#    sudo apt update
#    sudo apt install python3-rpi.gpio
#
#  Run:
#    sudo python3 RaspberryPi_SG90_RapidAngleTest.py
#  (sudo required for GPIO access)
#
#  NOTE: For smoother PWM use pigpio instead of RPi.GPIO:
#    sudo apt install pigpio python3-pigpio
#    sudo pigpiod
#    Then replace RPi.GPIO calls with pigpio equivalents.
# =====================================================

import RPi.GPIO as GPIO
import time

SERVO_PIN   = 18     # BCM GPIO 18 (hardware PWM0)
PWM_FREQ    = 50     # 50 Hz

# SG90 duty cycle range for RPi.GPIO software PWM (percentage):
#   0°  → 544µs  / 20000µs × 100 ≈ 2.72 %
#   90° → 1472µs / 20000µs × 100 ≈ 7.36 %
#  180° → 2400µs / 20000µs × 100 ≈ 12.0 %
SG90_MIN_DC = 2.72
SG90_MAX_DC = 12.0

def angle_to_dc(angle: int) -> float:
    """Convert 0–180° to duty cycle percentage."""
    return SG90_MIN_DC + (SG90_MAX_DC - SG90_MIN_DC) * angle / 180.0

GPIO.setmode(GPIO.BCM)
GPIO.setup(SERVO_PIN, GPIO.OUT)

pwm = GPIO.PWM(SERVO_PIN, PWM_FREQ)
pwm.start(angle_to_dc(90))   # Start at 90° (center)

def write_angle(angle: int):
    pwm.ChangeDutyCycle(angle_to_dc(angle))

# ── Setup ──────────────────────────────────────────
print("SG90 Rapid Angle Test — Raspberry Pi")
write_angle(90)
time.sleep(1)

# ── Main loop ──────────────────────────────────────
try:
    while True:
        # 0 → 180
        print("0 → 180")
        write_angle(0);   time.sleep(1)
        write_angle(180); time.sleep(1)

        # 180 → 90
        print("180 → 90")
        write_angle(90);  time.sleep(1)

        # 90 → 0
        print("90 → 0")
        write_angle(0);   time.sleep(1)

        # Bounce: 0 → 90 → 180 → 90
        print("Bounce: 0 → 90 → 180 → 90")
        write_angle(0);   time.sleep(0.5)
        write_angle(90);  time.sleep(0.5)
        write_angle(180); time.sleep(0.5)
        write_angle(90);  time.sleep(0.5)

        # Rapid snap: 0 ↔ 180 five times
        print("Rapid snap x5")
        for _ in range(5):
            write_angle(0);   time.sleep(0.2)
            write_angle(180); time.sleep(0.2)

        # Back to center
        print("Center → pause")
        write_angle(90)
        time.sleep(2)

except KeyboardInterrupt:
    print("\nStopped by user.")

finally:
    pwm.stop()
    GPIO.cleanup()
    print("GPIO cleaned up.")
