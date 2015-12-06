// the setup function runs once when you press reset or power the board

int in1 = 1;
int in2 = 4;
int stby = 0;
int pwm = 5;
int decoder = 2;

int counter=0;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(5, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(1, OUTPUT);
  pinMode(0, OUTPUT);
  pinMode(2, INPUT);
  attachInterrupt(digitalPinToInterrupt(decoder), count, CHANGE);
  Serial.begin(9600);
}



void count() {
  counter++; 
}




// the loop function runs over and over again forever
void loop() {

  digitalWrite(pwm, HIGH);   
  digitalWrite(stby, HIGH);   
  digitalWrite(in1, HIGH);   
  digitalWrite(in2, LOW); 
  delay(200);   
  Serial.println("Forward");  
  Serial.println(counter);
  delay(2000);              // wait for a second
  digitalWrite(pwm, HIGH);   
  digitalWrite(stby, HIGH);   
  digitalWrite(in1, HIGH);   
  digitalWrite(in2, HIGH);
  delay(200); 
  Serial.println("Stop");    
  Serial.println(counter);
  delay(2000);              // wait for a second

  
}
