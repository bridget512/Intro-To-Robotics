#include <NewPing.h> // You need to install this library. 
//Go to "Tools" ^^ > "Manage libraries" > Search For "newping" > Click "Install"

// Yes, they're both on the same pin. Not a typo! It's pretty cool.
#define trig01 3
#define echo01 3
#define maxDistance 400
int cm;

NewPing sensor01(trig01, echo01, maxDistance);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  cm = sensor01.ping_cm();
  Serial.println(cm); // Gets output from sensor 1
}
