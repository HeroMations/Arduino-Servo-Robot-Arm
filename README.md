# Arduino-Servo-Robot-Arm

A custom Arduino robot arm project using SG90 servo motors, joystick control, and an SSD1306 OLED display.

## Project Goals

- Control servo motors with Arduino
- Use joystick input for movement
- Display servo positions on OLED
- Build a custom mechanical arm structure

## Progress

- [x] Parts ordered
- [x] Single servo control
- [x] OLED angle display
- [x] Two servo arm
- [x] Three servo arm with claw

## Hardware

- Arduino UNO R3
- 3 SG90 Micro Servo Motors
- SSD1306 128x64 OLED Display
- Analog Joystick
- Plywood and screws

## How it works

The robot arm uses three SG90 servo motors:

Base servo: Rotates the arm left and right
Arm servo: Moves the arm up and down
Claw servo: Opens and closes the claw

The joystick is used to control the arm. Pressing the joystick button switches between ARM mode and CLAW mode.

The OLED displays the current servo positions and the active control mode.

## Photos
<img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/7991a875-43fc-4564-a660-e31a498a07f4" /> <img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/3972a2f0-53f3-4ef6-82a1-8225937f1630" /> <img width="300" height="300" alt="image" src="https://github.com/user-attachments/assets/17afa3c0-cc71-4a72-83ec-bd48549c8bd4" />


## Demo
https://youtu.be/sGa7yA_iKw8
# Challenges/Limitations
Claw grip: The claw initially had very little grip, especially with smooth or narrow objects. Foam was added to the gripping surfaces to improve friction, but some objects, such as pens, can still slip.

Servo torque: The SG90 servos have limited torque, so the arm is mainly capable of handling lightweight objects. It can pick up objects such as tissues, bottle caps, and a small plastic container, but heavier objects are difficult to move.

Base servo vibration: The base servo occasionally shakes while rotating, especially in one direction. This is likely caused by the weight of the arm and the mechanical load placed on the servo.

OLED code: With the code checking the angle every loop to send to the OLED to show, it made the servo slower and little more clunky to move.
