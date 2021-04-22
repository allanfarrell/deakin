import RPi.GPIO as GPIO
import time
import math

GPIO.setwarnings(False)

# Setup pins
TRIG = 23
ECHO = 24
led_buzzer = 17

# Use the rRaspberyPi GPIO pin numbers
GPIO.setmode(GPIO.BCM)

GPIO.setup(led_buzzer, GPIO.OUT)
GPIO.setup(TRIG, GPIO.OUT)
GPIO.setup(ECHO, GPIO.IN)

# Get distance measurement from utrlasonic sensor
def sense():
    # Wait for sensor to settle
    GPIO.output(TRIG, False)
    time.sleep(2)

    GPIO.output(TRIG, True)
    time.sleep(0.00001)
    GPIO.output(TRIG, False)

    # Set default start time
    pulse_start = time.time()

    # Wait for sensor change to record start
    while GPIO.input(ECHO) == 0:
        pulse_start = time.time()
    
    # Set default end time
    pulse_end = time.time()

    # Wait for sensor change to record stop
    while GPIO.input(ECHO) == 1:
        pulse_end = time.time()

    # Calculate distance
    pulse_duration = pulse_end - pulse_start

    distance = pulse_duration * 17150

    distance = round(distance, 2)
    
    return round(distance, 2)

# Configure pulse width modulation on pin
pwm = GPIO.PWM(led_buzzer, 60)

# Operation loop
try:
    while True:
        d = sense()
        print('Distance: ', d)
        pwm.start(0)
        if(d >= 100 and d < 200):
            pwm.ChangeDutyCycle(25)
            
        if(d >= 50 and d < 100):
            pwm.ChangeDutyCycle(50)
            
        if(d >= 25 and d < 50):
            pwm.ChangeDutyCycle(75)
            
        if(d >= 10 and d < 25):
            pwm.ChangeDutyCycle(100)
        time.sleep(1)
        pwm.stop()
except KeyboardInterrupt:
    GPIO.cleanup()