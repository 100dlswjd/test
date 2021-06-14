#include<SoftwareSerial.h>
int n = 0;
int Tx = 2 ;
int Rx = 3 ;
SoftwareSerial hm10(Tx,Rx);

void setup(){
  Serial.begin(9600);
  hm10.begin(9600);
}

void loop(){
  if(hm10.available()){
    if(n = 0){
      n = 120;
      Serial.write(120);
    }
    else if(n = 120){
      n = 0;
      Serial.write(0);
    }
  }
}
