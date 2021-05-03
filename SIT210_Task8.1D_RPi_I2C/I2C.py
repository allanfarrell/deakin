import RPi.GPIO as GPIO
import time
import smbus

# Terminal command 'i2cdetect -y 1'
ADDRESS = 0x23
ONE_TIME_HIGH_RES_MODE = 0x20

bus = smbus.SMBus(1)

# Convert sensor data into a number
def convertToNumber(data):
    return((data[1] + (256*data[0]))/1.2)

# Get data from sensor
def readLight():
    data = bus.read_i2c_block_data(ADDRESS, ONE_TIME_HIGH_RES_MODE)
    print(data)
    return convertToNumber(data)

try:
    # Sense light loop
    while True:
        lx = readLight()
        # Datasheet has max lux of 65535, however, the reading is never that high even with direct light
        max_lx = 15000
        if lx > max_lx * 0.8:
            print(f"Too Bright, {lx:.2f} lux")
        elif lx > max_lx * 0.6:
            print(f"Bright, {lx:.2f} lux")
        elif lx > max_lx * 0.4:
            print(f"Medium, {lx:.2f} lux")
        elif lx > max_lx * 0.2:
            print(f"Dark, {lx:.2f} lux")
        else:
            print(f"Too dark, {lx:.2f} lux")
        time.sleep(0.5)
except KeyboardInterrupt:
    print("Closing program.")
