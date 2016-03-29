// the setup function runs once when you press reset or power the board

int in1 = 6;
int in2 = 8;
int stby = 0;
int pwm = 5;
int decoder = 2;
int countLimit = 10000;


int counter=0;

void setup() {
  // initialize digital pin 13 as an output.
  pinMode(pwm, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(stby, OUTPUT);
  pinMode(decoder, INPUT);
  attachInterrupt(digitalPinToInterrupt(decoder), count, CHANGE);
  Serial.begin(9600);
}



void count() {
  ++counter; 
}




// the loop function runs over and over again forever
void loop() {

  leftwheel (true, 128, 100);
  delay(2000);
  leftwheel (false, 255, 10);
  delay(2000);
  
}


void leftwheel (boolean forward, int velocity, int steps)
{
  analogWrite(pwm, velocity);   
  counter = 0;
  while(counter<steps){
    digitalWrite(stby, HIGH);   
    if (forward == true) {
      digitalWrite(in1, HIGH);   
      digitalWrite(in2, LOW);
    }
    else {
      digitalWrite(in1, LOW);   
      digitalWrite(in2, HIGH);
    }
    Serial.println(counter);
  }
  Serial.print("DEBUG: Out of the loop now");
  digitalWrite(in1, HIGH);   
  digitalWrite(in2, HIGH);   
}

