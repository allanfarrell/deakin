// ------------
// Blink name
// ------------

/*-------------

This program will flash 'allan' in morse code
    - blink the oboard led on and off.
    - blink the led attached to D7 on and off
    
Morse code timing rules from, https://www.codebug.org.uk/learn/step/541/morse-code-timing-rules/
    - dot is 500
    - dash is 1500
    - space between symbols is 500
    - space between letters is 1500
    - space between words is 3500

-------------*/

int led1 = D0; // Default onboard LED
int led2 = D7; // Digital output pin 7

void dot(int led){ digitalWrite(led, HIGH); delay(500); digitalWrite(led, LOW); }
void dash(int led){ digitalWrite(led, HIGH); delay(1500); digitalWrite(led, LOW); }
void symbol_gap(){ delay(500); }
void letter_gap(){ delay(1500); }
void word_gap(){ delay(3500); }

void setup() {
  pinMode(led1, OUTPUT);
  pinMode(led2, OUTPUT);
}

void loop() {
  // A - dot dash
    dot(led2); symbol_gap(); dash(led2); letter_gap();
    
  // L - dot dash dot dot
    dot(led2); symbol_gap(); dash(led2); symbol_gap(); dot(led2); symbol_gap(); dot(led2); letter_gap();
    
  // L - dot dash dot dot
    dot(led2); symbol_gap(); dash(led2); symbol_gap(); dot(led2); symbol_gap(); dot(led2); letter_gap();
    
  // A - dot dash
    dot(led2); symbol_gap(); dash(led2); letter_gap();
    
  // N - dash dot
    dash(led2); symbol_gap(); dot(led2); word_gap();
}
