/*
Code Name:SMART_IRRIGATION
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
                               
Description:The Smart Irrigation is an automated monitoring soil moisture levels sollution in real-time, the system ensures that 
plants receive the precise amount of water they need, preventing both over-watering and dehydration. This project promotes water
conservation and allows for "hands-free" plant maintenance.The project uses Arduino Uno , Relay Module  , Water pump & Soil Sensor
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
// --- PIN DEFINITIONS ---
const int soilSensorPin = A0;   // Analog pin connected to the AOUT of the Soil Moisture Sensor
const int relayPin = 8;         // Digital pin connected to the IN pin of the Relay Module

// --- CALIBRATION VALUE ---
// IMPORTANT: You MUST calibrate this value for your specific soil and sensor.
// - A higher value (e.g., 700) means the soil is dry.
// - A lower value (e.g., 300) means the soil is wet.
// Start by monitoring the Serial Monitor to find a value that represents 
// "just dry enough" for your plants.
const int dryThreshold = 700; 

// --- TIMING PARAMETERS ---
// How long the pump runs when the soil is dry (in milliseconds)
const long wateringDuration = 10000; // 10 seconds (adjust as needed)
// How long the system waits after watering before checking the soil again
const long checkDelay = 1800000; // 30 minutes (30 * 60 * 1000 ms)

void setup() {
  // Initialize the relay pin as an output
  pinMode(relayPin, OUTPUT);
  
  // Ensure the pump is OFF when the system starts (ACTIVE-LOW: HIGH = OFF)
  digitalWrite(relayPin, HIGH);
  
  // Initialize serial communication for monitoring/debugging
  Serial.begin(9600);
  Serial.println("Smart Irrigation System Initialized.");
  Serial.print("Dry Threshold Set To: ");
  Serial.println(dryThreshold);
}

void loop() {
  // Read the analog value from the soil moisture sensor
  int moistureValue = analogRead(soilSensorPin);

  // Print the current reading to the Serial Monitor
  Serial.print("Current Soil Moisture Reading (0-1023): ");
  Serial.println(moistureValue);

  // --- CHECK CONDITION ---
  if (moistureValue > dryThreshold) {
    // Soil is dry (reading is higher than the dry threshold)
    
    Serial.println("--- SOIL IS DRY! Starting Watering Cycle... ---");
    
    // 1. Turn the pump ON (ACTIVE-LOW: LOW = ON)
    digitalWrite(relayPin, LOW); 
    Serial.print("Pump ON for ");
    Serial.print(wateringDuration / 1000);
    Serial.println(" seconds.");

    // 2. Wait for the predetermined watering duration
    delay(wateringDuration); 

    // 3. Turn the pump OFF (ACTIVE-LOW: HIGH = OFF)
    digitalWrite(relayPin, HIGH); 
    Serial.println("Watering complete. Pump OFF.");

    // 4. Wait for a longer delay before checking the soil again
    // This prevents the pump from cycling ON/OFF rapidly while water soaks in.
    Serial.print("Waiting for ");
    Serial.print(checkDelay / 60000);
    Serial.println(" minutes before next check.");
    delay(checkDelay);
    
  } else {
    // Soil is wet enough (reading is lower than or equal to the dry threshold)
    
    Serial.println("Soil is wet enough. Pump remains OFF.");
    
    // Wait for 2 minutes before checking the moisture again
    delay(120000); // 120 seconds = 2 minutes
  }

  Serial.println("----------------------------------------");
}
