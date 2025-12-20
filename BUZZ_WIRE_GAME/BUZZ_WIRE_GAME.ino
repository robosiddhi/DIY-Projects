/*
Code Name:BUZZ_WIRE_GAME
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
                               
Description: This project is an interactive electronic game designed to test a player's focus and motor skills. The objective is to move a metal 
wand through a zig-zag wire maze without making contact. If the wand touches the maze, the player loses a life. To make it more exciting, if all 
lives are lost, the game assigns a random dare to the player before restarting.The project uses Arduino Uno,buzzer,10k Resistor & 16x2 i2c Display
Great for
learning robotics, DIY projects, and basic STEM applications.
*/
#include <LiquidCrystal_I2C.h>

// --- Pin Definitions ---
const int CONTACT_PIN = 2; // Digital pin for the contact wand/maze
const int BUZZER_PIN = 9;  // Digital pin for the buzzer

// --- Game Variables ---
int lives = 5;
bool isGameOver = false;

// Array of Dares (Customize as desired!)
const char* dares[] = {
  "Sing a song loudly!",
  "Do 10 jumping jacks!",
  "Tell a funny joke!",
  "Act like a tiger!",
  "Give a compliment!",
  "Spin around 5 times!",
  "Pat your head, rub belly!"
};
const int NUM_DARES = sizeof(dares) / sizeof(dares[0]); // Calculates the number of dares

// Initialize the LCD object. Use the working address (e.g., 0x27)
LiquidCrystal_I2C lcd(0x27, 16, 2);

void startGame();
void updateDisplay();
void gameOver();
void handleDareAndRestart();

void setup() {
  Serial.begin(9600);
  
  // Setup Pins
  pinMode(CONTACT_PIN, INPUT);
  pinMode(BUZZER_PIN, OUTPUT);

  // Initialize Random Seed using a floating Analog pin (A0) for true randomness
  randomSeed(analogRead(A0)); 

  // Setup LCD
  lcd.init();
  lcd.backlight();
  
  startGame(); // Start the first game
}

void loop() {
  if (isGameOver) {
    // If game over, execute the dare and restart sequence
    handleDareAndRestart();
    // Use 'return' to immediately stop the loop from proceeding to the contact check
    return;
  }

  // Read the state of the contact pin (HIGH means contact is made)
  int contactState = digitalRead(CONTACT_PIN);

  if (contactState == HIGH) {
    // 1. Debounce: Wait briefly to prevent rapid false hits
    delay(50); 
    
    // Re-check after debounce
    if (digitalRead(CONTACT_PIN) == HIGH) { 
      
      lives--; // Decrement life
      Serial.print("Hit! Lives remaining: ");
      Serial.println(lives);
      
      // 2. Play short buzzer feedback (200ms tone)
      tone(BUZZER_PIN, 1000, 200); 
      
      // 3. Check for Game Over condition
      if (lives <= 0) {
        gameOver();
      } else {
        updateDisplay();
      }
      
      // 4. Wait for the player to remove the wand before allowing the next hit
      while (digitalRead(CONTACT_PIN) == HIGH) {
        delay(10); 
      }
    }
  }
}

// --- Custom Functions ---

/**
 * Resets game state and displays the initial message.
 */
void startGame() {
  lives = 5;
  isGameOver = false;
  lcd.clear();
  lcd.setCursor(2, 0);
  lcd.print("Steady Hand Game");
  lcd.setCursor(4, 1);
  lcd.print("Start!");
  delay(2000); // Show start message for 2 seconds
  updateDisplay();
}

/**
 * Clears the LCD and displays the current life count.
 */
void updateDisplay() {
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Keep Steady!");
  lcd.setCursor(0, 1);
  lcd.print("Lives: ");
  lcd.print(lives);
}

/**
 * Handles the game-ending sequence (display and long buzzer).
 */
void gameOver() {
  isGameOver = true;
  
  // 1. Display Game Over message
  lcd.clear();
  lcd.setCursor(3, 0);
  lcd.print("GAME OVER");
  lcd.setCursor(1, 1);
  lcd.print("5 HITS! Dare Time!");
  
  // 2. Play the long buzzer beep (3 seconds)
  tone(BUZZER_PIN, 440, 3000); 
  delay(3000); // Wait for the tone to finish
}

/**
 * Selects a random dare, displays it, waits, displays restart message, and then restarts the game.
 */
void handleDareAndRestart() {
  // 1. Select and Display Random Dare
  int dareIndex = random(NUM_DARES); // Selects a random index
  const char* currentDare = dares[dareIndex];
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("DARE:");
  
  // Display the dare on the second line (with scrolling logic)
  if (strlen(currentDare) > 16) {
    lcd.setCursor(0, 1);
    lcd.print(currentDare);
    delay(1000); // Pause before scrolling
    // Scroll the text for a better view
    for (int i = 0; i < strlen(currentDare) - 16 + 2; i++) {
        lcd.scrollDisplayLeft();
        delay(300);
    }
    // Ensure the last part of the dare is visible for a moment before the delay
    delay(500); 
  } else {
    // If short, just display it
    lcd.setCursor(0, 1);
    lcd.print(currentDare);
  }
  
  // --- Timing Adjustment 1: Hold Dare for 5 Seconds ---
  // The sum of previous delays (scrolling) and this delay should approximate the total viewing time.
  delay(5000); 
  
  // 2. Display Restart Message
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Dare Complete!");
  lcd.setCursor(0, 1);
  lcd.print("Restarting soon...");
  
  // --- Timing Adjustment 2: Hold Restart Message for 5 Seconds ---
  delay(5000); 
  
  // 3. Restart the Game
  startGame();
}