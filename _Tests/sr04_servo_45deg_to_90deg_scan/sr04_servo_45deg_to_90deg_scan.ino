int debug_showsensorFrontDistance = true; // Output distance values to SerialMonitor

//Motor Controller **Connected to Arduino Mega2560
#include <SparkFun_TB6612.h> //manual download, not in library manager
#define PWMA 7
#define AIN2 8
#define AIN1 9
#define STBY 13
#define BIN1 10
#define BIN2 11
#define PWMB 12

const int offsetA = -1;
const int offsetB = -1;

Motor motor1 = Motor(AIN1, AIN2, PWMA, offsetA, STBY);
Motor motor2 = Motor(BIN1, BIN2, PWMB, offsetB, STBY);

int motorSpeed = 150;

// Servo 180d (SG90) Reference code from http://www.educ8s.tv. Modified for project.
#include <Servo.h>
Servo myservo;   
int servoPin = 40;
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
#define sensorFrontPin 41 // Shared pin for Trigger and Echo


NewPing sensorFrontPing(sensorFrontPin, sensorFrontPin, maxDistance);


int sensorFront;
int sensorFrontDistance; // Final output passed to the loop



//========================================================== Setup()

void setup(){ 
  
  Serial.begin(9600);
  myservo.attach(servoPin);  
  myservo.write(servoCenter); 

  
} //void setup

//========================================================== Loop()

void loop() {
  
  sensorFrontDistance = sensorFrontPing.ping_cm();

 
  if(debug_showsensorFrontDistance == true){Serial.println(sensorFrontDistance);}


  int distanceR = 0;
  int distanceL = 0;
  

  
  delay(50);
  int choice;
  int proxMin = 20;

 //a
 if(sensorFrontDistance <= proxMin){
  
  brake();
  delay(100);
  reverse();
  delay(300);
  brake();
  delay(200);
  distanceR = scanR90();
  delay(200);
  distanceL = scanL90();
  delay(200);


  if(distanceR >= distanceL){
    right();
    brake();
  }
  
  else{
    left();
    brake();
  }

}//a


  else{

  forward();
  
  int distanceR45 = 0;
  int distanceL45 = 0;
  
  distanceR45 = scanR45();
  delay(50);
  scanF();
  delay(50);
  distanceL45 = scanL45();
  delay(50);
  scanF();
  delay(50);
//
//  if(distanceR45 >= distanceL45){
//    right();
//    brake();
//  }
//  
//  else{
//    left();
//    brake();
//  }

if(distanceR45 < proxMin + 10){
  motor1.drive(0,0);  
  motor2.drive(0,0);
  
  motor1.drive(255,200);  
  motor2.drive(-255,200);
  
}

else if(distanceL45 < proxMin + 10){
  motor1.drive(0,0);  
  motor2.drive(0,0);
  
//  motor1.drive(motorSpeed);
//  motor2.drive(-motorSpeed);

}


  }
  
  sensorFrontDistance;

} // void loop

//========================================================== Movement

void forward(){

  if(!isMovingForward){
    isMovingForward = true;
    forward(motor1, motor2, motorSpeed);
    Serial.println("Forward!");
    
    
  }
}

void reverse(){
  isMovingForward = false;
  forward(motor1, motor2, -motorSpeed);
  Serial.println("Reverse!");

}

void right(){
  motor1.drive(motorSpeed);
  motor2.drive(-motorSpeed);
  delay(250);
  Serial.println("Turning Right!");

}

void left(){
  motor1.drive(-motorSpeed);
  motor2.drive(motorSpeed);
  delay(250);
  Serial.println("Turning Left!");

}

void brake(){
  
  brake(motor1, motor2);
  Serial.println("Braking!");

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

int scanR90(){
  Serial.println("Scanning Right 90d");
  myservo.write(servoRangeMin);
  delay(100);
  int scanDistance = sensor(sensorFront) ;
  delay(50);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;
}

int scanL90(){
  Serial.println("Scanning Left 90d");
  myservo.write(servoRangeMax);
  delay(100);
  int scanDistance = sensor(sensorFront);
  delay(50);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;
}

int scanF(){
  Serial.println("Scanning Front!");
  int scanDistance = sensor(sensorFront);
  delay(100);
  return scanDistance;
}

 int scanL45(){

//  Serial.println("Scanning Left");
  myservo.write(servoCenter + 50);
  delay(100);
  int scanDistance = sensor(sensorFront);
  delay(50);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;

 }

 int scanR45(){

//  Serial.println("Scanning Right");
  myservo.write(servoCenter - 50);
  delay(100);
  int scanDistance = sensor(sensorFront);
  delay(50);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;

 }







 
