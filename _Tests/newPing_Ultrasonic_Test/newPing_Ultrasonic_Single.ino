#include <NewPing.h> // You need to install this library. 
//Go to "Tools" ^^ > "Manage libraries" > Search For "newping" > Click "Install"

// Yes, they're both on the same pin. Not a typo! It's pretty cool.
#define trig01 2
#define echo01 2
#define maxDistance 400

NewPing sensor01(trig01, echo01, maxDistance);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  Serial.println(sensor01.ping_cm()); // Gets output from sensor 1
}
