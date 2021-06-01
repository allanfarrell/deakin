from mttkinter import mtTkinter as mtk
from tkinter.constants import *

import rfid_controller
import mosquitto

## Events
def close():
    mosquitto.stop_service();
    win.destroy()

## Base GUI window
win = mtk.Tk()
win.title("RFID Reader")
win.geometry("675x475")

## Widgets
tab_parent =  mtk.ttk.Notebook(win)

tab_rfid = mtk.ttk.Frame(tab_parent)
tab_parent.add(tab_rfid, text='RFID Reader')
tab_parent.pack(expand=1, fill='both')

rfid_controller.load_ui(tab_rfid)

# Start mosquitto server
mosquitto.start_service()

# Close application
win.protocol("WM_DELETE_WINDOW", close)