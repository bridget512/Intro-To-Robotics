#include <Wire.h>
#define SLAVE_ADDR 9
int rd;

int pin_speaker = 2;
int soundHasPlayed = false;
int notes;
#define Do   261
#define Re   294
#define Mi   330
#define Fa   349
#define Sol  392
#define La   440
#define Ti   494
#define Do_h 523

void setup() {
  Wire.begin(SLAVE_ADDR);
  Wire.onReceive(receiveEvent);
  Serial.begin(9600);
  Serial.println("I2C Slave Demonstration");
}

void receiveEvent() {
  rd = Wire.read();
}

void loop() {
  delay(50);
  Serial.println(rd);

  if(rd == 1 && soundHasPlayed == false){
    powerUp(); 
  }

  else if(rd == 2 && soundHasPlayed == false){
    happy(); 
  }

  else if(rd == 3 && soundHasPlayed == false){
    sad(); 
  }

  
  else{
    noTone(pin_speaker);
    soundHasPlayed = false;
  }

 
}


void powerUp(){
  int note[] = {Re, Mi};
  int duration[] = {150, 150}; 

  Serial.println("Sound: I'm Awake!!");
  for (int i = 0; i < (sizeof(note) / 2); i++){  
    tone(pin_speaker, note[i]);
    delay(duration[i]);
    noTone(pin_speaker); 
  }
  soundHasPlayed = true; 
}

void happy(){
  int note[] = {Mi,Sol, Do_h};
  int duration[] = {150, 150, 150}; //Make sure you have a duration for each note you want to play

  Serial.println("Sound: I'm Awake!!");
  for (int i = 0; i < (sizeof(note) / 2); i++){  
    tone(pin_speaker, note[i]);       // tone(pin, frequency);
    delay(duration[i]);           // time defined in the duration[] 
    noTone(pin_speaker); 
  
  soundHasPlayed = true;
  }
}

void sad(){
  int note[] = {Mi, Sol, Ti};
  int duration[] = {150, 150, 150}; //Make sure you have a duration for each note you want to play

  Serial.println("Sound: I'm Awake!!");
  for (int i = 0; i < (sizeof(note) / 2); i++){  
    tone(pin_speaker, note[i]);       // tone(pin, frequency);
    delay(duration[i]);           // time defined in the duration[] 
    noTone(pin_speaker); 
  
  soundHasPlayed = true;
  }
}
