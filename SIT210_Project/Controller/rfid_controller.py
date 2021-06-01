from mttkinter import mtTkinter as mtk
from tkinter.constants import *

import config
from config import *

# Clear scrolling textbox
def clear():
    config.resultScrolledText.delete(1.0, END)

# Reset RFID reader
def reset():
    config.ourClient.publish("CONTROL", "Reset")

# Turn RFID reader 'On'
def rfid_on(Btn):
    config.ourClient.publish("CONTROL", "TurnOn")
    Btn['text'] = "Disable RFID Reader"
    Btn['command'] = lambda: rfid_off(Btn)

# Turn RFID reader 'Off'
def rfid_off(Btn):
    config.ourClient.publish("CONTROL", "TurnOff")
    Btn['text'] = "Enable RFID Reader"
    Btn['command'] = lambda: rfid_on(Btn)

# Load RFID controller user interface
def load_ui(tab_rfid):
    # Toggle On/Off button
    config.submitBtn = mtk.Button(tab_rfid, text="Enable RFID Reader", command= lambda: rfid_on(config.submitBtn), height = 1, width = 25)
    config.submitBtn.place(x=0+BORDER, y=400+BORDER)
    
    # Clear textbox button
    clearBtn = mtk.Button(tab_rfid, text="Clear", command=clear, height = 1, width = 10)
    clearBtn.place(x=235+BORDER, y=400+BORDER)
    
    # Clear textbox button
    resetBtn = mtk.Button(tab_rfid, text="Reset", command=reset, height = 1, width = 10)
    resetBtn.place(x=350+BORDER, y=400+BORDER)
    
    # Label
    resultLabel = mtk.Label(tab_rfid, text="Output", background='black', foreground='white', width = 78, height=1)
    resultLabel.place(x=0+BORDER,y=0+BORDER)
    
    # Scrolling textbox
    config.resultScrolledText = mtk.scrolledtext.ScrolledText(tab_rfid, background='black', foreground='white', width=78, height=23)
    config.resultScrolledText.place(x=0+BORDER, y=20+BORDER)