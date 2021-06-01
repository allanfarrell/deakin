from mttkinter import mtTkinter as mtk

BORDER=10
LOCAL_IP="127.0.0.1"
MOSQUITTO_SERVER_IP="192.168.0.14"
PORT=1883
TOPIC="RFID"
TOPIC2="CONTROL"

## Global variables shared between files
# MQTT client
ourClient = ''
# ScrolledText box widget
ourConsole = ''
# Toggle device On/Off button
submitBtn = ''
# Display CONTROL topic when in debug mode
debugMode = True

# TO BE REMOVED
topicsDISPLAY = 'TO BE REMOVED'
