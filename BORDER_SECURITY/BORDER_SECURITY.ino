/*
Code Name:BORDER_SECURITY
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
                               
Description: This project is a multi-zone security system designed to detect movement or intrusion across two separate points.
It utilizes two independent laser beams and Light Dependent Resistors (LDRs) to create invisible "tripwires." When an object 
breaks the connection between a laser and its corresponding sensor, the system identifies which zone has been breached and 
activates a localized audio alarm.The project uses 2_laser module,2_ldr sensor,2_buzzer & Arduino Uno.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// --- Pin Definitions ---
const int laserPin1 = 2; // Digital pin for Laser 1
const int ldrPin1 = A0;  // Analog pin for LDR 1
const int buzzerPin1 = 4; // Digital pin for Buzzer 1

const int laserPin2 = 3; // Digital pin for Laser 2
const int ldrPin2 = A1;  // Analog pin for LDR 2
const int buzzerPin2 = 5; // Digital pin for Buzzer 2

// --- Settings ---
// Threshold for the LDR.
// This value is highly dependent on your ambient light, laser strength,
// and LDR module. You will likely need to adjust this value.
// A HIGHER value means LESS light is required to trigger the alarm (more sensitive).
// For LDRs, light causes resistance to DECREASE, leading to a LOWER analog value.
// If your reading is HIGH when light is present, reverse the logic (e.g., trigger if reading > threshold).
const int BREAK_THRESHOLD = 500; 

// --- Setup Function ---
void setup() {
  // Set the laser and buzzer pins as outputs
  pinMode(laserPin1, OUTPUT);
  pinMode(buzzerPin1, OUTPUT);
  pinMode(laserPin2, OUTPUT);
  pinMode(buzzerPin2, OUTPUT);

  // Initialize Serial Communication for debugging
  Serial.begin(9600);
  Serial.println("Laser Alarm System Initialized.");

  // 1. Turn on both lasers
  digitalWrite(laserPin1, HIGH);
  digitalWrite(laserPin2, HIGH);

  // 2. Perform a brief calibration (Wait for LDRs to get initial laser light)
  delay(1000); 
  
  // OPTIONAL: Print initial values to help set the threshold
  int initialLDR1 = analogRead(ldrPin1);
  int initialLDR2 = analogRead(ldrPin2);
  Serial.print("Initial LDR 1 Reading (With Laser): ");
  Serial.println(initialLDR1);
  Serial.print("Initial LDR 2 Reading (With Laser): ");
  Serial.println(initialLDR2);
  Serial.print("Alarm set to trigger if reading is BELOW: ");
  Serial.println(BREAK_THRESHOLD);
  
  // Wait a moment before starting the loop
  delay(2000); 
}

// --- Main Loop Function ---
void loop() {
  // --- Side 1 Check ---
  int ldrValue1 = analogRead(ldrPin1);
  
  // Print current reading for debugging
  Serial.print("LDR 1: ");
  Serial.print(ldrValue1);

  // Check if the light intensity has dropped (beam broken)
  if (ldrValue1 < BREAK_THRESHOLD) {
    // Beam is broken - Activate Alarm 1
    digitalWrite(buzzerPin1, HIGH); // Turn the buzzer ON
    Serial.println("  *** ALARM 1 TRIGGERED! ***");
  } else {
    // Beam is intact - Keep the alarm OFF
    digitalWrite(buzzerPin1, LOW); // Turn the buzzer OFF
    Serial.println(" - OK");
  }

  // --- Side 2 Check ---
  int ldrValue2 = analogRead(ldrPin2);

  // Print current reading for debugging
  Serial.print("LDR 2: ");
  Serial.print(ldrValue2);

  // Check if the light intensity has dropped (beam broken)
  if (ldrValue2 < BREAK_THRESHOLD) {
    // Beam is broken - Activate Alarm 2
    digitalWrite(buzzerPin2, HIGH); // Turn the buzzer ON
    Serial.println("  *** ALARM 2 TRIGGERED! ***");
  } else {
    // Beam is intact - Keep the alarm OFF
    digitalWrite(buzzerPin2, LOW); // Turn the buzzer OFF
    Serial.println(" - OK");
  }

  // Small delay to stabilize readings and avoid constantly spamming the Serial Monitor
  delay(100); 
}
