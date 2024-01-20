#include <Servo.h>

//Right motor
#define A_1ARight 2
#define A_1BRight 3
//Left motor
#define A_1ALeft 4
#define A_1BLeft 5

#define ClubPin = 3;
int stop = 90;
Servo Club;

void setup() {
  //Right motor setup
  pinMode(A_1ARight, OUTPUT);
  pinMode(A_1ARight, OUTPUT);
  //Left motor setup
  pinMode(A_1ALeft, OUTPUT);
  pinMode(A_1ALeft, OUTPUT);
  
  //Club setup
  Club.attach(motorPin);
  Club.write(90);

}

//Function signatures
void forward(int A_1A, int A_1B);
void backward(int A_1A, int A_1B);
void brake(int A_1A, int A_1B);

void loop() {
  forward();
  brake();
  backward();
  brake();

  myservo.write(45);
  delay(2000);

  myservo.write(135);
  delay(2000);

  myservo.write(90);
  delay(2000);
}

//Functions

void forward(int A_1A, int A_1B) {
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, HIGH);
  delay(1000);
}

void backward(int A_1A, int A_1B) {
  digitalWrite(A_1A, HIGH);
  digitalWrite(A_1B, LOW);
  delay(1000);
}

void brake(int A_1A, int A_1B) {
  digitalWrite(A_1A, LOW);
  digitalWrite(A_1B, LOW);
  delay(1000);
}