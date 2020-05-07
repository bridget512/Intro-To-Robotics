#include <NewPing.h> // You need to install this library. 
//Go to "Tools" ^^ > "Manage libraries" > Search For "newping" > Click "Install"

// Yes, they're both on the same pin. Not a typo! It's pretty cool.
#define trig01 3
#define echo01 3
#define maxcm 400
int cm;

NewPing sensor01(trig01, echo01, maxcm);



#include <LedControl.h>

int DIN = 26;
int CS =  28;
int CLK = 30;

byte happy[8]= {0x0,0x42,0xa5,0x0,0x0,0x24,0x18,0x0};
byte neutral[8]= {0x0,0x0,0x24,0x24,0x0,0x24,0x18,0x0};
byte surprise[8]= {0x0,0x0,0x24,0x24,0x0,0x18,0x24,0x18};
byte sad[8]= {0x0,0x0,0x24,0x24,0x0,0x18,0x24,0x0};
  
LedControl lc=LedControl(DIN,CLK,CS,1);

void setup() {
  Serial.begin(9600);      

  lc.shutdown(0,false);       //The MAX72XX is in power-saving mode on startup
  lc.setIntensity(0,1);      // Set the brightness to maximum value
  lc.clearDisplay(0);         // and clear the display


}

void loop() {

cm = sensor01.ping_cm();
 Serial.println(cm); // Gets output from sensor 1
  // sad within 10cm
  // surprised within 50cm
  // neutral within 100cm
  // happy within 300cm
  
  if (cm <= 10){  
    printByte(sad);
    delay(100);   
  }
  else if (cm >= 10 && cm <= 50){  
    printByte(surprise);
    delay(100);
  }
  else if (cm >= 50 && cm <= 100){  
    printByte(neutral);
    delay(100);
  }
  else if (cm >= 100 && cm <= 200){  
    printByte(neutral);
    delay(100);
  }
  else if (cm >= 200 && cm <= 300){  
    printByte(happy);
    delay(100);
  }
  else if (cm >= 300){  
    printByte(happy);
    delay(100);
  }
    
 
   
}
void printByte(byte character [])
{
  int i = 0;
  for(i=0;i<8;i++)
  {
    lc.setRow(0,i,character[i]);
  }
}
