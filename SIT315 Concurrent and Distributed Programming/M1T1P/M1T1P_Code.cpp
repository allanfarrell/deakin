// TaskM1.T1P: Build a simple Sense-Think-Act Board
// Ultrasonic sensor -> Arduino -> LED

const int sensor = 8;
const int actuator = 2;

// Configure device at start up
void setup()
{
  Serial.begin(9600);
  pinMode(actuator, OUTPUT);
}

// Main program loop
void loop()
{
	// Think
	if(sense() < 19000){ act();}
}

// Gather input from sensors
int sense()
{
  // Trigger ultrasonic pulse
  pinMode(sensor, OUTPUT);
  digitalWrite(sensor, LOW);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(sensor, HIGH);
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(sensor, LOW);
  
  // Get ultrasonic return value
  pinMode(sensor, INPUT);
  int result = pulseIn(sensor, HIGH);
  
  // Output result
  serial("Ultrasonic: ", result);
  return result;
}

// Perform actions using attached actuators
void act()
{
  digitalWrite(actuator, HIGH);
  
  // Output current pin state
  serial("LED: ", digitalRead(actuator));
  delay(1000); // Wait for 1000 millisecond(s)
  digitalWrite(actuator, LOW);
  
  // Output current pin state
  serial("LED: ", digitalRead(actuator));
}

// Print output to serial
void serial(char* msg, int value)
{
  Serial.print(msg);
  Serial.println(value);
}