// Code Referenced From: //http://educ8s.tv/arduino-bluetooth-tutorial//
// Toggles the onboard LED. 
// Tested with "Arduino Bluetooth Controller" app by Giumig Apps

//Motor Controller
#include <SparkFun_TB6612.h> //manual download, not in library manager
#define PWMA 11
#define AIN2 10
#define AIN1 9
#define STBY 8
#define BIN1 3
#define BIN2 5
#define PWMB 6

const int offsetA = -1;
const int offsetB = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int motorSpeed = 255;

#include <SoftwareSerial.h>
char BTcommand;
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
  BTcommand = BTserial.read();




if(BTcommand == '1'){
  brake();
  forward();
}

else if(BTcommand == '2'){
  brake();
}

else if(BTcommand == '3'){
  brake();
  delay(250);
  left();
  delay(300);
  brake();
}

else if(BTcommand == '4'){
  brake();
  delay(250);
  right();
  delay(300);
  brake();
}

else{
  brake();
}


} // loop()

//========================================================== Movement

void forward(){
  forward(motor1, motor2, motorSpeed);
}

void reverse(){
  forward(motor1, motor2, -motorSpeed);
}

void right(){
  motor1.drive(motorSpeed);
  motor2.drive(-motorSpeed);

}

void left(){
  motor1.drive(-motorSpeed);
  motor2.drive(motorSpeed);

}

void brake(){
  brake(motor1, motor2);
}
