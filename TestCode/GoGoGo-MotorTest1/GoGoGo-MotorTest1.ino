// the setup function runs once when you press reset or power the board
void setup() {
  // initialize digital pin 13 as an output.
  pinMode(13, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(10, OUTPUT);
  
}

// the loop function runs over and over again forever
void loop() {
  int in1 = 13;
  int in2 = 12;
  int stby = 11;
  int pwm = 10;
  
  
  digitalWrite(pwm, HIGH);   
  digitalWrite(stby, HIGH);   
  digitalWrite(in1, HIGH);   
  digitalWrite(in2, LOW);   
  delay(2000);              // wait for a second
  digitalWrite(pwm, HIGH);   
  digitalWrite(stby, HIGH);   
  digitalWrite(in1, HIGH);   
  digitalWrite(in2, HIGH);   
  delay(2000);              // wait for a second
  digitalWrite(pwm, HIGH);   
  digitalWrite(stby, HIGH);   
  digitalWrite(in1, LOW);   
  digitalWrite(in2, HIGH); 
  delay(2000);              // wait for a second
}
