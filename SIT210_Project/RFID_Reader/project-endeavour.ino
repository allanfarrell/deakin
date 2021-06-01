// *******************************************************************************************
//
//  Particle Argon RFID reader
//
// *******************************************************************************************
//
// Documentation for the libraries and Particle functions used
// https://github.com/hirotakaster/MQTT
// https://github.com/miguelbalboa/rfid
// https://docs.particle.io/reference/device-os/firmware/#introduction
//
// TOPICS
//  - RFID - Display information from device to controller
//  - CONTROL - Communication for controling device
//
// *******************************************************************************************

#include <MFRC522.h>
#include <MQTT.h>
#include <string>

// *******************************************************************************************

// Configure RFID reader
#define SS_PIN A5
#define RST_PIN A4

// Create MFRC522 instance
MFRC522 mfrc522(SS_PIN, RST_PIN);

// *******************************************************************************************

// Configure Mosquitto Server
#define MOSQ_IP "192.168.0.14"
#define MOSQ_PORT 1883

// Create an MQTT client
MQTT client(MOSQ_IP, MOSQ_PORT, callback);

// *******************************************************************************************

#define PIN_buzzer D2
#define PIN_LEDwifi D3
#define PIN_LEDclient D4
#define PIN_LEDmode D5

// Initalise application to disabled
bool STATE_wifi = false;
bool STATE_client = false;
bool STATE_mode = false;

// Perform actions on device when message is published to topic device is subscribed to
void callback(char* topic, byte* payload, unsigned int length)
{
    // Convert payload to char array
    char p[length + 1];
    memcpy(p, payload, length);
    p[length] = NULL;
    
    // Switch device to reading mode
    if(strcmp(p, "TurnOn") == 0)
    {
        STATE_mode = true;
    }
    // Switch device to idle mode
    else if(strcmp(p, "TurnOff") == 0)
    {
        STATE_mode = false;
    }
    // Publish device status on request
    else if (strcmp(p, "GetStatus") == 0)
    {
        const char* STATE_STRING = STATE_mode == false ? "Status=Idle" : "Status=Read";
        client.publish("CONTROL", STATE_STRING);
    }
    // Reset Argon device
    else if(strcmp(p, "Reset") == 0)
    {
        System.reset();
    }
}

// Setup the Argon
void setup() 
{
    // Connect to the server and call ourselves "RFID_Reader"
    client.connect("RFID_Reader");
    client.subscribe("CONTROL");
    client.publish("CONTROL", "Registering device...");
    
    // Configure Pins
    pinMode(PIN_buzzer, OUTPUT);
    pinMode(PIN_LEDwifi, OUTPUT);
    pinMode(PIN_LEDclient, OUTPUT);
    pinMode(PIN_LEDmode, OUTPUT);
    
    // Configure RFID reader
    mfrc522.setSPIConfig();
    mfrc522.PCD_Init();  // Init MFRC522 card
}

// Main loop
void loop() 
{
    // Check device state -> Update embedded device output
    update_state_wifi();
    update_state_client();
    update_state_mode();
    
    // Check connection to WiFi
    if(STATE_wifi)
    {
        // Check connection to Mosquitto server
        if (STATE_client)
        {
            // Only read cards when device is in read mode
            if(STATE_mode)
            {
                // Read RFID and output via MQTT
                MIFARE_DumpToMQTT();
            }
            
            // This should be called regularly to allow the client to process incoming messages and maintain its connection to the server.
            client.loop();
            delay(2000);
        }
        // Client not connected -> Attempt to reconnect
        else
        {
            STATE_client = client.connect("RFID_Reader");
            if(STATE_client)
            {
                client.subscribe("CONTROL");
                client.publish("CONTROL", "Registering device...");
                delay(500);
            } else
            {
                delay(5000);
            }
        }
    }
    // Wifi not connected -> Long delay
    else
    {
        delay(5000);
    }
}

// Check WiFi status and update device WiFi LED
void update_state_wifi()
{
    STATE_wifi = WiFi.ready();
    bool wifiled_state = digitalRead(PIN_LEDwifi);
    if(STATE_wifi && !wifiled_state) digitalWrite(PIN_LEDwifi, HIGH);
    if(!STATE_wifi && wifiled_state) digitalWrite(PIN_LEDwifi, LOW);
}

// Check Mosquitto/MQTT server status and update device client LED
void update_state_client()
{
    STATE_client = client.isConnected();
    bool client_led_state = digitalRead(PIN_LEDclient);
    if(STATE_client && !client_led_state) digitalWrite(PIN_LEDclient, HIGH);
    if(!STATE_client && client_led_state) digitalWrite(PIN_LEDclient, LOW);
}

// Check device status and update mode LED
void update_state_mode()
{
    // Mode state is held gloabally
    bool mode_led_state = digitalRead(PIN_LEDmode);
    if(STATE_mode && !mode_led_state) digitalWrite(PIN_LEDmode, HIGH);
    if(!STATE_mode && mode_led_state) digitalWrite(PIN_LEDmode, LOW);
}

// Convert byte to Hex string
// Code excerpt from https://forum.arduino.cc/t/convert-mfrc522-uid-to-string-byte-array-to-string/613945
void array_to_string(byte array[], unsigned int len, char buffer[])
{
   for (unsigned int i = 0; i < len; i++)
   {
      byte nib1 = (array[i] >> 4) & 0x0F;
      byte nib2 = (array[i] >> 0) & 0x0F;
      buffer[i*2+0] = nib1  < 0xA ? '0' + nib1  : 'A' + nib1  - 0xA;
      buffer[i*2+1] = nib2  < 0xA ? '0' + nib2  : 'A' + nib2  - 0xA;
   }
   buffer[len*2] = '\0';
}

// Convert byte array to ASCII
void hex_to_ascii(byte array[], unsigned int len, char buffer[])
{
   for (unsigned int i = 0; i < len; i++)
   {
      buffer[i] =  array[i] > 0x1F && array[i] < 0x7E ? array[i]  : ' ';
   }
   buffer[len*2] = '\0';
}

// Code adapted from https://github.com/miguelbalboa/rfid
void MIFARE_DumpToMQTT()
{
        // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
        MFRC522::MIFARE_Key key;
        for (byte i = 0; i < 6; i++) {
                key.keyByte[i] = 0xFF;
        }
        
        // Look for new cards
        if ( ! mfrc522.PICC_IsNewCardPresent()) {
                return;
        }

        // Select one of the cards
        if ( ! mfrc522.PICC_ReadCardSerial()) {
                return;
        }
        // Now a card is selected. The UID and SAK is in mfrc522.uid.
        
        // Buzzer On
        digitalWrite(PIN_buzzer, HIGH);
        
        // Dump UID
        char str[mfrc522.uid.size * 8] = "";
        array_to_string(mfrc522.uid.uidByte, mfrc522.uid.size, str);
        client.publish("RFID", (std::string("Card UID: ") + std::string(str)).c_str());
        
        // Dump PICC type
        byte piccType = mfrc522.PICC_GetType(mfrc522.uid.sak);
        client.publish("RFID", (std::string("PICC type: ") + std::string(mfrc522.PICC_GetTypeName(piccType))).c_str());
        
        if (              piccType != MFRC522::PICC_TYPE_MIFARE_MINI 
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_1K
                &&        piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
                client.publish("RFID", "Only MIFARE Classic cards are currently supported.");
                return;
        }
        
        // Operation status for PCD_Authenticate and MIFARE_Read
        byte status;
         
        byte buffer[18];
        byte block  = 0;
        byte size = sizeof(buffer);
        char str_hex[size] = "";
        // Read block
    	byte byteCount = sizeof(buffer);

        // Loop through all blocks
    	do
    	{
    	    // Publish title for every 4 blocks
    	    if(block % 4 == 0) client.publish("RFID", (std::string("Sector") + std::to_string(block / 4)).c_str());
    	    
    	    // Authenticate 
            status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, block, &key, &(mfrc522.uid));
            if (status != MFRC522::STATUS_OK) {
               client.publish("RFID", (std::string("PCD_Authentication() failed: ") + std::string(mfrc522.GetStatusCodeName(status))).c_str());
               //return;
            }
            else
            {
                status = mfrc522.MIFARE_Read(block, buffer, &byteCount);
        	    if(status == MFRC522::STATUS_OK)
        	    {
        	        array_to_string(buffer, size, str_hex);
        	        // hex_to_ascii(buffer, size, str_hex);
        	        client.publish("RFID", str_hex);
        	    }
        	    else
        	    {
                    client.publish("RFID", "MIFARE_Read() failed.");
        	    }
        	    
        	    // Increment block counter
        	    block++;
            }
    	} while(status == MFRC522::STATUS_OK);
    	
        // Halt PICC
        mfrc522.PICC_HaltA();

        // Stop encryption on PCD
        mfrc522.PCD_StopCrypto1();
        
        // Buzzer Off
        digitalWrite(PIN_buzzer, LOW);
}