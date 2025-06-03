Bluetooth-Controlled Two-Wheel Robot
Author: Tristan Zabala
Date: May 2025
Platform: Arduino Uno
Bluetooth Module: HM-10 (BLE)
Motor Driver: L298N Dual H-Bridge
Control App: Dabble (Gamepad Module)

Overview
This project enables Bluetooth control of a two-wheel robot using the Dabble mobile app and an HM-10 BLE module. It lets you drive the robot forward, backward, left, and right, and adjust its speed in real time. An emergency stop is also built in for safety.

Features
🔼 Forward, 🔽 Backward, ◀️ Left, and ▶️ Right motion

🔄 Real-time speed control using Dabble Gamepad buttons:

Triangle: Increase speed

Cross: Decrease speed

Square: Reset speed to default (180)

Circle: Emergency stop (sets speed to 0)

📟 Serial Monitor feedback for debugging

🔧 Uses PWM to vary motor speed

Required Libraries
Dabble Library

SoftwareSerial (included in Arduino IDE)

Install the Dabble library via the Arduino Library Manager or manually from the GitHub link above.

Wiring Diagram
Component	      Arduino Pin
HM-10 TX	      2 (RX via SoftwareSerial)
HM-10 RX	      3 (TX via SoftwareSerial)
HM-10 VCC       5V
HM-10 GND       GND
L298N IN1    	  6
L298N IN2	      7
L298N ENA       (PWM)	10
L298N IN3	      4
L298N IN4	      5
L298N ENB       (PWM)	9

Note: Use a proper power supply for motors; do not power them directly from the Arduino.

How to Use
Upload the code to your Arduino Uno.

Open the Dabble app and navigate to the Gamepad module.

Connect via BLE to the HM-10 module.
  - If you're using the DSD TECH HM-10, the device will appear as "DSD Tech" in the Dabble app’s Bluetooth scan list. Make sure to select it to establish the connection.

Control the robot using the on-screen D-pad and buttons.

Open Serial Monitor (9600 baud) for live feedback on speed and actions.

Customization
Adjust Speed: Modify baseSpeed to change the robot's default speed.

Motor Logic: The setMotorDirection() function can be changed if your wiring requires reversing the polarity for proper motor direction.

Troubleshooting

Motors not turning? 
  - Make sure all motor wiring and the external power supply are properly connected and delivering sufficient voltage.
  - Confirm that the L298N motor driver pins are correctly wired to the Arduino and match the pin numbers defined in the code

No response to Dabble? Ensure correct pins and baud rate in Dabble.begin().

License
This project is open-source under the MIT License.
