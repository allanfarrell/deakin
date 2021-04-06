from tkinter import *
import tkinter.font
import RPi.GPIO as GPIO

## Configure pins
redPin = 11
greenPin = 13
bluePin = 15

# Set configuration to use board pin numbers
GPIO.setmode(GPIO.BOARD)

GPIO.setup(redPin, GPIO.OUT)
GPIO.setup(greenPin, GPIO.OUT)
GPIO.setup(bluePin, GPIO.OUT)

# Turn off all lights to start  - Not sure why light turns on at start up
GPIO.output(redPin, GPIO.LOW)
GPIO.output(greenPin, GPIO.LOW)
GPIO.output(bluePin, GPIO.LOW)

## Base GUI window
win = Tk()
win.title("LED controller")
win.geometry("275x175")

## Events
def redOn():
    GPIO.output(redPin, GPIO.HIGH)
    GPIO.output(greenPin, GPIO.LOW)
    GPIO.output(bluePin, GPIO.LOW)
    
def greenOn():
    GPIO.output(redPin, GPIO.LOW)
    GPIO.output(greenPin, GPIO.HIGH)
    GPIO.output(bluePin, GPIO.LOW)

def blueOn():
    GPIO.output(redPin, GPIO.LOW)
    GPIO.output(greenPin, GPIO.LOW)
    GPIO.output(bluePin, GPIO.HIGH)
    
def close():
    GPIO.cleanup()
    win.destroy()

## Widgets
# Radio buttons
var = IntVar()
Radiobutton(win, text = "Red", variable=var, value="red", command=redOn).pack(anchor = W)
Radiobutton(win, text = "Green", variable=var, value="green", command=greenOn).pack(anchor = W)
Radiobutton(win, text = "Blue", variable=var, value="blue", command=blueOn).pack(anchor = W)

# Close application
win.protocol("WM_DELETE_WINDOW", close)