#include <Arduino.h>
#include <FastLED.h>

#define LED1 D0
#define LED2 NEOPIXEL_POWER
#define LED3 D7
#define BTN D1
#define NUM_LEDS 1
#define NEOPIXEL_BRIGTHNESS 2

CRGB leds[NUM_LEDS];

bool led1State = HIGH; // HIGH, true and 1 mean the same
bool led2State = HIGH;
bool led3State = HIGH;

bool btnState = HIGH; // button is high as it is connected to 3.3V via a pull-up resistor

int targetLED = 0;

void setup() {

  FastLED.addLeds<NEOPIXEL, PIN_NEOPIXEL>(leds, NUM_LEDS);
  FastLED.setBrightness(NEOPIXEL_BRIGTHNESS);

  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  pinMode(LED3, OUTPUT);
  pinMode(BTN, INPUT);

  // set initial state of LEDs
  digitalWrite(PIN_LED_R, HIGH);
  digitalWrite(PIN_LED_G, HIGH);
  digitalWrite(PIN_LED_B, HIGH);

  digitalWrite(LED1, led1State);
  digitalWrite(LED2, led2State);
  digitalWrite(LED3, led3State);

  leds[0] = CRGB::Orange;
  FastLED.show();
}

void loop() {
  bool btnReading = digitalRead(BTN);

  // we want to do something only if the reading and the state are different
  // in this case they are the same and we exit the loop immediatly
  if(btnReading == btnState){
    return; 
  }
 
  if(btnReading == LOW){ // LOW means button is pressed on Tarantino
    btnState = LOW;
    targetLED++;

    switch(targetLED % 3){
      case 0: 
        led1State = LOW;
        led2State = LOW;
        led3State = HIGH;
        break;
      case 1: 
        led1State = HIGH;
        led2State = LOW;
        led3State = LOW;
        break;
      case 2: 
        led1State = LOW;
        led2State = HIGH;
        led3State = LOW;
        break;
    }
  }else{
    btnState = HIGH;
  }

  digitalWrite(LED1, led1State);
  digitalWrite(LED2, led2State);
  digitalWrite(LED3, led3State);
  delay(10);
  FastLED.show();
}