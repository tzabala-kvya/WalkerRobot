/*
  Project: Bluetooth-Controlled Two-Wheel Robot
  Author: Tristan Zabala
  Date: May 2025
  Board: Arduino Uno
  Bluetooth Module: HM-10 (BLE)
  Motor Driver: L298N Dual H-Bridge
  Control App: Dabble (Gamepad Module)

  Description:
  This project enables wireless control of a two-wheel robot using the Dabble mobile app via Bluetooth Low Energy (BLE).
  The robot's movement and speed are managed through the Gamepad module in Dabble, allowing for real-time adjustments.
  The L298N motor driver facilitates direction and speed control of the DC motors through PWM signals.

  Features:
  - Forward, backward, left, and right movement control
  - Adjustable speed using Gamepad buttons
  - Emergency stop functionality
  - Real-time feedback via Serial Monitor

  Libraries Required:
  - Dabble: https://github.com/TinkerHub/Dabble
  - SoftwareSerial (built-in with Arduino IDE)

  Wiring Overview:
  - HM-10 TX → Arduino Pin 2 (SoftwareSerial RX)
  - HM-10 RX → Arduino Pin 3 (SoftwareSerial TX)
  - L298N IN1 → Arduino Pin 10
  - L298N IN2 → Arduino Pin 7
  - L298N ENA → Arduino Pin 9 (PWM)
  - L298N IN3 → Arduino Pin 4
  - L298N IN4 → Arduino Pin 5
  - L298N ENB → Arduino Pin 9 (PWM)

  Notes:
  - Ensure the HM-10 module is properly configured for BLE communication.
  - Verify motor connections and power supply are adequate for the motors used.
  - Adjust 'baseSpeed' variable as needed to suit your specific motor characteristics.
*/

#include <Dabble.h>
#include <SoftwareSerial.h>


// Motor A (left)
#define IN1 6
#define IN2 7
#define ENA 10  // PWM

// Motor B (right)
#define IN3 4
#define IN4 5
#define ENB 9 // PWM

int baseSpeed = 180;  // Adjustable motor speed
bool prevTriangle = false;
bool prevCross = false;
bool prevSquare = false;
bool prevCircle = false;


void setup() {
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(ENA, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(ENB, OUTPUT);

  // Connect HM-10 RXD to Pin 3
  // Conenct HM-10 TXD to Pin 2
  Dabble.begin(9600, 2, 3);  // Dabble on HM-10
  Serial.begin(9600);
  Serial.println("Dabble Gamepad Control with Speed Adjustment");
}

void loop() {
  Dabble.processInput();

  bool triangle = GamePad.isTrianglePressed();
  bool cross = GamePad.isCrossPressed();
  bool square = GamePad.isSquarePressed();
  bool circle = GamePad.isCirclePressed();

  // Triangle: Increase speed
  if (triangle && !prevTriangle) {
    baseSpeed += 10;
    if (baseSpeed > 255) baseSpeed = 255;
    Serial.print("Speed increased to ");
    Serial.println(baseSpeed);
  }

  // Cross: Decrease speed
  if (cross && !prevCross) {
    baseSpeed -= 10;
    if (baseSpeed < 0) baseSpeed = 0;
    Serial.print("Speed decreased to ");
    Serial.println(baseSpeed);
  }

  // Square: Reset speed
  if (square && !prevSquare) {
    baseSpeed = 180;
    Serial.println("Speed reset to 180");
  }

  // Circle: Emergency stop
  if (circle && !prevCircle) {
    baseSpeed = 0;
    Serial.println("Emergency stop");
  }

  // Update previous states
  prevTriangle = triangle;
  prevCross = cross;
  prevSquare = square;
  prevCircle = circle;


  int leftSpeed = 0;
  int rightSpeed = 0;

  if (GamePad.isUpPressed()) {
    Serial.println("Forward");
    setMotorDirection(true, true);
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed;
  } else if (GamePad.isDownPressed()) {
    Serial.println("Backward");
    setMotorDirection(false, false);
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed;
  } else if (GamePad.isLeftPressed()) {
    Serial.println("Turn Left");
    setMotorDirection(true, false);
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed;
  } else if (GamePad.isRightPressed()) {
    Serial.println("Turn Right");
    setMotorDirection(false, true);
    leftSpeed = baseSpeed;
    rightSpeed = baseSpeed;
  } else {
    setMotorDirection(false, false);
    leftSpeed = 0;
    rightSpeed = 0;
  }

  analogWrite(ENA, leftSpeed);
  analogWrite(ENB, rightSpeed);
//  Serial.print("Left PWM: ");
//  Serial.println(leftSpeed);
//  Serial.print("Right PWM: ");
//  Serial.println(rightSpeed);

}

void setMotorDirection(bool leftForward, bool rightForward) {
  digitalWrite(IN1, leftForward ? HIGH : LOW);
  digitalWrite(IN2, leftForward ? LOW : HIGH);
  digitalWrite(IN3, rightForward ? HIGH : LOW);
  digitalWrite(IN4, rightForward ? LOW : HIGH);
}
