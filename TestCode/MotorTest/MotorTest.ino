
 
// Pin 13 has an LED connected on most Arduino boards.
// give it a name:
int stby = 0;
int in1 = 1;
int in2 = 2;
int pwm = 3;

// the setup routine runs once when you press reset:
void setup() {                
  // initialize the digital pin as an output.
  pinMode(stby, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(pwm, OUTPUT);  
}

// the loop routine runs over and over again forever:
void loop() {
  digitalWrite(stby, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(in1, HIGH);
  analogWrite(pwm, 255);
  digitalWrite(in2, LOW);  
  delay(2000);               // wait for a second
  analogWrite(pwm, 64);    // turn the LED off by making the voltage LOW
  delay(2000); 
  analogWrite(pwm, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  delay(2000);               // wait for a second
  analogWrite(pwm, 64);    // turn the LED off by making the voltage LOW
  delay(2000); 
  digitalWrite(stby,LOW);
  delay(2000);
  }
