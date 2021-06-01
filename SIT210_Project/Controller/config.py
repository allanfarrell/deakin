from mttkinter import mtTkinter as mtk

BORDER=10
LOCAL_IP="127.0.0.1"
MOSQUITTO_SERVER_IP="192.168.0.14"
PORT=1883
TOPIC="RFID"
TOPIC2="CONTROL"

## Global variables shared between files
#
ourClient = ''
#
ourConsole = ''
#
#resultScrolledText = mtk.scrolledtext.ScrolledText()
#
submitBtn = ''

# Recording the device state (RFID/All)
debugMode = True

#
topicsDISPLAY = 'TO BE REMOVED'