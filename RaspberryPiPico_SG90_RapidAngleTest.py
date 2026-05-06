# =====================================================
#  Raspberry Pi Pico + SG90 — Rapid Angle Change Test
#  Language: MicroPython
#
#  Wiring:
#    SG90 Signal (Orange) --> GP15  (any GP pin works)
#    SG90 VCC    (Red)    --> VBUS (5V, Pin 40) or 3V3
#    SG90 GND    (Brown)  --> GND  (Pin 38 or any GND)
#
#  Pinout reference (physical pin → GP):
#    Pin 20 = GP15
#    Pin 40 = VBUS (5V from USB)
#    Pin 38 = GND
#
#  Note: SG90 runs fine at 3.3V signal level from Pico.
#        For power, prefer VBUS (5V) over 3V3 for torque.
#  Flash MicroPython firmware first:
#    https://micropython.org/download/rp2-pico/
# =====================================================

from machine import Pin, PWM
import time

SERVO_PIN = 15          # GP15
PWM_FREQ  = 50          # 50 Hz (20 ms period)

SG90_MIN_US = 544       # Pulse for 0°
SG90_MAX_US = 2400      # Pulse for 180°

servo = PWM(Pin(SERVO_PIN))
servo.freq(PWM_FREQ)

def angle_to_duty(angle: int) -> int:
    """Convert 0–180° to a 16-bit duty cycle value."""
    pulse_us = SG90_MIN_US + (SG90_MAX_US - SG90_MIN_US) * angle // 180
    # PWM period = 1_000_000 / 50 Hz = 20_000 µs
    return int(pulse_us / 20_000 * 65535)

def write_angle(angle: int):
    servo.duty_u16(angle_to_duty(angle))

# ── Setup ──────────────────────────────────────────
print("SG90 Rapid Angle Test — Raspberry Pi Pico")
write_angle(90)
time.sleep(1)

# ── Main loop ──────────────────────────────────────
while True:
    # 0 → 180 in 1 second
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
