#include <ezButton.h>
#include <Servo.h>

//Left motor
#define L_1A 3
#define L_1B 9
//Right motor
#define R_1A 10
#define R_1B 11

//Servo pins
#define ClubPin = 3;
int stop = 90;
Servo Club;
int motorpin = 8;

//Joystick
#define VRX_PIN A4 // Arduino pin connected to VRX pin
#define VRY_PIN A5 // Arduino pin connected to VRY pin
#define SW_PIN 8  // Arduino pin connected to SW  pin
ezButton button(SW_PIN);

#define stop 0
#define delayTime 100

long x = 0;
long y = 0;
int b = 0;
bool wasPressed = false;
long speed;


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

//function signatures
void forward();
void right();
void left();
void backward();
void brake();

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

  long speedt = sqrt((x-510)*(x-510)+(y-513)*(y-513));

  if (speedt < 30) {
    speed = 0;
  } else if (speedt <= 256){
    speed = 100;
  } else {
    speed = 200;
  }
  
  if (y >= x && y >= 1024-x) {
    forward(speed);
    Serial.println("forward");
  } else if (y <= x && y <= 1024-x) {
    backward(speed);
    Serial.println("backward");
  } else if (y <= x && y >= 1024-x) {
    left(speed);
    Serial.println("left");
  } else {
    right(speed);
    Serial.println("right");
  }
  
  Serial.print("x = ");
  Serial.print(x);
  Serial.print(", y = ");
  Serial.println(y);
  Serial.println((x-510)*(x-510));
  Serial.println((y-513)*(y-513));
  Serial.println(speed);
  delay(1000);
}

//Functions

void forward(int speed) {
  analogWrite(L_1A, stop);
  analogWrite(L_1B, speed);
  analogWrite(R_1A, stop);
  analogWrite(R_1B, speed);
}

void right(int speed) {
  analogWrite(L_1A, stop);
  analogWrite(L_1B, speed);
  analogWrite(R_1A, speed);
  analogWrite(R_1B, stop);
}

void left(int speed) {
  analogWrite(L_1A, speed);
  analogWrite(L_1B, stop);
  analogWrite(R_1A, stop);
  analogWrite(R_1B, speed);
}

void backward(int speed) {
  analogWrite(L_1A, speed);
  analogWrite(L_1B, stop);
  analogWrite(R_1A, speed);
  analogWrite(R_1B, stop);
}

void brake() {
  analogWrite(L_1A, stop);
  analogWrite(L_1B, stop);
  analogWrite(R_1A, stop);
  analogWrite(R_1B, stop);
}
