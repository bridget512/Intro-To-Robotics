//Motor Controller
#include <SparkFun_TB6612.h>
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

// HC-SR04 (NewPing Library Single Pin Mode)
#include <NewPing.h>
#define maxDistance 500
#define sensorFrontPin 2 // Shared pin for Trigger and Echo
NewPing sensorFrontPing(sensorFrontPin, sensorFrontPin, maxDistance);

int sensorFront;
int sensorFrontValue; // Final output passed to the loop

// Sketch wide variables


//========================================================== Setup()

void setup(){ 
  Serial.begin(115200);
} //void setup

//========================================================== Movement

void forward(){
  forward(motor1, motor2, 200);
  Serial.println("Forward!");
}

void right(){
  motor1.drive(255);
  Serial.println("Turning Right!");
}

void left(){
  motor2.drive(255);
  Serial.println("Turning Left!");
}

void brake(){
  brake(motor1, motor2);
}

int sensor(int sensorFront){
  sensorFront = sensorFrontPing.ping_cm(); 
  return sensorFront; 
}


//========================================================== Loop()

void loop() {

  sensorFrontValue = sensor(sensorFront);
  Serial.println(sensorFrontValue);

  if(sensorFrontValue > 0 && sensorFrontValue >= 25){
    forward(); 
  }

  else if( sensorFrontValue > 5 && sensorFrontValue <= 25){
    brake();
    right();
  }

  else{
    brake();
  }

delay(25);
  
} // void loop
