// SIT210 Task3.3D Particle - Buddy System

// LED pin
int led = D2;

// Particle subscribe callback method
void controller(const char *event, const char *data)
{
    // Control flow
    if(strcmp(data, "pat") == 0)
    {
        // Long blink    
        digitalWrite(led, HIGH); delay(1000); digitalWrite(led, LOW); delay(1000);
    }
    else if(strcmp(data, "wave") == 0)
    {
        // Quick blink
        for(int i = 0; i < 3; i++)
        {
            digitalWrite(led, HIGH); delay(1000); digitalWrite(led, LOW); delay(1000);
        }
    }
}

void setup() {
    // Set pin as output
    pinMode(led, OUTPUT);
    
    // Subscribe to deakins public event - Only works on campus!
    // Particle.subscribe("Deakin_RIOT_SIT210_Photon_Buddy", controller);
}

void loop() {
    // Test LED
    controller("none", "wave");
}