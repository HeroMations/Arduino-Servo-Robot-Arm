#include <Servo.h> // Servo library
#include <Adafruit_GFX.h> // Graphics library used for drawing text/shapes
#include <Adafruit_SSD1306.h> // Library for controlling the SSD1306 OLED display

// OLED display dimensions
#define SCREEN_WIDTH 128 
#define SCREEN_HEIGHT 64

Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);
Servo baseServo;
Servo armServo;
Servo clawServo;

int basePos = 90; // starting positions
int armPos = 90;
int clawPos = 90;
int servoSpeed;

// Joystick button and center calibration
int joystickX;
int joystickY;
int joystickButton = 7;
int joystickCenter = 512;
int deadZone = 100;
int joystickDifference;

// Button and control mode states
bool lastButtonState = HIGH;
bool currentButtonState;
bool clawMode = false;


void setup() {
baseServo.attach(9); //attaches the servo to pins
armServo.attach(10);
clawServo.attach(11);
pinMode(joystickButton, INPUT_PULLUP);
baseServo.write(basePos); //Moves the servo to that point
armServo.write(armPos);
clawServo.write(clawPos);
display.begin(SSD1306_SWITCHCAPVCC, 0x3C); 
Wire.setClock(400000); // Increase the I2C communication speed
delay(100);
}

void showAngle(){ // Displays the current servo angles and control mode
display.clearDisplay();
display.setTextSize(1);
display.setTextColor(WHITE);
display.setCursor(10,10);
display.println("    Robot Arm");
display.setCursor(5, 20);
display.print("Base:");
display.print(basePos);
display.println(" degrees");
display.setCursor(5, 30);
display.print("Arm:");
display.print(armPos);
display.println(" degrees");
display.setCursor(5, 40);
display.print("Claw:");
display.print(clawPos);
display.println(" degrees");
display.setCursor(5, 55);
display.print("MODE: ");
if (clawMode == true){
  display.print("CLAW");
}
else{
  display.print("ARM");
}
display.display();
}

void loop() {
currentButtonState = digitalRead(joystickButton);
if (lastButtonState == HIGH && currentButtonState == LOW) {
    clawMode = !clawMode;
    delay(50);
}
showAngle();
lastButtonState = currentButtonState;
joystickX = analogRead(A0);
joystickY = analogRead(A1);
if (!clawMode){ // Switch between ARM and CLAW mode when the button is pressed
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
}
  else{
    joystickY = analogRead(A1);
    if (joystickY > (joystickCenter + deadZone)){ //up/closing
      joystickDifference = joystickY - joystickCenter;
      servoSpeed = map(joystickDifference, 0, 511, 0, 5);
      if (clawPos + servoSpeed <= 180){
        clawPos += servoSpeed;
      }
      clawServo.write(clawPos);
    }
    if (joystickY < (joystickCenter - deadZone)){ //down/opening
      joystickDifference = joystickCenter - joystickY;
      servoSpeed = map(joystickDifference, 0, 511, 0, 5);
      if (clawPos - servoSpeed >= 0){
        clawPos -= servoSpeed;
      }
      clawServo.write(clawPos);
    }
}
}
