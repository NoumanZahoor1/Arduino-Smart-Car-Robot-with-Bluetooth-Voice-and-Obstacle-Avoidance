<img width="1536" height="1024" alt="roobot" src="https://github.com/user-attachments/assets/ed69bacb-d109-4c59-832c-077d81133901" />

<img width="1536" height="1024" alt="robot" src="https://github.com/user-attachments/assets/f37e1462-ed27-49aa-b2fb-043b736a7536" />

Arduino Smart Car Robot
Overview

This project is a Smart Robotic Car built using Arduino Uno, L293D Motor Shield, Ultrasonic Sensor, Servo Motor, and Bluetooth Module.

The robot supports three different operating modes:

Bluetooth Control
Voice Control
Obstacle Avoidance

The ultrasonic sensor detects obstacles while the servo motor scans the environment to determine the best direction for movement.

Features
Bluetooth Control

Control the robot using a smartphone Bluetooth application.

Commands:

Command	Action
F	Forward
B	Backward
L	Left
R	Right
S	Stop
Voice Control

Control the robot through voice commands converted into serial characters.

Command	Action
^	Forward
-	Backward
<	Left
>	Right
*	Stop
Obstacle Avoidance

The robot:

Detects obstacles using HC-SR04.
Stops when an object is too close.
Scans left and right.
Chooses the direction with more free space.
Continues moving automatically.
Hardware Components
Component	Quantity
Arduino Uno	1
L293D Motor Shield	1
HC-SR04 Ultrasonic Sensor	1
SG90 Servo Motor	1
HC-05 Bluetooth Module	1
DC Motors	4
Chassis	1
Battery Pack	1
Pin Connections
Component	Arduino Pin
Echo	A0
Trigger	A1
Servo	D10
Libraries Used
#include <Servo.h>
#include <AFMotor.h>
Installation
Install Arduino IDE.
Install AFMotor Library.
Install Servo Library.
Upload the code to Arduino Uno.
Connect the hardware.
Power the robot.
Future Improvements
Mobile App Integration
WiFi Control
Camera Streaming
AI-Based Object Detection
GPS Navigation
Author

Nouman Zahoor

BS Computer Science

COMSATS University Islamabad, Sahiwal Campus

License

MIT License
