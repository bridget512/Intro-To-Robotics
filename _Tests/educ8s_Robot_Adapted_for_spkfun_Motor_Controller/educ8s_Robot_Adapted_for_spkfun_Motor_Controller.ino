   //////////////////////////////////////////////
  //          Arduino ROBOT v0.1              //
 //                                          //
//           http://www.educ8s.tv           //
/////////////////////////////////////////////


#include <NewPing.h>
#include <Servo.h> 
#include <SparkFun_TB6612.h> //manual download, not in library manager

#define sensorFrontPin 2 // Shared pin for Trigger and Echo
#define MAX_DISTANCE 350 

NewPing sonar(sensorFrontPin, sensorFrontPin, MAX_DISTANCE); 

//Motor Controller

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

Servo myservo;   

int servoPin = 13;
int servoRange = 180; // Total rotation of servo. SG90
int servoCenter = servoRange / 2; 
int servoEdgeOffset = 50; 
int servoRangeMin = servoRange - servoRange + servoEdgeOffset;
int servoRangeMax = servoRange - servoEdgeOffset;



boolean goesForward=false;
int distance = 100;


void setup(){
  Serial.begin(9600);
  myservo.attach(servoPin);  
  myservo.write(servoCenter); 
  delay(2000);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
  distance = readPing();
  delay(100);
}

void loop(){
 int distanceR = 0;
 int distanceL = 0;
 delay(40);
 
 if(distance<=25){
  moveStop();
  delay(100);
  moveBackward();
  delay(300);
  moveStop();
  delay(200);
  distanceR = lookRight();
  delay(200);
  distanceL = lookLeft();
  delay(200);

  if(distanceR>=distanceL){
    turnRight();
    moveStop();
  }
  
  else{
    turnLeft();
    moveStop();
  }
 }
 
 else{
  moveForward();
 }
 distance = readPing();
}

int lookRight(){
    myservo.write(servoRangeMin); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(servoCenter); 
    return distance;
}

int lookLeft(){
    myservo.write(servoRangeMax); 
    delay(500);
    int distance = readPing();
    delay(100);
    myservo.write(servoCenter); 
    return distance;
    delay(100);
}

int readPing(){ 
  delay(70);
  
  int cm = sonar.ping_cm();
  
  if(cm==0){
    cm = 250;
  }
  
  Serial.println(cm);
  return cm;
}

void moveStop() {
  brake(motor1, motor2);
} 
  
void moveForward(){

 if(!goesForward) {
    goesForward=true;
  forward(motor1, motor2, motorSpeed);    

  }
}

void moveBackward(){
  goesForward=false;
  forward(motor1, motor2, -motorSpeed);
}  

void turnRight(){
  motor1.drive(motorSpeed);
  motor2.drive(-motorSpeed);
  delay(500);
} 
 
void turnLeft(){
  motor1.drive(-motorSpeed);
  motor2.drive(motorSpeed);
  delay(500);
}  
