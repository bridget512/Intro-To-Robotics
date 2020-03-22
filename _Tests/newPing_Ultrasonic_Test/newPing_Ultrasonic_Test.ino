#include <NewPing.h>

#define trig01 7
#define echo01 7

#define trig02 8
#define echo02 8
#define maxDistance 200

NewPing sensor01(trig01, echo01, maxDistance);
NewPing sensor02(trig02, echo02, maxDistance);

void setup() {
  Serial.begin(9600);
}

void loop() {
  delay(50);
  Serial.println(sensor01.ping_cm());
  delay(50);
  Serial.println(sensor02.ping_cm());
}
