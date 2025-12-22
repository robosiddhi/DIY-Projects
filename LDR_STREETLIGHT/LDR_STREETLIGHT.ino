/*
Code Name:LDR_STREETLIGHT
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
                               
Description:This project is an automated lighting system based on the Arduino platform. It utilizes a Light Dependent Resistor 
(LDR) to detect environmental light intensity. The system automatically turns on an LED when the surroundings become dark and 
turns it off when there is sufficient light, simulating the behavior of smart streetlights or garden lamps
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
const int LDR = A0; // Use 'const' for variables that won't change
const int LED = 13;

void setup() {
  pinMode(LED, OUTPUT);
  pinMode(LDR, INPUT); // Good practice, though optional for analog pins
  Serial.begin(9600);
}

void loop() {
  int light = analogRead(LDR);
  Serial.print("Light Level: "); // Label your data
  Serial.println(light);

  // LOGIC:
  // If reading is LOW (Dark), turn LED ON
  if (light < 500) { 
    digitalWrite(LED, HIGH);
  } 
  // If reading is HIGH (Bright), turn LED OFF
  else { 
    digitalWrite(LED, LOW);
  }

  delay(500);
}
