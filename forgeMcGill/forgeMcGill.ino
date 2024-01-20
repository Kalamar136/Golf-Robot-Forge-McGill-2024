#include <ezButton.h>
#include <Servo.h>

//Left motor
#define L_1A A2
#define L_1B A3
//Right motor
#define R_1A A0
#define R_1B A1

//Servo pins
int stop = 90;
Servo Club;

//Drive Joystick
#define VRX_PIN_Drive A4 // Arduino pin connected to VRX1 pin
#define VRY_PIN_Drive A5 // Arduino pin connected to VRY1 pin
#define SW_PIN_Drive 8  // Arduino pin connected to SW1  pin
ezButton button_Drive(SW_PIN_Drive);

#define VRX_PIN_Club A6 // Arduino pin connected to VRX1 pin
#define VRY_PIN_Club A7 // Arduino pin connected to VRY1 pin
#define SW_PIN_Club 9  // Arduino pin connected to SW1  pin
ezButton button_Club(SW_PIN_Club);

int x_D = 0;
int y_D = 0;
int b_D = 0;
bool wasPressedDrive = false;

int x_C = 0;
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
void forward();
void right();
void left();
void backward();
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

  forward(x_D);
  Serial.print("x_D = ");
  Serial.print(x_D);
  Serial.print(", y_D = ");
  Serial.println(y_D);
  delay(100);



//Club

  x_C = analogRead(VRX_PIN_Club);
  y_C = analogRead(VRY_PIN_Club);
  // Read the button value
  b_C = button_Club.getState();

  if (button_Club.isPressed()) {
    Serial.println("The club button is pressed");
    wasPressedClub = true;

    // TODO do something here

    //move the club forward
    if((y_C >= 768) && (position_C > 0)){
      moveClub(1);
      position_C -= 1;
    }
    //move the club backwards
    else if(y_C <= 256){
      moveClub(-1);
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

}

//Functions

void forward(int speed) {
  analogWrite(L_1A, abs(speed-513)/2);
  analogWrite(L_1B, abs(speed-513)/2);
  analogWrite(R_1A, abs(speed-513)/2);
  analogWrite(R_1B, abs(speed-513)/2);
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

void shoot(){
  myservo.write(135);
  delay(200*position_C);
  myservo.write(90);
}

void moveClub(int direction){
  myservo.write(90 + direction*45);
  delay(200);
  myservo.write(90);

}
