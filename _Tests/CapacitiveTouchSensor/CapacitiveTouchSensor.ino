//12-23-2013 | SparkFun Electronics 2013 | Shawn Hymel
//SparkFun AT42QT101X


const int TOUCH_BUTTON_PIN = 3;  // Input pin for touch state
         // Pin number for LED

// Global Variables
int buttonState = 0;             // Variable for reading button

void setup() {

  pinMode(TOUCH_BUTTON_PIN, INPUT);
  Serial.begin(9600);
}

void loop() {

buttonState = digitalRead(TOUCH_BUTTON_PIN);


  if (buttonState == HIGH) {

    Serial.println("Button Pressed");
    delay(150);
  }


}
