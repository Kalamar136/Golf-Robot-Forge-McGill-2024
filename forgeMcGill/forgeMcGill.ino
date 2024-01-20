#include <ezButton.h>
#include <Servo.h>

#define L_1A 3
#define L_1B 2
#define R_1A 4
#define R_1B 5

#define ClubPin = 3;
int stop = 90;
Servo Club;
int motorpin = 8;

//Joystick
#define VRX_PIN A4 // Arduino pin connected to VRX pin
#define VRY_PIN A5 // Arduino pin connected to VRY pin
#define SW_PIN 8  // Arduino pin connected to SW  pin
ezButton button(SW_PIN);

int x = 0;
int y = 0;
int b = 0;
bool wasPressed = false;

void setup() {
  //Right motor setup
  pinMode(L_1A, OUTPUT);
  pinMode(L_1B, OUTPUT);
  pinMode(R_1A, OUTPUT);
  pinMode(R_1B, OUTPUT);
  
  //Club setup
  Club.attach(9);
  Club.write(90);

  Serial.begin(9600);
  
  button.setDebounceTime(50); // set debounce time to 50 milliseconds
}

void forward() {
  digitalWrite(L_1A, LOW);
  digitalWrite(L_1B, HIGH);
  digitalWrite(R_1A, LOW);
  digitalWrite(R_1B, HIGH);
  delay(100);
}

void right() {
  digitalWrite(L_1A, LOW);
  digitalWrite(L_1B, HIGH);
  digitalWrite(R_1A, HIGH);
  digitalWrite(R_1B, LOW);
  delay(100);
}

void left() {
  digitalWrite(L_1A, HIGH);
  digitalWrite(L_1B, LOW);
  digitalWrite(R_1A, LOW);
  digitalWrite(R_1B, HIGH);
  delay(100);
}

void backward() {
  digitalWrite(L_1A, HIGH);
  digitalWrite(L_1B, LOW);
  digitalWrite(R_1A, HIGH);
  digitalWrite(R_1B, LOW);
  delay(100);
}

void brake() {
  digitalWrite(L_1A, LOW);
  digitalWrite(L_1B, LOW);
  digitalWrite(R_1A, LOW);
  digitalWrite(R_1B, LOW);
  delay(100);
}

void loop() {

  //myservo.write(45);
  //delay(2000);

  //myservo.write(135);
  //delay(2000);

  //myservo.write(90);
  //delay(2000);

  // put your main code here, to run repeatedly:
  button.loop(); // MUST call the loop() function first
  x = analogRead(VRX_PIN);
  y = analogRead(VRY_PIN);
  // Read the button value
  b = button.getState();

  if (button.isPressed()) {
    Serial.println("The button is pressed");
    // TODO do something here
  }

  if (button.isReleased()) {
    Serial.println("The button is released");
    // TODO do something here
    wasPressed = !wasPressed;
  }

  if (!wasPressed) {
    brake();
  } else {
    if (x > 950) {
      right();
    } else if (x < 74) {
      left();
    } else if (y > 950) {
      forward();
    } else if (y < 74) {
      backward();
    } else {
      brake();
    }
  }
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.println(y);
  delay(100);
}

//Functions














