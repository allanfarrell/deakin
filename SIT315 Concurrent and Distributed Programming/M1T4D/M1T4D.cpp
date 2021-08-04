// TaskM1.T4d: More inputs timer board
// PIR + Button + Timer -> Arduino -> LED

const int pin_grn = 8;
const int pin_blu = 11;
const int pin_red = 12;
const int pin_obLED = 13;

const int pin_button = 2;
const int pin_motion1 = 3;
const int pin_motion2 = 4;


// Configure device at start up
void setup()
{
  Serial.begin(9600);
  // Configure I/O pins
  pinMode(pin_button, INPUT);
  pinMode(pin_motion1, INPUT);
  pinMode(pin_motion2, INPUT);

  pinMode(pin_grn, OUTPUT);
  pinMode(pin_blu, OUTPUT);
  pinMode(pin_red, OUTPUT);
  pinMode(pin_obLED, OUTPUT);

  // Turn on interupts on pord d (pins 0 - 7)
  PCICR |= 0b00000100;
  
  // Enable interupts on pins 2, 3, and 4
  PCMSK2 |= 0b00011100;
  
  // Start timer with frequency
  startTimer(0.5);
}

// Main program loop
void loop()
{
  // ...
}

// Setup timer interupts based on required frequency
void startTimer(double timerFrequency)
{
    noInterrupts();

    // Clear registers
    TCCR1A = 0;
    TCCR1B = 0;
    TCNT1 = 0;

  	// Set TCCRx to largest prescaller
  	TCCR1B |= (1 << CS12) | (1 << CS10);
  
  	// Calculate OCRx register
  	OCR1A = 16000000 /(timerFrequency * 1024);

    // Output Compare Match A Interrupt Enable
    TIMSK1 |= (1 << OCIE1A);

    // CTC
    TCCR1B |= (1 << WGM12);
    interrupts();
}

// Timer interrupt
ISR(TIMER1_COMPA_vect){
  digitalWrite(pin_obLED, digitalRead(pin_obLED) ^ 1);
  Serial.println("Timer");
}

// Interrupt Port D
ISR(PCINT2_vect)
{
  // Check the pin that interrupted and call actuator accordingly
  if(PIND & 0b00000100)
  {
    serial("In: ", pin_button);
    toggle_actuator(pin_grn);
  }
  if(PIND & 0b00001000)
  {
    serial("In: ", pin_motion1);
    toggle_actuator(pin_red);
  }
  if(PIND & 0b00010000)
  {
    serial("In: ", pin_motion2);
    toggle_actuator(pin_blu);
  }
}

// Toggle actuator output
void toggle_actuator(int pin)
{
  	noInterrupts();
  	digitalWrite(pin, HIGH);
  	serial("Out: ", pin);
  	delay(500);
  	digitalWrite(pin, LOW);
  	interrupts();
}

// Print output to serial
void serial(char* msg, int value)
{
  Serial.print(msg);
  Serial.println(value);
}