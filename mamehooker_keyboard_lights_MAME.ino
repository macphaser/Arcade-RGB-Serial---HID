// RGB Keyboard
// Tested and working on Teensy Arduino
// add Rumble, Lights optional from AK - WiiMod  
// 2 RDB LED - showing Player1 and Player2 mame status
// 10 Pixel Neopixel strip for Serial Colors


#include "Keyboard.h"
#include <Adafruit_NeoPixel.h>

// Neopixel Part
#define PIN            3  // Neopixel data input pin
#define NUMPIXELS      10 // Number of Neopixels
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

// RGB LED pins - Player 1 LED
int redPin1 = 6;
int greenPin1 = 9;
int bluePin1 = 10;

// RGB LED pins - Player 2 LED
int redPin2 = 23;
int greenPin2 = 22;
int bluePin2 = 21;

// LED for normal button inputs - feedback
const int led = 20;

void setup() {
  Serial.begin(9600); // Serial communication
  
  Keyboard.begin();
  strip.begin();    // Start Neopixel Strip
  strip.show();     // Initialize all pixels to 'off'

  // RGB LED setup
  pinMode(redPin1, OUTPUT);
  pinMode(greenPin1, OUTPUT);
  pinMode(bluePin1, OUTPUT);
  analogWrite(redPin1, 255);
  analogWrite(greenPin1, 255);
  analogWrite(bluePin1, 255);

  pinMode(redPin2, OUTPUT);
  pinMode(greenPin2, OUTPUT);
  pinMode(bluePin2, OUTPUT);
  analogWrite(redPin2, 255);
  analogWrite(greenPin2, 255);
  analogWrite(bluePin2, 255);

  // Signal LED for Keyboard
  pinMode(led, OUTPUT);

  // Joystick and button connections
  pinMode(2, INPUT_PULLUP);   // left arrow pin
  pinMode(7, INPUT_PULLUP);   // right arrow pin
  pinMode(16, INPUT_PULLUP);  // ESC Key pin
  pinMode(11, INPUT_PULLUP);  // TAB Key pin
  pinMode(12, INPUT_PULLUP);  // ENTER Key pin
  pinMode(8, INPUT_PULLUP);   // down arrow pin
  pinMode(17, INPUT_PULLUP);  // up arrow pin
}

void loop() {
  // Serial command handling for RGB LEDs
  if (Serial.available() > 0) {
    String command = Serial.readStringUntil('\n');

// Commands for Neopixel
    if (command.startsWith("RED")) {
      knightRider(255, 0, 0); // Red
    } else if (command.startsWith("GREEN")) {
      knightRider(0, 255, 0); // Green
    } else if (command.startsWith("BLUE")) {
      knightRider(0, 0, 255); // Blue
    } else if (command.startsWith("ALLRED")) {
      flashAll(255, 0, 0); // All pixels flashing red
    } else if (command.startsWith("ALLGREEN")) {
      flashAll(0, 255, 0); // All pixels flashing green
    } else if (command.startsWith("ALLBLUE")) {
      flashAll(0, 0, 255); // All pixels flashing blue
    } else if (command.startsWith("ALTFLASH")) {
      flashAlternate(); // All pixels flashing alternating red and blue
    } else if (command.startsWith("LEFT")) {
      lightUp(255, 0, 0); // Left to right one after the other red
    } else if (command.startsWith("RIGHT")) {
      lightUp(0, 0, 255); // Left to right one after the other blue
    } else if (command.startsWith("RAINBOW")) {
      rainbow(); // Rainbow animation
    }

    
    // Commands for First RGB LED
    if (command.startsWith("1RED")) {
      setColor(redPin1, 100, 0, 0); // Set RGB values for red
    } else if (command.startsWith("1GREEN")) {
      setColor(redPin1, 0, 100, 0); // Set RGB values for green
    } else if (command.startsWith("1BLUE")) {
      setColor(redPin1, 0, 0, 255); // Set RGB values for blue
    } else if (command.startsWith("1OFF")) {
      setColor(redPin1, 0, 0, 0); // Turn off the LED
    
    // Commands for Second RGB LED
    } else if (command.startsWith("2RED")) {
      setColor(redPin2, 100, 0, 0); // Set RGB values for red
    } else if (command.startsWith("2GREEN")) {
      setColor(redPin2, 0, 100, 0); // Set RGB values for green
    } else if (command.startsWith("2BLUE")) {
      setColor(redPin2, 0, 0, 255); // Set RGB values for blue
    } else if (command.startsWith("2OFF")) {
      setColor(redPin2, 0, 0, 0); // Turn off the LED
    }
  }

  // Check the switches for Keyboard inputs
  int buttonState2 = digitalRead(2);    // left arrow pin
  int buttonState3 = digitalRead(7);    // right arrow pin
  int buttonState4 = digitalRead(16);   // ESC key pin
  int buttonState5 = digitalRead(11);   // TAB key pin
  int buttonState6 = digitalRead(12);   // ENTER key pin
  int buttonState7 = digitalRead(8);    // down arrow pin
  int buttonState8 = digitalRead(17);   // up arrow pin

  // Joystick Left = Arrow Left Key
  if (buttonState2 == LOW) {
    Keyboard.press(KEY_LEFT_ARROW);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Keyboard.release(KEY_LEFT_ARROW);
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  }

  // Joystick Right = Arrow Right Key
  if (buttonState3 == LOW) {
    Keyboard.press(KEY_RIGHT_ARROW);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Keyboard.release(KEY_RIGHT_ARROW);
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  }

  // Fire Button = ESC Key
  if (buttonState4 == LOW) {
    Keyboard.press(KEY_ESC);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Keyboard.release(KEY_ESC);
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  }

  // TAB - Key
  if (buttonState5 == LOW) {
    Keyboard.press(KEY_TAB);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Keyboard.release(KEY_TAB);
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)

  }

  // Return - Key
  if (buttonState6 == LOW) {
    Keyboard.press(KEY_RETURN);
    digitalWrite(led, HIGH);   // turn the LED on (HIGH is the voltage level)
  } else {
    Keyboard.release(KEY_RETURN);
    digitalWrite(led, LOW);   // turn the LED on (HIGH is the voltage level)
  }

// down arrow key
if (buttonState7 == LOW) {
  Keyboard.press(KEY_DOWN_ARROW);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_DOWN_ARROW);
  digitalWrite(led, LOW);
}

// up arrow key
if (buttonState8 == LOW) {
  Keyboard.press(KEY_UP_ARROW);
  digitalWrite(led, HIGH); // Set LED to HIGH only when button is pressed
} else {
  Keyboard.release(KEY_UP_ARROW);
  digitalWrite(led, LOW);
}

}

/*
//RGB LED Colors

void setColor(int redPin, int red, int green, int blue) {
  analogWrite(redPin, 255 - red);
  
  if (redPin == redPin1) {
    analogWrite(greenPin1, 255 - green);
    analogWrite(bluePin1, 255 - blue);
  } else if (redPin == redPin2) {
    analogWrite(greenPin2, 255 - green);
    analogWrite(bluePin2, 255 - blue);
  }
}

*/

// RGB LED Colors - new
void setColor(int redPin, int red, int green, int blue) {
  analogWrite(redPin, 255 - red);
  
  if (redPin == redPin1) {
    analogWrite(greenPin1, 255 - green);
    analogWrite(bluePin1, 255 - blue);
    delay(200);  // Delay to keep the LED on for 500 milliseconds - 100
    analogWrite(greenPin1, 255);  // Turn off green LED
    analogWrite(bluePin1, 255);   // Turn off blue LED
    analogWrite(redPin1, 255);    // Turn off red LED
  } else if (redPin == redPin2) {
    analogWrite(greenPin2, 255 - green);
    analogWrite(bluePin2, 255 - blue);
    delay(200);  // Delay to keep the LED on for 500 milliseconds - 100
    analogWrite(greenPin2, 255);  // Turn off green LED
    analogWrite(bluePin2, 255);   // Turn off blue LED
    analogWrite(redPin2, 255);    // Turn off red LED
  }
}



//Neopixel Colors and Animations

// Knight Rider - runs 5 times
void knightRider(uint8_t r, uint8_t g, uint8_t b) {
  for (int j = 0; j < 1; j++) { // Run 3 times Animation -- 1
    for (int i = 0; i < NUMPIXELS - 2; i++) {
      strip.setPixelColor(i, r, g, b);      // Turn on the first LED
      strip.setPixelColor(i + 1, r, g, b);  // Turn on the second LED
      strip.setPixelColor(i + 2, r, g, b);  // Turn on the third LED
      strip.show();
      delay(30);    //test was 50
      
      strip.setPixelColor(i, 0, 0, 0);      // Turn off the first LED
      strip.setPixelColor(i + 1, 0, 0, 0);  // Turn off the second LED
      strip.setPixelColor(i + 2, 0, 0, 0);  // Turn off the third LED
    }
    
    for (int i = NUMPIXELS - 3; i >= 0; i--) {
      strip.setPixelColor(i, r, g, b);      // Turn on the first LED
      strip.setPixelColor(i + 1, r, g, b);  // Turn on the second LED
      strip.setPixelColor(i + 2, r, g, b);  // Turn on the third LED
      strip.show();
      delay(30);
      
      strip.setPixelColor(i, 0, 0, 0);      // Turn off the first LED
      strip.setPixelColor(i + 1, 0, 0, 0);  // Turn off the second LED
      strip.setPixelColor(i + 2, 0, 0, 0);  // Turn off the third LED
    }
  }
  // Clear the strip
    strip.clear();
    strip.show();
}

// flash all Pixels same Color 3 Times
void flashAll(uint8_t r, uint8_t g, uint8_t b) {
  for (int j = 0; j < 1; j++) { // Run animation 3 times -1
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, r, g, b);
    }
    strip.show();
    delay(50);   //was 500
    strip.clear();
    strip.show();
    delay(50); //was 500
  }
}

// Flash Red / Blue - 5 times

void flashAlternate() {
  for (int j = 0; j < 1; j++) { // Run 5 times -1
    // Set all pixels to red
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 255, 0, 0); // Red
    }
    strip.show();
    delay(100);  // Adjusted delay was 700
    
    // Clear the strip
    strip.clear();
    strip.show();
    
    // Set all pixels to blue
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, 0, 0, 255); // Blue
    }
    strip.show();
    delay(100);  // Adjusted delay, was 1000
    
    // Clear the strip
    strip.clear();
    strip.show();
  }
}




// light up all pixels one after the other
void lightUp(uint8_t r, uint8_t g, uint8_t b) {
  for (int j = 0; j < 1; j++) { // Run animation 3 times - 1
    for (int i = 0; i < NUMPIXELS; i++) {
      strip.setPixelColor(i, r, g, b);
      strip.show();
      delay(50);    //100
    }
    strip.clear();
    strip.show();
  }
}

// Rainbow Animation
void rainbow() {
  for (int k = 0; k < 1; k++) { // Run animation 6 times --1
    for (int i = 0; i < 256; i++) {
      for (int j = 0; j < NUMPIXELS; j++) {
        strip.setPixelColor(j, Wheel((i + j) & 255));
      }
      strip.show();
      delay(20);
    }
    
    // Turn off all pixels after each rainbow cycle
    strip.clear();
    strip.show();
  }
}


uint32_t Wheel(byte WheelPos) {
  WheelPos = 255 - WheelPos;
  if (WheelPos < 85) {
    return strip.Color(255 - WheelPos * 3, 0, WheelPos * 3);
  }
  if (WheelPos < 170) {
    WheelPos -= 85;
    return strip.Color(0, WheelPos * 3, 255 - WheelPos * 3);
  }
  WheelPos -= 170;
  return strip.Color(WheelPos * 3, 255 - WheelPos * 3, 0);
}

   