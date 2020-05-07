// Code Referenced From: //http://educ8s.tv/arduino-bluetooth-tutorial//
// Toggles the onboard LED. 
// Tested with "Arduino Bluetooth Controller" app by Giumig Apps

#include <SoftwareSerial.h>

char LEDtoggle;
int  LED = 13;
int RX = 4;
int TX = 2;
 
SoftwareSerial BTserial(RX, TX);

void setup(){
  Serial.begin(9600);
  pinMode(LED, OUTPUT);
  BTserial.begin(9600);
}

void loop(){
  while (!BTserial.available());
  
  LEDtoggle = BTserial.read();
  
  if (LEDtoggle == '1'){
    Serial.println("LED HIGH");
    digitalWrite(LED, HIGH);
  }
  
  else{
    Serial.println("LED LOW");
    digitalWrite(LED, LOW);
  } 
  
} // loop()
