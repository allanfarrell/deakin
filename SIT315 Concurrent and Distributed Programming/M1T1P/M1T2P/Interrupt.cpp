// Task1.T2P: Interrupt-driven Board
// PIR sensor -> Arduino -> LED

const int sensor = 2;
const int actuator = 8;
volatile byte state = LOW;

// Configure device at start up
void setup()
{
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  pinMode(actuator, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensor), interrupt, CHANGE);
}

// Main program loop
void loop()
{
  // ...
}

// Actions taken during interrupt
void interrupt()
{
  state = !state;
  serial("State: ", state);
  digitalWrite(actuator, state);
  serial("LED: ", state);
}

// Print output to serial
void serial(char* msg, int value)
{
  Serial.print(msg);
  Serial.println(value);
}