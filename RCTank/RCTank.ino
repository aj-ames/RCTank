#define enMotorR 5
#define MotorR1 13
#define MotorR2 14
#define MotorL1 15
#define MotorL2 2
#define enMotorL 4

#define maxPWM 1023
#define turnPWM 1023

char ch = ' ', cmd = ' ';

void setup() {
  Serial.begin(9600);
  pinMode(enMotorR, OUTPUT);
  pinMode(enMotorL, OUTPUT);
  pinMode(MotorR1, OUTPUT);
  pinMode(MotorR2, OUTPUT);
  pinMode(MotorL1, OUTPUT);
  pinMode(MotorL2, OUTPUT);

  Serial.println("Setup Complete.");
}

void loop() {
  if(Serial.available() > 0) {
    while(Serial.available()) {
      ch = Serial.read();
      if((int)ch == 13 || (int)ch == 10) {
        break;
      }
      cmd = ch;
    }
   switch(cmd) {
    case 'F':
      forward();
      Serial.println("forward!");
      break;
     case 'B':
      reverse();
      break;
     case 'R':
      right();
      break;
     case 'L':
      left();
      break;
     default:
      halt();
   }
  }
}

void forward() {
  analogWrite(enMotorL, maxPWM);
  analogWrite(enMotorR, maxPWM);
  
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
}

void reverse() {
  analogWrite(enMotorL, maxPWM);
  analogWrite(enMotorR, maxPWM);
  
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
}

void left() {
  analogWrite(enMotorL, turnPWM);
  analogWrite(enMotorR, turnPWM);
  
  digitalWrite(MotorR1, HIGH);
  digitalWrite(MotorR2, LOW);
  
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, HIGH);
}

void right() {
  analogWrite(enMotorL, turnPWM);
  analogWrite(enMotorR, turnPWM);
  
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, HIGH);
  
  digitalWrite(MotorL1, HIGH);
  digitalWrite(MotorL2, LOW);
}

void halt() {
  analogWrite(enMotorL, 0);
  analogWrite(enMotorR, 0);
  
  digitalWrite(MotorR1, LOW);
  digitalWrite(MotorR2, LOW);
  
  digitalWrite(MotorL1, LOW);
  digitalWrite(MotorL2, LOW);
}



