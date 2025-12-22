/*
Code Name:TRAFFIC_LIGHT
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
                               
Description: This project utilizes an Arduino microcontroller to simulate a standard traffic signal system. The circuit consists of three LEDs 
(Red, Yellow, and Green) connected to the Arduino's digital output pins via current-limiting resistors. The system operates on a programmed loop 
that mimics real-world traffic logic
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// Define the pins for the LEDs
const int redPin = 10;
const int yellowPin = 9;
const int greenPin = 8;

void setup() {
  // Configure the LED pins as Outputs
  pinMode(redPin, OUTPUT);
  pinMode(yellowPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
}

void loop() {
  // 1. Green Light ON (Go)
  digitalWrite(greenPin, HIGH);  // Turn Green ON
  digitalWrite(redPin, LOW);     // Ensure Red is OFF
  digitalWrite(yellowPin, LOW);  // Ensure Yellow is OFF
  delay(5000);                   // Wait for 5 seconds

  // 2. Yellow Light ON (Slow Down)
  digitalWrite(greenPin, LOW);   // Turn Green OFF
  digitalWrite(yellowPin, HIGH); // Turn Yellow ON
  delay(2000);                   // Wait for 2 seconds

  // 3. Red Light ON (Stop)
  digitalWrite(yellowPin, LOW);  // Turn Yellow OFF
  digitalWrite(redPin, HIGH);    // Turn Red ON
  delay(5000);                   // Wait for 5 seconds
}
