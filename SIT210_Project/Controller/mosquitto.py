from tkinter.constants import *

import paho.mqtt.client as mqtt
import config
from rfid_controller import *
import rfid_controller
    
## Events
def messageFunction(client, userdata, message):
    topic = str(message.topic)
    message = str(message.payload.decode("utf-8"))
    if(topic == 'RFID'):
        messageRFID(topic, message)
    elif(topic == 'CONTROL'):
        messageCONTROL(topic, message)

def messageRFID(topic, message):
    # Print to RFID textbox
    if(config.debugMode == True):
        config.resultScrolledText.insert(INSERT, f"{topic}: {message}\n")
    else:
        config.resultScrolledText.insert(INSERT, f"{message}\n")
    config.resultScrolledText.yview(END)
    
def messageCONTROL(topic, message):
    if(message == 'Registering device...'):
        config.ourClient.publish(TOPIC2, 'GetStatus')
        rfid_controller.rfid_off(config.submitBtn)
    if(message == 'Status=Read'):
        rfid_controller.rfid_on(config.submitBtn)
    if(message == 'Status=Idle'):
        rfid_controller.rfid_off(config.submitBtn)
    # Print to RFID textbox
    if(config.debugMode == True):
        config.resultScrolledText.insert(INSERT, f"{topic}: {message}\n")
        config.resultScrolledText.yview(END)

def start_service():
    config.ourClient = mqtt.Client("makerio_mqtt")
    config.ourClient.connect(LOCAL_IP, PORT)
    config.ourClient.subscribe(TOPIC)
    config.ourClient.subscribe(TOPIC2)
    config.ourClient.on_message = messageFunction
    config.ourClient.loop_start()
    
    config.resultScrolledText.insert(INSERT, "Initialising mosquitto service...\n")
    config.resultScrolledText.insert(INSERT, f"IP: {LOCAL_IP}\n")
    config.resultScrolledText.insert(INSERT, f"Port: {PORT}\n")
    config.resultScrolledText.insert(INSERT, f"Topic: {TOPIC}\n")
    config.ourClient.publish('CONTROL', 'GetStatus')
    config.resultScrolledText.yview(END)

def stop_service():
    config.ourClient.loop_stop()
    config.resultScrolledText.insert(INSERT, "Mosquitto service terminated...\n")
    config.resultScrolledText.yview(END)
    
def restart_service():
    stop_service()
    start_service()
    config.resultScrolledText.insert(INSERT, "Restarting mosquitto service...\n")
    config.resultScrolledText.yview(END)