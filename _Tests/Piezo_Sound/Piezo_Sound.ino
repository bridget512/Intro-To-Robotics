
int pin_speaker = 3;

#define Do   261
#define Re   294
#define Mi   330
#define Fa   349
#define Sol  392
#define La   440
#define Ti   494
#define Do_h 523

int soundHasPlayed = false;
int notes;
 
void setup(){
  Serial.begin(9600);
}

void loop() {
  
  if(soundHasPlayed == false){
    
    powerUp(); // Change this to happy(); to test your happy sounds!
  
  }
  else{
    noTone(pin_speaker); // We turn the sound off here if soundHasPlayed is True
  }
  
} // loop



void powerUp(){
  int note[] = {Re, Mi, Re};
  int duration[] = {150, 150, 150}; 
  //Make sure you have a duration for each note you want to play

  Serial.println("Sound: I'm Awake!!");
  for (int i = 0; i < (sizeof(note) / 2); i++){  
    tone(pin_speaker, note[i]);       // tone(pin, frequency);
    delay(duration[i]);           // time defined in the duration[] 
    noTone(pin_speaker); 
  }
  soundHasPlayed = true; 
  // Once the sound has played, it will change soundHasPlayed to true. 
  // We use this as a counter so it doesn't continue playing sound forever.

}

void happy(){
  
  // code for happy here
  // copy the code from powerUp() and adjust it to make your happy sounds!
  
}




  
  
