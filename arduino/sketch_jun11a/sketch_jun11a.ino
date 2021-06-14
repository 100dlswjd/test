#include<SoftwareSerial.h>
#include<Servo.h>

int servoPin = 5;
int posDegrees = 0;
int Tx = 2 ;
int Rx = 3 ;

SoftwareSerial hm10(Tx,Rx);
Servo servo;

void setup(){
  Serial.begin(9600);
  hm10.begin(9600);
  servo.attach(servoPin);
}

void loop(){
  while(hm10.available()){
    char h = (char)hm10.read();
    if(h == 'o'){
      servo.write(110);
    }
    if(h == 'f'){
      servo.write(20);
    }
  }
}
