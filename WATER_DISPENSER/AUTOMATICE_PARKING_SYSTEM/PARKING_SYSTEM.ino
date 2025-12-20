/*
Code Name:PARKING_SYSTEM
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
                               
Description: This project is an automated vehicle access control system designed for private parking lots, residential gates,
or secure corporate zones. Using Radio Frequency Identification (RFID) technology, the system identifies authorized vehicles 
and manages entry via a motorized barrier arm. It eliminates the need for manual security intervention, ensuring both 
convenience and security.The project uses Arduino uno , RFID and servo.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
#include <SPI.h>
#include <MFRC522.h>
#include <Servo.h>

// Pin Definitions
#define SS_PIN 10
#define RST_PIN 9
#define SERVO_PIN 3
#define BUZZER_PIN 4

MFRC522 rfid(SS_PIN, RST_PIN);
Servo gateServo;

// Replace this with your card's actual UID (found via Serial Monitor)
byte authorizedUID[] = {0xDE, 0xAD, 0xBE, 0xEF}; 

void setup() {
  Serial.begin(9600);
  SPI.begin();           // Init SPI bus
  rfid.PCD_Init();       // Init MFRC522
  gateServo.attach(SERVO_PIN);
  
  gateServo.write(0);    // Start with gate closed
  pinMode(BUZZER_PIN, OUTPUT);
  
  Serial.println("Parking System Ready. Scan your card...");
}

void loop() {
  // Look for new cards
  if (!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial()) {
    return;
  }

  // Check if the scanned UID matches our authorized UID
  if (checkUID(rfid.uid.uidByte, authorizedUID)) {
    Serial.println("Access Granted! Opening gate...");
    openGate();
  } else {
    Serial.println("Access Denied! Invalid card.");
    denyAccess();
  }

  rfid.PICC_HaltA(); // Halt PICC
}

boolean checkUID(byte *scanned, byte *authorized) {
  for (byte i = 0; i < 4; i++) {
    if (scanned[i] != authorized[i]) return false;
  }
  return true;
}

void openGate() {
  digitalWrite(BUZZER_PIN, HIGH);
  delay(100);
  digitalWrite(BUZZER_PIN, LOW);
  
  gateServo.write(90);  // Open gate
  delay(5000);          // Wait 5 seconds for car to pass
  gateServo.write(0);   // Close gate
}

void denyAccess() {
  for(int i=0; i<3; i++) {
    digitalWrite(BUZZER_PIN, HIGH);
    delay(100);
    digitalWrite(BUZZER_PIN, LOW);
    delay(100);
  }
}
