/*
Code Name:JOYSTIC_SERVO CONTROL
Author: RoboSiddhi

⚠ Warning

This project and its code are shared for learning and personal use only.  
Commercial use, redistribution, or selling (in any form) of this code or
project is not allowed without proper permission.  

                                                                                 .                 
              !^           .   ..   ..            
              ??^~~~^.      ....:....             
             :P5J?7?JY5.   ...^:::^..             
            .BG5JY75&JYG   ...^:::^..             
            .BBBP57?YYYG.   ....::::              
             :YBBGYJ??Y?   .  .^ YGGY.            
              :!BBBBY!:       .G??5BP^            
            ~GP5P5??77!7:    .^J55Y!              
           ^#57!7#5777!?57~:~77JG~                
           ?#G5PB#57777!B5GG5YPJ.                 
          .BGYY&&BPY???J!!Y5Y7:                   
          :7!~!7777!!!!^     
                               
Description: This project demonstrates the fundamental principles of robotics and control systems by interfacing a Servo Motor
with a Joystick module using an Arduino microcontroller. The system is designed to translate the manual movement of the joystick 
into precise angular rotation of the servo motor
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
#include <Servo.h>

Servo myServo;  // Create a servo object

const int joyPin = A0;  // Joystick X-axis connected to Analog 0
const int servoPin = 9; // Servo signal connected to Digital 9

int joyVal;    // Variable to read the value from the analog pin
int angle;     // Variable to hold the angle for the servo

void setup() {
  myServo.attach(servoPin);  // Attaches the servo on pin 9 to the servo object
  Serial.begin(9600);        // Optional: for debugging
}

void loop() {
  // 1. Read the joystick value (between 0 and 1023)
  joyVal = analogRead(joyPin);

  // 2. Map the joystick value to servo angle (between 0 and 180)
  // The joystick goes from 0 to 1023, but the servo only goes 0 to 180.
  angle = map(joyVal, 0, 1023, 0, 180);

  // 3. Move the servo to that angle
  myServo.write(angle);

  // 4. Small delay to make the movement smooth
  delay(15);
}
