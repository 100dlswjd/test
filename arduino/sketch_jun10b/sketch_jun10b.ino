#include<SoftwareSerial.h>
#include<Servo.h>
int servoPin = 5;
int i;
int Tx = 2 ;
int Rx = 3 ;
int result;
int on_off=0;
Servo servo;
SoftwareSerial hm10(Tx,Rx);

void setup(){
  Serial.begin(9600);
  hm10.begin(9600);
}

void loop(){
  if(hm10.available()){
    Serial.write(hm10.read());
    on_off = hm10.read();
    Serial.print("on_off의 값");
    Serial.println(on_off);
  }
  
  if(Serial.available()){
    hm10.write(Serial.read());
  }
  
  //if(on_off = -1){
    for(i=0;i<110;i++){
      servo.write(i);
    }
    delay(1000);
  //}
  //if(on_off = 10){
    for(i=110;i>20;i--){
      servo.write(i);
    }
    delay(1000);
  //}
}
