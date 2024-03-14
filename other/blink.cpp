#include <Arduino.h>
#include <FastLED.h>

#define NUM_LEDS 1
#define BRIGHTNESS 1

CRGB leds[NUM_LEDS];

void setup() { 
    FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL>(leds, NUM_LEDS);
    FastLED.setBrightness(BRIGHTNESS);
    pinMode(NEOPIXEL_POWER, OUTPUT);
    digitalWrite(NEOPIXEL_POWER, HIGH);
}

void loop() { 

  leds[0] = CRGB::Red;
  FastLED.show();
  delay(500);

  leds[0] = CRGB::Black;
  FastLED.show();   
  delay(500);
  
}