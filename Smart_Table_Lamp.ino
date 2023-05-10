// Include the necessary libraries
#include <Wire.h>
#include <Adafruit_NeoPixel.h>

// Define the pin where the NeoPixel LED is connected
#define LED_PIN 6

// Define the number of NeoPixel LEDs
#define LED_COUNT 1

// Define the maximum brightness of the LED
#define MAX_BRIGHTNESS 255

// Define the minimum brightness of the LED
#define MIN_BRIGHTNESS 0

// Define the initial brightness of the LED
#define INITIAL_BRIGHTNESS 128

// Define the variable to store the current brightness of the LED
int brightness = INITIAL_BRIGHTNESS;

// Define the function to set the brightness of the LED
void setBrightness(int newBrightness) {
  // Make sure the new brightness is within the allowed range
  if (newBrightness < MIN_BRIGHTNESS) {
    newBrightness = MIN_BRIGHTNESS;
  }
  else if (newBrightness > MAX_BRIGHTNESS) {
    newBrightness = MAX_BRIGHTNESS;
  }

  // Set the brightness of the LED
  brightness = newBrightness;
}

// Create the NeoPixel object
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Initialize the NeoPixel LED
  strip.begin();
  strip.show(); // Initialize all pixels to 'off'

  // Set the initial brightness of the LED
  setBrightness(INITIAL_BRIGHTNESS);
}

void loop() {
  // Check if there is any data available on the serial port
  if (Serial.available() > 0) {
    // Read the data from the serial port
    char command = Serial.read();

    // Handle the different commands
    if (command == 'o') { // Turn the LED on
      strip.setBrightness(brightness);
      strip.show();
    }
    else if (command == 'f') { // Turn the LED off
      strip.setBrightness(MIN_BRIGHTNESS);
      strip.show();
    }
    else if (command == '+') { // Increase the brightness
      setBrightness(brightness + 10);
      strip.setBrightness(brightness);
      strip.show();
    }
    else if (command == '-') { // Decrease the brightness
      setBrightness(brightness - 10);
      strip.setBrightness(brightness);
      strip.show();
    }
  }
}
