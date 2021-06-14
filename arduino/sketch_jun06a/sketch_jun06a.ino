#include <Servo.h>

int Button_red = D6;
int Button_yellow = D9;
int servoPin = D8;
int posDegrees = 90;

Servo servo;

void setup() {
  // put your setup code here, to run once:
  pinMode(Button_red,INPUT);
  pinMode(Button_yellow,INPUT);
  servo.attach(servoPin);
  Serial.begin(9600);
  servo.write(posDegrees);
}

void loop() {
  int B_R = digitalRead(Button_red);
  int B_Y = digitalRead(Button_yellow);
  if(B_R==0){
    servo.write(posDegrees);
    posDegrees = posDegrees + 1;
    Serial.println(posDegrees);
    delay(1);
  }
  if(posDegrees > 180){
    posDegrees = 180;
  }
  if(B_Y==0){
    servo.write(posDegrees);
    posDegrees = posDegrees - 1;
    Serial.println(posDegrees);
    delay(1);
  }
  if (posDegrees < 0){
    posDegrees = 0;
  }
}
