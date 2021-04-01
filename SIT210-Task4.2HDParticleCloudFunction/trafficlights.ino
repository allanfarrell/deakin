// SIT210 Task 4.2HD Particle - Calling a function from a web device

// Assign pins
int led_red = D4;
int led_green = D6;
int led_blue = D8;

int Manage_Lights(String value);

void setup() {
    pinMode(led_red, OUTPUT);
    pinMode(led_green, OUTPUT);
    pinMode(led_blue, OUTPUT);
    
    // Register the cloud function
    Particle.function("trafficlights", Manage_Lights);
}

void loop() {
    // Not required
}

// Switch on/off LEDs
int Manage_Lights(String value)
{
    if(strcmp(value, "red") == 0)
    {
        digitalWrite(led_red, HIGH);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, LOW);
    }
    if(strcmp(value, "green") == 0)
    {
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, HIGH);
        digitalWrite(led_blue, LOW);
    }
    if(strcmp(value, "blue") == 0)
    {
        digitalWrite(led_red, LOW);
        digitalWrite(led_green, LOW);
        digitalWrite(led_blue, HIGH);
    }
    return 0;
}