int debug_showsensorFrontDistance = true; // Output distance values to SerialMonitor

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

// Servo 180d (SG90) Reference code from http://www.educ8s.tv. Modified for project.
#include <Servo.h>
Servo myservo;   
int servoPin = 13;
int servoRange = 180; // Total rotation of servo. SG90
int servoCenter = 80;//servoRange / 2; 
int servoEdgeOffset = 0; 
int servoRangeMin = servoRange - servoRange + servoEdgeOffset;
int servoRangeMax = servoRange - servoEdgeOffset;

boolean isMovingForward = false;
int distance = 100;
int scanDistance;

// HC-SR04 (NewPing Library Single Pin Mode)
#include <NewPing.h>
#define maxDistance 350
#define sensorFrontPin 2 // Shared pin for Trigger and Echo

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

  sensorFrontDistance = sensor(sensorFront);
  
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
  delay(300);
  Serial.println("Turning Right!");
}

void left(){
  motor1.drive(-motorSpeed);
  motor2.drive(motorSpeed);
  delay(300);
  Serial.println("Turning Left!");
}

void brake(){
  brake(motor1, motor2);
  Serial.println("Braking!");
}

//========================================================== Sensor and Scanning

int sensor(int sensorFront){
  delay(70);
  sensorFront = sensorFrontPing.ping_cm(); 
  if(sensorFront == 0){
    sensorFront = 250;
  }
  return sensorFront; 
}

int scanRight(){
  Serial.println("Scanning Right");
  myservo.write(servoRangeMin);
  delay(500);
  int scanDistance = sensor(sensorFront) ;
  delay(100);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;
}

int scanLeft(){
  Serial.println("Scanning Left");
  myservo.write(servoRangeMax);
  delay(500);
  int scanDistance = sensor(sensorFront);
  delay(100);
  myservo.write(servoCenter);
  Serial.println(scanDistance);
  return scanDistance;
}


