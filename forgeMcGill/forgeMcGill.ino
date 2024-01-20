#include <ezButton.h>
#include <Servo.h>

//Left motor
#define L_1A 3
#define L_1B 9
//Right motor
#define R_1A 10
#define R_1B 11

//Servo pins
int stop = 90;
Servo Club;

//Drive Joystick
#define VRX_PIN_Drive A4 // Arduino pin connected to VRX1 pin
#define VRY_PIN_Drive A5 // Arduino pin connected to VRY1 pin
#define SW_PIN_Drive 8  // Arduino pin connected to SW1  pin
ezButton button_Drive(SW_PIN_Drive);

#define stop 0
#define delayTime 100

#define VRY_PIN_Club A6 // Arduino pin connected to VRY1 pin
#define SW_PIN_Club 9  // Arduino pin connected to SW1  pin
ezButton button_Club(SW_PIN_Club);

long x_D = 0;
long y_D = 0;
int b_D = 0;
bool wasPressedDrive = false;
long speed;


int y_C = 0;
int b_C = 0;
int position_C = 0;
bool wasPressedClub = false;

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
  
  button_Drive.setDebounceTime(50); // set debounce time to 50 milliseconds
  button_Club.setDebounceTime(50); // set debounce time to 50 milliseconds
}

//function signatures
void forward(int);
void right(int);
void left(int);
void backward(int);
void brake();
void shoot();
void moveClub(int angle);

void loop() {

  // put your main code here, to run repeatedly:
  button_Drive.loop(); // MUST call the loop() function first
  button_Club.loop(); // MUST call the loop() function first

//Drive
  x_D = analogRead(VRX_PIN_Drive);
  y_D = analogRead(VRY_PIN_Drive);
  // Read the button value
  b_D = button_Drive.getState();

  if (button_Drive.isPressed()) {
    Serial.println("The drive button is pressed");
    wasPressedDrive = true;
    // TODO do something here
  }

  if (button_Drive.isReleased()) {
    Serial.println("The drive button is released");
    // TODO do something here
    wasPressedDrive = !wasPressedDrive;
    Serial.println("Shoot!");
    shoot();
  }

  //Drive subsystem
  long speedt = sqrt((x_D-510)*(x_D-510)+(y_D-513)*(y_D-513));

  if (speedt < 30) {
    speed = 0;
  } else if (speedt <= 256){
    speed = 100;
  } else {
    speed = 200;
  }
  
  if (y_D >= x_D && y_D >= 1024-x_D) {
    forward(speed);
    Serial.println("forward");
  } else if (y_D <= x_D && y_D <= 1024-x_D) {
    backward(speed);
    Serial.println("backward");
  } else if (y_D <= x_D && y_D >= 1024-x_D) {
    left(speed);
    Serial.println("left");
  } else {
    right(speed);
    Serial.println("right");
  }
  
  Serial.print("x = ");
  Serial.print(x_D);
  Serial.print(", y = ");
  Serial.println(y_D);
  Serial.println((x_D-510)*(x_D-510));
  Serial.println((y_D-513)*(y_D-513));
  Serial.println(speed);
  delay(100);

  //Club Subsystem
  y_C = analogRead(VRY_PIN_Club);
  // Read the button value
  b_C = button_Club.getState();

  if (button_Club.isPressed()) {
    Serial.println("The club button is pressed");
    wasPressedClub = true;

    // TODO do something here

    //move the club forward
    if((y_C >= 768) && (position_C > 0)){
      moveClub(-1);
      position_C -= 1;
    }
    //move the club backwards
    else if(y_C <= 256){
      moveClub(1);
      position_C += 1;
    }
    else{

    }
  }

  if (button_Club.isReleased()) {
    Serial.println("The club button is released");
    // TODO do something here
    wasPressedClub = !wasPressedClub;
  }

  
  Serial.print(", y_C = ");
  Serial.println(y_C);
  delay(100);
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

void shoot(){
  Club.write(135);
  delay(200*position_C);
  Club.write(90);
}

void moveClub(int direction){
  Club.write(90 - direction*45);
  delay(200);
  Club.write(90);

}
