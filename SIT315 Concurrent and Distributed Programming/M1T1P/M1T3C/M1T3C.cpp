// TaskM1.T3C: Multiple-Inputs Board
// PIR + Switch -> Arduino -> LED

const int sensor_switch = 2;
const int sensor_motion = 3;

volatile byte state_switch = LOW;
volatile byte state_motion = LOW;

const int actuator = 8;

// Configure device at start up
void setup()
{
  Serial.begin(9600);
  pinMode(sensor_switch, INPUT);
  pinMode(sensor_motion, INPUT);
  pinMode(actuator, OUTPUT);
  attachInterrupt(digitalPinToInterrupt(sensor_switch), interrupt_switch, CHANGE);
  attachInterrupt(digitalPinToInterrupt(sensor_motion), interrupt_motion, CHANGE);
}

// Main program loop
void loop()
{
  // ...
}

// Motion sensor interrupt
void interrupt_motion()
{
  state_motion = !state_motion;
  serial("State_motion: ", state_motion);
  toggle_actuator();
}

// Switch interrupt
void interrupt_switch()
{
  state_switch = !state_switch;
  serial("State_switch: ", state_switch);
  toggle_actuator();
}

// Toggle actuator output
void toggle_actuator()
{
  if(state_switch == state_motion)
  {
    digitalWrite(actuator, state_switch);
    serial("LED: ", state_switch);
  } else
  {
    digitalWrite(actuator, LOW);
  }
}

// Print output to serial
void serial(char* msg, int value)
{
  Serial.print(msg);
  Serial.println(value);
}