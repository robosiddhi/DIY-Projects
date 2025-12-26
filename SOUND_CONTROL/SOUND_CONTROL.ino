/*
Code Name:SOUND_DETECTION
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
                               
Description: This project demonstrates a home automation prototype capable of controlling electrical appliances using sound commands. The system utilizes 
an Arduino Uno microcontroller interface with a high-sensitivity microphone sound sensor module.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// --- CONNECTIONS ---
const int soundSensorPin = 7;  // Sensor D0 pin
const int ledPin = 13;         // LED Positive leg (Long leg)

// --- VARIABLES ---
int sensorStatus = 0;
int ledState = LOW;            // Start with LED OFF
unsigned long lastClapTime = 0; 

// Increase this if the light flickers too much
const int debounceDelay = 500; // 0.5 seconds wait between claps

void setup() {
  pinMode(soundSensorPin, INPUT);
  pinMode(ledPin, OUTPUT);
  
  Serial.begin(9600);
  Serial.println("System Ready. Clap to toggle LED.");
}

void loop() {
  // Read the sensor
  sensorStatus = digitalRead(soundSensorPin);

  // If sound detected (Active LOW for your sensor)
  if (sensorStatus == LOW) {
    
    // Check timer to prevent flickering (Debounce)
    if (millis() - lastClapTime > debounceDelay) {
      
      // Toggle logic: If OFF, turn ON. If ON, turn OFF.
      if (ledState == LOW) {
        ledState = HIGH;
        Serial.println(">>> CLAP DETECTED: Turning LED ON");
      } else {
        ledState = LOW;
        Serial.println(">>> CLAP DETECTED: Turning LED OFF");
      }
      
      // Apply the new state to the physical pin
      digitalWrite(ledPin, ledState);
      
      // Reset timer
      lastClapTime = millis();
    }
  }
}
