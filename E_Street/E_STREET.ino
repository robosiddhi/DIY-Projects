/*
Code Name: E_Street
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
                               
Description: E_Street is an automatice street lighting system in which if a vehical passes from the road
the lights of the street were glow automatically and when the vehical passes the lights were turn off it 
uses arduino uno 5 ir sensor and 5 led.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// --- Configuration Constants ---
const int FULL_BRIGHTNESS = 255;  // Full brightness for the LEDs
const int LIGHT_SPREAD = 1;       // How many lights AHEAD of the detected sensor to turn ON (1 = paired light + 1 next light)
const int NUM_PAIRS = 5;

// --- Pin Definitions ---
// Digital Pins for IR sensors (Inputs)
const int IR_PINS[NUM_PAIRS] = {2, 4, 7, 8, 12};   
// PWM Digital Pins for LEDs (Outputs - using PWM pins for flexibility, but analogWrite(255) is essentially HIGH)
const int LED_PINS[NUM_PAIRS] = {3, 5, 6, 9, 10}; 

// --- Function Prototypes ---
void setAllLeds(int brightness);


void setup() {
  // Initialize all Sensor pins as inputs
  for (int i = 0; i < NUM_PAIRS; i++) {
    pinMode(IR_PINS[i], INPUT);
    // Initialize all LED pins as outputs
    pinMode(LED_PINS[i], OUTPUT);
  }
  
  // Start with all lights OFF
  setAllLeds(0);
  Serial.begin(9600); // For optional debugging
}

void loop() {
  
  // 1. Reset all lights to OFF (The "trailing" logic)
  // This is the CRITICAL step that ensures lights turn OFF behind the car.
  setAllLeds(0);
  
  // 2. Check for Vehicle Detection and Activate Lights
  // Iterate through the sensors from the start of the road (index 0)
  for (int i = 0; i < NUM_PAIRS; i++) {
    // Read the current sensor state
    // IR sensor is typically LOW when a car is detected
    if (digitalRead(IR_PINS[i]) == LOW) {
      
      // Car detected: Turn ON the light corresponding to this sensor and subsequent ones
      for (int j = 0; j <= LIGHT_SPREAD; j++) {
        int ledIndex = i + j;
        
        // Ensure the index is within the bounds of the LED array
        if (ledIndex < NUM_PAIRS) {
          // Turn on the light at full brightness
          analogWrite(LED_PINS[ledIndex], FULL_BRIGHTNESS);
        }
      }
      
      // CRITICAL: Break the loop after the first detection.
      // This ensures that the light activation is only controlled by the LEADING sensor.
      break; 
    }
  }
  
  delay(50); // Small loop delay for stable readings
}


// --- Supporting Function ---

/**
 * Sets all road LEDs to a specified brightness level (0 for OFF, 255 for ON).
 */
void setAllLeds(int brightness) {
  for (int i = 0; i < NUM_PAIRS; i++) {
    // Using analogWrite for 0/255 is equivalent to LOW/HIGH but keeps the code flexible
    analogWrite(LED_PINS[i], brightness); 
  }
}