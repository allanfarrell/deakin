from tkinter import *
import tkinter.font
import RPi.GPIO as GPIO
import morse_code as MC

## Configure pins
redPin = 11

# Set configuration to use board pin numbers
GPIO.setmode(GPIO.BOARD)

GPIO.setup(redPin, GPIO.OUT)

# Turn off all lights to start  - Not sure why light turns on at start up
GPIO.output(redPin, GPIO.LOW)

## Base GUI window
win = Tk()
win.title("Morse code implementation")
win.geometry("275x175")

## Events
def redOn():
    GPIO.output(redPin, GPIO.HIGH)

def redOff():
    GPIO.output(redPin, GPIO.LOW)
    
def close():
    GPIO.cleanup()
    win.destroy()

def morseCodeiffy():
    morse_str2 = morse_str.get()
    MC.reader(morse_str2, redOn, redOff)

## Widgets
# Textbox
morse_str = StringVar()
textBox = Entry(win, width=30, textvariable=morse_str)
textBox.grid(row=0, column=1)

# Buttons
submitbutton = Button(win, text="Submit", command=morseCodeiffy, height = 1, width = 30)
submitbutton.grid(row=1, column=1)

exitbutton = Button(win, text="Close", command=close, height = 1, width = 30)
exitbutton.grid(row=2, column=1)

# Close application
win.protocol("WM_DELETE_WINDOW", close)