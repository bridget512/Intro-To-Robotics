
int motorLeft = 4;
int motorRight = 5;

void setup() {
  pinMode(motorLeft, OUTPUT);
  pinMode(motorRight, OUTPUT);
}

void loop() {
  digitalWrite(motorLeft, LOW);
  digitalWrite(motorRight, LOW);
}
