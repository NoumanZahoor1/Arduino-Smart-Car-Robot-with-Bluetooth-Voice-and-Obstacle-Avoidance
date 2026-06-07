/* * Multifunctional Robot Car: Obstacle Avoiding, Bluetooth Control, and Voice Control
 * Author: Nouman Zahoor Jatoi
 */

#include <Servo.h>
#include <AFMotor.h>

// Pin Definitions
#define Echo A0
#define Trig A1
#define SERVO_PIN 10

// Speed and Calibration Configuration
#define MOTOR_SPEED 170
#define SERVO_CENTER 103  // Calibrated center point for the servo

// Global Variables
char bluetoothValue = 'S'; 
int distance = 0;
int distanceLeft = 0;
int distanceRight = 0;

Servo servoLook;
AF_DCMotor motorLeftFront(1);
AF_DCMotor motorLeftRear(2);
AF_DCMotor motorRightRear(3);
AF_DCMotor motorRightFront(4);

void setup() {
  Serial.begin(9600);
  
  pinMode(Trig, OUTPUT);
  pinMode(Echo, INPUT);
  
  servoLook.attach(SERVO_PIN);
  servoLook.write(SERVO_CENTER); // Start looking forward
  
  // Initialize all motor speeds
  motorLeftFront.setSpeed(MOTOR_SPEED);
  motorLeftRear.setSpeed(MOTOR_SPEED);
  motorRightRear.setSpeed(MOTOR_SPEED);
  motorRightFront.setSpeed(MOTOR_SPEED);
}

void loop() {
  // Uncomment the mode you want to execute, or build a switch-case to toggle them dynamically.
  
  // obstacleAvoidanceMode();
  // bluetoothControlMode();
  voiceControlMode();
}

/* ================= HARDWARE CONTROL MODES ================= */

void bluetoothControlMode() {
  if (Serial.available() > 0) {
    bluetoothValue = Serial.read();
    Serial.println(bluetoothValue);
  }
  
  switch (bluetoothValue) {
    case 'F': moveForward();  break;
    case 'B': moveBackward(); break;
    case 'L': turnLeft();     break;
    case 'R': turnRight();    break;
    case 'S': stopRobot();    break;
  }
}

void voiceControlMode() {
  if (Serial.available() > 0) {
    bluetoothValue = Serial.read();
    Serial.println(bluetoothValue);
    
    if (bluetoothValue == '^') {
      moveForward();
    } else if (bluetoothValue == '-') {
      moveBackward();
    } else if (bluetoothValue == '<') {
      distanceLeft = lookLeft();
      servoLook.write(SERVO_CENTER);
      if (distanceLeft >= 10) {
        turnLeft();
        delay(500);
        stopRobot();
      } else {
        stopRobot();
      }
    } else if (bluetoothValue == '>') {
      distanceRight = lookRight();
      servoLook.write(SERVO_CENTER);
      if (distanceRight >= 10) {
        turnRight();
        delay(500);
        stopRobot();
      } else {
        stopRobot();
      }
    } else if (bluetoothValue == '*') {
      stopRobot();
    }
  }
}

void obstacleAvoidanceMode() {
  distance = readUltrasonic();
  
  if (distance <= 12 && distance > 0) { // Added > 0 check to handle sensor errors
    stopRobot();
    moveBackward();
    delay(150);
    stopRobot();
    
    distanceLeft = lookLeft();
    servoLook.write(SERVO_CENTER);
    delay(400);
    
    distanceRight = lookRight();
    servoLook.write(SERVO_CENTER);
    delay(400);
    
    if (distanceLeft < distanceRight) {
      turnRight();
      delay(500);
      stopRobot();
      delay(200);
    } else {
      turnLeft();
      delay(500);
      stopRobot();
      delay(200);
    }
  } else {
    moveForward();
  }
}

/* ================= SENSOR & SERVO UTILITIES ================= */

int readUltrasonic() {
  digitalWrite(Trig, LOW);
  delayMicroseconds(2);
  digitalWrite(Trig, HIGH);
  delayMicroseconds(10);
  digitalWrite(Trig, LOW);
  
  long duration = pulseIn(Echo, HIGH, 30000); // 30ms timeout prevents hanging if no echo
  if (duration == 0) return 400;              // Return max distance if timeout occurs
  
  int cm = duration / 29 / 2; 
  return cm;
}

int lookRight() {
  servoLook.write(20);
  delay(500); // 500ms is generally sufficient for a micro servo to travel 80 degrees
  return readUltrasonic();
}

int lookLeft() {
  servoLook.write(180);
  delay(500); 
  return readUltrasonic();
}

/* ================= MOTOR MOVEMENT UTILITIES ================= */

void moveForward() {
  motorLeftFront.run(FORWARD);
  motorLeftRear.run(FORWARD);
  motorRightRear.run(FORWARD);
  motorRightFront.run(FORWARD);
}

void moveBackward() {
  motorLeftFront.run(BACKWARD);
  motorLeftRear.run(BACKWARD);
  motorRightRear.run(BACKWARD);
  motorRightFront.run(BACKWARD);
}

void turnRight() {
  motorLeftFront.run(BACKWARD);
  motorLeftRear.run(BACKWARD);
  motorRightRear.run(FORWARD);
  motorRightFront.run(FORWARD);
}

void turnLeft() {
  motorLeftFront.run(FORWARD);
  motorLeftRear.run(FORWARD);
  motorRightRear.run(BACKWARD);
  motorRightFront.run(BACKWARD);
}

void stopRobot() {
  motorLeftFront.run(RELEASE);
  motorLeftRear.run(RELEASE);
  motorRightRear.run(RELEASE);
  motorRightFront.run(RELEASE);
}