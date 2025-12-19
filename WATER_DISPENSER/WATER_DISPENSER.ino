/*
Code Name:WATER_DISPENSER
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
                               
Description: This project involves the design and implementation of an automatic, non-contact water dispensing system. 
The goal is to create a hygienic solution where water is pumped automatically when a user places their hand or a glass 
near the nozzle, eliminating the need to physically touch a switch or tap.It use arduino uno,ultrasonic sensor,5v pump
motor driver.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// Define Pins
const int trigPin = 9;
const int echoPin = 10;
const int motorPin1 = 3; 
const int motorPin2 = 4; 

// Variables
long duration;
int distance;

// CHANGED: Set to 5 cm to safely detect objects at 2 cm
const int activationDistance = 5; 

void setup() {
  Serial.begin(9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(motorPin1, OUTPUT);
  pinMode(motorPin2, OUTPUT);

  // Ensure pump is off at startup
  digitalWrite(motorPin1, LOW);
  digitalWrite(motorPin2, LOW);
}

void loop() {
  // 1. Clear the trigPin
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  // 2. Send the sound wave
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);

  // 3. Read the echoPin
  duration = pulseIn(echoPin, HIGH);

  // 4. Calculate distance
  distance = duration * 0.034 / 2;

  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // 5. Logic: Turn ON if object is very close (0 to 5 cm)
  // We use > 1 because 0 often means "sensor error" or "out of range"
  if (distance > 1 && distance <= activationDistance) {
    digitalWrite(motorPin1, HIGH);
    digitalWrite(motorPin2, LOW);
  } 
  else {
    digitalWrite(motorPin1, LOW);
    digitalWrite(motorPin2, LOW);
  }

  delay(100); 
}
