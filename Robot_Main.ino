//==========================================================
// Robot project for Introduction to Robotics -1711ICT
// Bridget, Cecilia, Macy
//==========================================================
// Pin Setup for Mega2560

int debug = true; // Output distance values to Serial Monitor
int enable_sweep = false; // Enable/Disable front servo to sweep and take measurements while moving
int enable_motor = true; // Enable/Disable Motor Driver

//========================================================== Motor
//Motor Controller
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

int motorSpeed = 180;

//========================================================== Servo
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

//========================================================== HC-SR04 (NewPing Library Single Pin Mode)
#include <NewPing.h>
#define maxDistance 250
#define sensorFrontPin 41 // Shared pin for Trigger and Echo

NewPing sensorFrontPing(sensorFrontPin, sensorFrontPin, maxDistance);

int sensorFront;
int sensorFrontDistance; // Final output passed to the loop

int sensorFrontRight;
int sensorFrontRightDistance; // Final output passed to the loop
int sensorFrontLeft;
int sensorFrontLeftDistance; // Final output passed to the loop

//========================================================== IR Distance Sensors
int irLeftPin = 3;
int irRightPin = 4;
int irLeft = HIGH;
int irRight = HIGH;

//========================================================== Dot Matrix Display
#include <LedControl.h>

int DIN = 22;
int CS =  24;
int CLK = 26;

byte matrix_happy[8]= {0x4,0x2,0x24,0x40,0x40,0x24,0x2,0x4};
byte matrix_neutral[8]= {0x0,0x0,0x2c,0x40,0x40,0x2c,0x0,0x0};
byte matrix_surprise[8]= {0x0,0x0,0x4c,0xa0,0xa0,0x4c,0x0,0x0};
byte matrix_sad[8]= {0x0,0x0,0x4c,0x20,0x20,0x4c,0x0,0x0};
byte matrix_left[8]= {0x0,0x0,0x0,0x4c,0x20,0x20,0x4c,0x0};
byte matrix_right[8]= {0x0,0x4c,0x20,0x20,0x4c,0x0,0x0,0x0};
byte matrix_angry[8]= {0x01,0x06,0x44,0x20,0x20,0x44,0x06,0x01};

LedControl lc=LedControl(DIN,CLK,CS,1);

//========================================================== Capacitive Touch Button
int touchButtonPin = 32;
int touchButtonState = LOW;

//========================================================== Piezo Speaker I2C to Arduino
#include <Wire.h>
#define SLAVE_ADDR 9
int playSoundNumber;

//========================================================== Bluetooth
//#include <SoftwareSerial.h>
////char BTcommand;
//int RX = 50;
//int TX = 52;
// 
//SoftwareSerial BTserial(RX, TX);
//char BTcommand;

//========================================================== Setup()
void setup(){ 
  Wire.begin();
  Serial.begin(9600);
  //BTserial.begin(9600);

  // Servo
  myservo.attach(servoPin);  
  myservo.write(servoCenter); 

  // LED Dot Matrix
  lc.shutdown(0,false);      //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,1);      // Set the brightness to maximum value
  lc.clearDisplay(0);        // and clear the display

  // Capacitive Touch Sensor
  pinMode(touchButtonPin, INPUT);
  pinMode(STBY, OUTPUT);

  // IR Obstacle Sensor
  pinMode(irLeftPin, INPUT);
  pinMode(irRightPin, INPUT);
  playSoundNumber = 1;

} //void setup

//======================================================================= START Loop()
void loop() {
  if(debug == true){Serial.println(sensorFrontDistance);}
  if(enable_motor == true){digitalWrite(STBY, HIGH);} else{digitalWrite(STBY, LOW);}

//  while (!BTserial.available());
//  BTcommand = BTserial.read();
//  Serial.println(BTcommand);
  Wire.beginTransmission(SLAVE_ADDR);
  Wire.write(playSoundNumber);
  Wire.endTransmission();

  touchButtonState = digitalRead(touchButtonPin);
  
  sensorFrontDistance = sensorFrontPing.ping_cm();
 
  int distanceR = 0;
  int distanceL = 0;
  delay(40);
  int choice;
  int proxMin = 20;

// If the robot comes to a wall, turn servo and get the distance. Largest distance wins.
 if(sensorFrontDistance >= 1 && sensorFrontDistance <= proxMin){
  brake();
  delay(100);
  reverse();
  delay(300);
  brake();
  delay(200);
  distanceR = scanRight90();
  delay(200);
  distanceL = scanLeft90();
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

// Runs the code for the IR sensors. Used as object avoidance
ir_frontCorners();

// If the robot scans left and right and the distances are less than the minimum proximitiy distance, turn around
//========================================================== Dead End
  if(sensorFrontDistance >= 1 && sensorFrontDistance <= proxMin && 
     distanceR <= proxMin && distanceL <= proxMin){
      
    playSoundNumber = 3;
    
    Wire.beginTransmission(SLAVE_ADDR);
    Wire.write(playSoundNumber);
    Wire.endTransmission();
    
    Serial.println("Action: Dead End! Turning around!");
    choice = random(1, 128);
      
    if(choice <= 64){
      right();
      right();
      brake();
    }
    
    else{
      left();
      left();
      brake();
    }
    printByte(matrix_angry);
    delay(1000);
  }

// Sometimes the front sensor throws zeros. 
//========================================================== Ultrasonic zero value handling
  else if(sensorFrontDistance == 0 ){
    if(debug == true){Serial.println("Error: Random Zero");}
  }

//========================================================== Touch Sensor

// If the sensor is touched while moving, the robot will stop and be matrix_sad
if(isMovingForward == true && touchButtonState == HIGH){
  Serial.println("Touch: You booped me!");
  playSoundNumber = 2;
  Serial.println(playSoundNumber);
  isMovingForward = false;
  printByte(matrix_sad);
  brake();
  delay(1000);
  forward();
}

// This is the default forward for the loop, don't move me!
else{
  forward();
  playSoundNumber = 0;
}
  
  sensorFrontDistance;

}//====================================================================== END Loop()

//========================================================== Movement

void forward(){
  printByte(matrix_happy);
  if(!isMovingForward){
    isMovingForward = true;
    forward(motor1, motor2, motorSpeed);
    Serial.println("Action: Moving Forward!");
  }
}

void reverse(){
  isMovingForward = false;
  forward(motor1, motor2, -motorSpeed);
  Serial.println("Action: Reverse!");
  printByte(matrix_sad);
}

void right(){
  motor1.drive(motorSpeed);
  motor2.drive(-motorSpeed);
  delay(250);
  Serial.println("Action: Turning Right!");
}

void left(){
  motor1.drive(-motorSpeed);
  motor2.drive(motorSpeed);
  delay(250);
  Serial.println("Action: Turning Left!");
}

void brake(){
  brake(motor1, motor2);
  Serial.println("Action: Braking!");
  //printByte(matrix_neutral);
}

//========================================================== Sensor and Scanning

int sensor(int sensorFront){
  delay(50);
  sensorFront = sensorFrontPing.ping_cm(); 
  if(sensorFront == 0){
    sensorFront = maxDistance;
  }
  return sensorFront; 
}

int scanRight90(){
  Serial.println("Vision: Scanning Right");
  printByte(matrix_right);
  myservo.write(servoRangeMin);
  delay(100);
  int scanDistance = sensor(sensorFront) ;
  delay(50);
  myservo.write(servoCenter);
  if(debug == true){Serial.println(scanDistance);}
  return scanDistance;
}

int scanLeft90(){
  Serial.println("Vision: Scanning Left");
  printByte(matrix_left);
  myservo.write(servoRangeMax);
  delay(100);
  int scanDistance = sensor(sensorFront);
  delay(50);
  myservo.write(servoCenter);
  if(debug == true){Serial.println(scanDistance);}
  return scanDistance;
}

//========================================================== Face
void printByte(byte character []){
  int i = 0;
  
  for(i=0;i<8;i++){
    lc.setRow(0,i,character[i]);
  }
}

//========================================================== IR Obstacle Sensors
void ir_frontCorners(){
  irLeft = digitalRead(irLeftPin);
  irRight = digitalRead(irRightPin);


  if(isMovingForward == true && irLeft == LOW){
    printByte(matrix_left);
    Serial.println("Too close on left ir_frontCorners!");
    isMovingForward = false;
    motor1.drive(motorSpeed - 80);
    motor2.drive(-motorSpeed +80);
    delay(200);
  }

  if(isMovingForward == true && irRight == LOW){
    printByte(matrix_right);
    Serial.println("Too close on right ir_frontCorners!");
    isMovingForward = false;
    motor1.drive(-motorSpeed + 80);
    motor2.drive(motorSpeed - 80);
    delay(200);
    
  }
}

//========================================================== Bluetooth - not working yet, probably wont
//void bluetooth(){
//  while (!BTserial.available());
//  BTcommand = BTserial.read();
