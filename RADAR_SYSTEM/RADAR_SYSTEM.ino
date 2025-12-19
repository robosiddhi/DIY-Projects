/*
Code Name:RADAR_SYSTEM
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
                               
Description: A real-time mini radar system that maps object distance and angle on a 0.96" OLED display
using an Arduino Uno, HC-SR04 ultrasonic sensor, and a servo motor.
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Servo.h>

// --- Configuration ---
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET    -1 
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

const int trigPin = 9;
const int echoPin = 10;
const int servoPin = 11;

Servo myServo;

// Radar Settings
const int radarRange = 40; // Max detection distance in cm to fit on screen
const int sweepSpeed = 30; // Delay in ms between servo moves (lower is faster)

void setup() {
  Serial.begin(9600);
  
  // Initialize Servo
  myServo.attach(servoPin);
  
  // Initialize Pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);

  // Initialize OLED
  if(!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { 
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);
  }
  
  display.clearDisplay();
  display.setTextSize(1);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(25, 25);
  display.print("RADAR SYSTEM");
  display.display();
  delay(2000);
}

void loop() {
  // Sweep from Left to Right (15 to 165 degrees)
  for(int i = 15; i <= 165; i += 2) {  
    myServo.write(i);
    int dist = calculateDistance();
    drawRadar(i, dist);
    delay(sweepSpeed);
  }
  
  // Sweep from Right to Left (165 to 15 degrees)
  for(int i = 165; i >= 15; i -= 2) {  
    myServo.write(i);
    int dist = calculateDistance();
    drawRadar(i, dist);
    delay(sweepSpeed);
  }
}

// Function to measure distance using Ultrasonic Sensor
int calculateDistance() { 
  digitalWrite(trigPin, LOW); 
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH); 
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  long duration = pulseIn(echoPin, HIGH);
  int distance = duration * 0.034 / 2;
  return distance;
}

// Function to draw the Radar Interface
void drawRadar(int angle, int distance) {
  display.clearDisplay();
  
  // 1. Draw Radar Arcs (Background UI)
  display.drawCircle(64, 64, 20, SSD1306_WHITE); // Inner arc
  display.drawCircle(64, 64, 40, SSD1306_WHITE); // Outer arc
  display.drawCircle(64, 64, 60, SSD1306_WHITE); // Max range arc

  // 2. Calculate coordinates for the sweep line
  // Convert angle to radians for math functions
  // We subtract angle from 180 because the servo mounts usually mirror the screen
  float radian = (angle * PI) / 180; 
  
  // Calculate tip of the sweep line (always at max range)
  int x_line = 64 - (60 * cos(radian));
  int y_line = 64 - (60 * sin(radian));
  
  // Draw the sweep line
  display.drawLine(64, 64, x_line, y_line, SSD1306_WHITE);

  // 3. Draw the Object if detected
  // If distance is within our defined radarRange (e.g., 40cm)
  if (distance > 0 && distance < radarRange) {
    // Map distance to screen pixels (0 to 40cm -> 0 to 60 pixels)
    int distMap = map(distance, 0, radarRange, 0, 60);
    
    // Calculate object coordinates
    int x_obj = 64 - (distMap * cos(radian));
    int y_obj = 64 - (distMap * sin(radian));
    
    // Draw a big dot for the object
    display.fillCircle(x_obj, y_obj, 3, SSD1306_WHITE);
    
    // Optional: Display distance text
    display.setCursor(0, 0);
    display.print("Dist: ");
    display.print(distance);
    display.print(" cm");
  }
  
  display.display();
}
