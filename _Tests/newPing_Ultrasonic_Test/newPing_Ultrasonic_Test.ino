#include <NewPing.h>

// Yes, they're both on pin 7. Not a typo!
#define trig01 7
#define echo01 7
#define maxDistance 200

NewPing sensor01(trig01, echo01, maxDistance);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  Serial.println(sensor01.ping_cm()); // Gets output from sensor 1
}
