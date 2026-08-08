#include <Servo.h>

Servo baseServo;
int pos = 90; // starting position
int servoSpeed;


int joystickX;
int joystickCenter = 512;
int deadZone = 100;
int joystickDifference;

void setup() {
baseServo.attach(9); //attaches the servo to pin 9
baseServo.write(pos); //Moves the servo to that point
delay(100);
}

void loop() {
joystickX = analogRead(A0);
if (joystickX < (joystickCenter - deadZone)){
  joystickDifference = joystickCenter - joystickX;
  servoSpeed = map(joystickDifference, 0, 511, 0, 5); // Converts joystick strength from 0-511 into a servo movement speed of 0-5 
  if (pos - servoSpeed >= 0){
    pos -= servoSpeed;
  }
  baseServo.write(pos);
}
if (joystickX > (joystickCenter + deadZone)){
  joystickDifference = joystickX - joystickCenter;
  servoSpeed = map(joystickDifference, 0, 511, 0, 5);
  if (pos + servoSpeed <= 180){
    pos += servoSpeed;
  }
  baseServo.write(pos);
}
delay(10);
}
