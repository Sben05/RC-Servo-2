import pwmio
import board
import time

# GP15, 50Hz servo
pwm = pwmio.PWMOut(board.GP15, frequency=50)

def angle_to_duty(angle):
    pulse_ms = 0.5 + (angle / 180.0) * 2.0
    duty = int((pulse_ms / 20.0) * 65535)
    return duty

while True:
    for angle in range(0, 181, 1):
        pwm.duty_cycle = angle_to_duty(angle)
        time.sleep(0.01)
    for angle in range(180, -1, -1):
        pwm.duty_cycle = angle_to_duty(angle)
        time.sleep(0.01)
