#include <Servo.h>

Servo baseServo;
Servo armServo;
int basePos = 90; // starting position
int armPos = 90;
int servoSpeed;


int joystickX;
int joystickY;
int joystickCenter = 512;
int deadZone = 100;
int joystickDifference;

void setup() {
baseServo.attach(9); //attaches the servo to pin 9
armServo.attach(10);
baseServo.write(basePos); //Moves the servo to that point
armServo.write(armPos);
delay(100);
}

void loop() {
joystickX = analogRead(A0);
joystickY = analogRead(A1);
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
