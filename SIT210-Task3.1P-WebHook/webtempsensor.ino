// Task 3.1P Sending data to the web
#include <Adafruit_DHT.h>

// Define values
#define DHTTYPE DHT22   // DHT 22  (AM2302)
#define DHTPIN 3        // Digital Pin 3

DHT dht(DHTPIN, DHTTYPE);

//Stores temperature value
float temp;

// Tempature as string
String tempString;


// Device start up configuration
void setup() {
  dht.begin();
}

// Temperature recording loop
void loop() {
    // Store analog sensor value
    temp = dht.getTempCelcius();
    
    // Convert temperature value to string
    tempString = String::format("%.2f", temp);

    // Publish data to particle.io
    Particle.publish("TempHook", tempString, PRIVATE);
    
    // Wait 60 seconds
    delay(60000);
}