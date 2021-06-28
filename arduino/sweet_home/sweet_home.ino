#include <Servo.h>
#include "BluetoothSerial.h"

#if !defined(CONFIG_BT_ENABLED) || !defined(CONFIG_BLUEDROID_ENABLED)
#error Bluetooth is not enabled! Please run `make menuconfig` to and enable it
#endif
int servoPin = 22;

Servo servo;
BluetoothSerial SerialBT;

void setup() {
  Serial.begin(9600);
  servo.attach(servoPin);
  SerialBT.begin("BigRoom"); //
}

void loop(){
  if (Serial.available()) {
    SerialBT.write(Serial.read());
  }
  
  if (SerialBT.available()) {
    char ch = SerialBT.read();
    Serial.write(ch);
    if(ch == 'o')
    {
      servo.write(120);
      Serial.write(ch);
    }
      
    if(ch == 'f')
    {
      servo.write(70);
      Serial.write(ch);
    }
  }
  delay(20);
}
