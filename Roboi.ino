int debug_showsensorFrontDistance = true; // Output distance values to SerialMonitor

//Motor Controller
#include <SparkFun_TB6612.h> //manual download, not in library manager
#define PWMA 12
#define AIN2 11
#define AIN1 10
#define STBY 13
#define BIN1 9
#define BIN2 8
#define PWMB 7

const int offsetA = -1;
const int offsetB = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int motorSpeed = 180;

// Servo 180d (SG90) Reference code from http://www.educ8s.tv. Modified for project.
#include <Servo.h>
Servo myservo;   
int servoPin = 2;
int servoRange = 180; // Total rotation of servo. SG90
int servoCenter = 85; 
int servoEdgeOffset = 0; 
int servoRangeMin = servoRange - servoRange + servoEdgeOffset + 5;
int servoRangeMax = servoRange - servoEdgeOffset + 5;

boolean isMovingForward = false;
int distance = 100;
int scanDistance;

// HC-SR04 (NewPing Library Single Pin Mode)
#include <NewPing.h>
#define maxDistance 350
#define sensorFrontPin 3 // Shared pin for Trigger and Echo

NewPing sensorFrontPing(sensorFrontPin, sensorFrontPin, maxDistance);

int sensorFront;
int sensorFrontDistance; // Final output passed to the loop

// Dot Matrix Display
#include <LedControl.h>

int DIN = 26;
int CS =  28;
int CLK = 30;

byte happy[8]= {0x4,0x2,0x24,0x40,0x40,0x24,0x2,0x4};
byte neutral[8]= {0x0,0x0,0x2c,0x40,0x40,0x2c,0x0,0x0};
byte surprise[8]= {0x0,0x0,0x4c,0xa0,0xa0,0x4c,0x0,0x0};
byte sad[8]= {0x0,0x0,0x4c,0x20,0x20,0x4c,0x0,0x0};

LedControl lc=LedControl(DIN,CLK,CS,1);

//#include <SoftwareSerial.h>
//char BTcommand;
//int RX = 42;
//int TX = 40;
// 
//SoftwareSerial BTserial(RX, TX);

//========================================================== Setup()

void setup(){ 
  
  Serial.begin(9600);
  myservo.attach(servoPin);  
  myservo.write(servoCenter); 

  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,1);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display
  
} //void setup

//========================================================== Loop()

void loop() {

 sensorFrontDistance = sensorFrontPing.ping_cm(); ;
  
  if(debug_showsensorFrontDistance == true){Serial.println(sensorFrontDistance);}


  int distanceR = 0;
  int distanceL = 0;
  delay(40);

    
 if(sensorFrontDistance <= 25){
  brake();
  delay(100);
  reverse();
  delay(300);
  brake();
  delay(200);
  distanceR = scanRight();
  delay(200);
  distanceL = scanLeft();
  delay(200);


  
    
  
  if(distanceR >= distanceL){
    right();
    brake();
  }
  
  else{
    left();
    brake();
  }
}
 
  else{
    forward();
  }



  
  sensorFrontDistance;

} // void loop

//========================================================== Movement

void forward(){
  if(!isMovingForward){
    isMovingForward = true;
    forward(motor1, motor2, motorSpeed);
    Serial.println("Forward!");
    printByte(happy);
  }
}

void reverse(){
  isMovingForward = false;
  forward(motor1, motor2, -motorSpeed);
  Serial.println("Reverse!");
  printByte(sad);
}

void right(){
  motor1.drive(motorSpeed);
  motor2.drive(-motorSpeed);
  delay(300);
  Serial.println("Turning Right!");
  printByte(surprise);
}

void left(){
  motor1.drive(-motorSpeed);
  motor2.drive(motorSpeed);
  delay(300);
  Serial.println("Turning Left!");
  printByte(surprise);
}

void brake(){
  
  brake(motor1, motor2);
  Serial.println("Braking!");
  printByte(neutral);
}

//========================================================== Sensor and Scanning

int sensor(int sensorFront){
  delay(50);
  sensorFront = sensorFrontPing.ping_cm(); 
  if(sensorFront == 0){
    sensorFront = 250;
  }
  return sensorFront; 
}

int scanRight(){
  Serial.println("Scanning Right");
  myservo.write(servoRangeMin);
  delay(100);
  int scanDistance = sensor(sensorFront) ;
  //delay(50);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;
}

int scanLeft(){
  Serial.println("Scanning Left");
  myservo.write(servoRangeMax);
  delay(100);
  int scanDistance = sensor(sensorFront);
  //delay(50);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;
}

//========================================================== Face
void printByte(byte character []){
  int i = 0;
  
  for(i=0;i<8;i++){
    lc.setRow(0,i,character[i]);
  }
}

//========================================================== Bluetooth - not working yet

//void bluetooth(){
//  while (!BTserial.available());
//  BTcommand = BTserial.read();
//
//  if(BTcommand == '1'){
//    brake();
//    forward();
//  }
//  
//  else if(BTcommand == '2'){
//    brake();
//  }
//  
//  else if(BTcommand == '3'){
//    brake();
//    delay(250);
//    left();
//    delay(300);
//    brake();
//  }
//  
//  else if(BTcommand == '4'){
//    brake();
//    delay(250);
//    right();
//    delay(300);
//    brake();
//  }
//  
//  else{
//    brake();
//  }
//}
