// SIT210 Task2.3C Create IFTTT trigger
#include <BH1750Lib.h>

//initialize device
BH1750Lib lightmeter;

// Current and previous luminosicty
uint16_t prevlux = 0;
uint16_t lux = 0;

void setup(){
  lightmeter.begin(BH1750LIB_MODE_CONTINUOUSHIGHRES);
}


void loop() {
  // Store previous lux
  prevlux = lux;
  // Get current lux
  lux = lightmeter.lightLevel();
  
  // Change from Sunlight -> Shade
  if(prevlux > 0 && lux == 0)
  {
    // Publish data to particle.io
    Particle.publish("Terrarium", "Shade", PRIVATE);     
  }
  
  // Change from Shade -> Sunlight
  if(prevlux == 0 && lux > 0)
  {
    // Publish data to particle.io
    Particle.publish("Terrarium", "Sunlight", PRIVATE);
  }

  // Pause execution
  delay(30000);
}