#include <Servo.h>

Servo baseServo;
Servo armServo;
Servo clawServo;

int basePos = 90; // starting position
int armPos = 90;
int clawPos = 90;
int servoSpeed;


int joystickX;
int joystickY;
int joystickButton = 7;
int joystickCenter = 512;
int deadZone = 100;
int joystickDifference;

bool lastButtonState = HIGH;
bool currentButtonState;
bool clawMode = false;

void setup() {
baseServo.attach(9); //attaches the servo to pin 9
armServo.attach(10);
clawServo.attach(11);
pinMode(joystickButton, INPUT_PULLUP);
baseServo.write(basePos); //Moves the servo to that point
armServo.write(armPos);
clawServo.write(clawPos);
delay(100);
}

void loop() {
currentButtonState = digitalRead(joystickButton);
if (lastButtonState == HIGH && currentButtonState == LOW) {
    clawMode = !clawMode;
    delay(50);
}
lastButtonState = currentButtonState;

joystickX = analogRead(A0);
joystickY = analogRead(A1);
if (!clawMode){
  if (joystickX < (joystickCenter - deadZone)){ //left
  joystickDifference = joystickCenter - joystickX;
  servoSpeed = map(joystickDifference, 0, 511, 0, 5); // Converts joystick strength from 0-511 into a servo movement speed of 0-5 
  if (basePos + servoSpeed <= 180){
    basePos += servoSpeed;
  }
  baseServo.write(basePos);
}
if (joystickX > (joystickCenter + deadZone)){ //right 
  joystickDifference = joystickX - joystickCenter;
  servoSpeed = map(joystickDifference, 0, 511, 0, 5);
  if (basePos - servoSpeed >= 0){
    basePos -= servoSpeed;
  }
  baseServo.write(basePos);
}
if (joystickY > (joystickCenter + deadZone)){ //up
  joystickDifference = joystickY - joystickCenter;
  servoSpeed = map(joystickDifference, 0, 511, 0, 5);
  if (armPos + servoSpeed <= 180){
    armPos += servoSpeed;
  }
  armServo.write(armPos);
}
if (joystickY < (joystickCenter - deadZone)){ //down
  joystickDifference = joystickCenter - joystickY;
  servoSpeed = map(joystickDifference, 0, 511, 0, 5);
  if (armPos - servoSpeed >= 0){
    armPos -= servoSpeed;
  }
  armServo.write(armPos);
}
delay(10);
}
  else{
    joystickY = analogRead(A1);
    if (joystickY > (joystickCenter + deadZone)){ //up
      joystickDifference = joystickY - joystickCenter;
      servoSpeed = map(joystickDifference, 0, 511, 0, 5);
      if (clawPos + servoSpeed <= 180){
        clawPos += servoSpeed;
      }
      clawServo.write(clawPos);
    }
    if (joystickY < (joystickCenter - deadZone)){ //down
      joystickDifference = joystickCenter - joystickY;
      servoSpeed = map(joystickDifference, 0, 511, 0, 5);
      if (clawPos - servoSpeed >= 0){
        clawPos -= servoSpeed;
      }
      clawServo.write(clawPos);
    }
delay(10);
}
}
