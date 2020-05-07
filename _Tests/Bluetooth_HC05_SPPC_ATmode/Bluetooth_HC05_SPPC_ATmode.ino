// Click the reset button on the arduino after loading sketch!

#include <SoftwareSerial.h>
// Remember! Arduino TX goes to Bluetooth RX! & Arduino RX goes to Bluetooth TX!
// Either switch them in code, or switch them via wiring
int RX = 7;
int TX = 8;

SoftwareSerial BTSerial(RX, TX);

void setup(){
  
  pinMode(9, OUTPUT); // Used to put the module in to AT mode (only for testing, don't use in a sketch)
  digitalWrite(9, HIGH); 
  Serial.begin(9600);
  Serial.println("Enter AT commands:");
  BTSerial.begin(9600);
  
}

void loop(){

  // Keep reading from HC-05 and send to Arduino Serial Monitor
  if (BTSerial.available())
    Serial.write(BTSerial.read());

  // Keep reading from Arduino Serial Monitor and send to HC-05
  if (Serial.available())
    BTSerial.write(Serial.read());
}
