/*
Code Name:POTENTIO METER SPEED CONTROL
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
                               
Description: his project demonstrates how to control the rotational speed of a DC motor using an Arduino Uno, an L293D motor driver module,
 and a 100kΩ potentiometer. Unlike standard configurations that use an "Enable" pin for speed control
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// --- PIN DEFINITIONS ---
// We must use PWM pins for the inputs now because there is no Enable pin
const int in1 = 5;    // Connect to IN1 on module (Must be PWM pin ~)
const int in2 = 6;    // Connect to IN2 on module (Must be PWM pin ~)
const int potPin = A0; // Potentiometer Middle Pin

// Variables
int potValue = 0;
int motorSpeed = 0;

void setup() {
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
}

void loop() {
  // 1. Read Potentiometer
  potValue = analogRead(potPin);

  // 2. Map to Speed (0-255)
  motorSpeed = map(potValue, 0, 1023, 0, 255);

  // 3. Control Speed via Input Pins
  // To move FORWARD: Apply PWM to IN1, keep IN2 LOW
  analogWrite(in1, motorSpeed); 
  digitalWrite(in2, LOW);

  // NOTE: To move BACKWARD, you would do:
  // digitalWrite(in1, LOW);
  // analogWrite(in2, motorSpeed);
  
  delay(10);
}
