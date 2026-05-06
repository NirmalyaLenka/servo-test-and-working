# =====================================================
#  Raspberry Pi Pico W + SG90 — Rapid Angle Change Test
#  Language: MicroPython
#
#  Wiring:
#    SG90 Signal (Orange) --> GP15  (Pin 20)
#    SG90 VCC    (Red)    --> VBUS  (Pin 40 — 5V from USB)
#    SG90 GND    (Brown)  --> GND   (Pin 38 or any GND pin)
#
#  Pico W physical pin map (relevant pins):
#    Pin 20 = GP15 (PWM channel 7B)
#    Pin 40 = VBUS (5V USB supply)
#    Pin 38 = GND
#
#  Note: Pico W adds CYW43439 WiFi/BT chip on GP23/GP24/GP25/GP29
#        but GP15 is completely free.
#  WiFi is NOT used in this sketch — purely servo control.
#
#  Flash MicroPython for Pico W:
#    https://micropython.org/download/rp2-pico-w/
# =====================================================

from machine import Pin, PWM
import time

SERVO_PIN   = 15       # GP15
PWM_FREQ    = 50       # 50 Hz → 20 ms period

SG90_MIN_US = 544      # Pulse width for 0°
SG90_MAX_US = 2400     # Pulse width for 180°
PERIOD_US   = 20_000   # 1 / 50 Hz = 20,000 µs

servo = PWM(Pin(SERVO_PIN))
servo.freq(PWM_FREQ)

def angle_to_duty(angle: int) -> int:
    """Map 0–180° to 16-bit duty cycle (0–65535)."""
    pulse_us = SG90_MIN_US + (SG90_MAX_US - SG90_MIN_US) * angle // 180
    return int(pulse_us / PERIOD_US * 65535)

def write_angle(angle: int):
    servo.duty_u16(angle_to_duty(angle))

# ── Setup ──────────────────────────────────────────
print("SG90 Rapid Angle Test — Raspberry Pi Pico W")
write_angle(90)
time.sleep(1)

# ── Main loop ──────────────────────────────────────
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
