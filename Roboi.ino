
// Motor Pins
int motor_left = 4;
int motor_right = 5;

// HC-SR04 (NewPing Library Single Pin Mode)
#include <NewPing.h>
#define maxDistance 400

#define sensorFrontPin 7 // Shared pin for Trigger and Echo
NewPing sensorFrontPing(sensorFrontPin, sensorFrontPin, maxDistance);

int sensorFront;

//========================================================== Setup()

void setup(){ 
  
  pinMode(motor_left, OUTPUT);
  pinMode(motor_right, OUTPUT);

  Serial.begin(9600);
  
} //void setup

//========================================================== Movement

void forward(){
  digitalWrite(motor_left, HIGH);
  digitalWrite(motor_right, HIGH);
}

void halt(){
  digitalWrite(motor_left, LOW);
  digitalWrite(motor_right, LOW);
}

void right(){
  digitalWrite(motor_left, HIGH);
  digitalWrite(motor_right, LOW);
}

void left(){
  digitalWrite(motor_left, LOW);
  digitalWrite(motor_right, HIGH);
}

//========================================================== Loop()

void loop() {
delay(100);

sensorFront = sensorFrontPing.ping_cm();
Serial.println(sensorFront);

  if(sensorFront > 0 && sensorFront >= 15){
    forward();
  }

  else{
    halt();
  }


} // void loop





/* ======================================== Current Issues ::





========================================================== */
