#include <Arduino.h>
#include <FastLED.h>

// Decoy LED pin
#define D_LED D0

// Win LED pin
#define W_LED D7

// Neopixel feedback LED configuration
#define FEEDBACK_LED PIN_NEOPIXEL
#define NEOPIXEL_BRIGHTNESS 2
#define NUM_LEDS 1
CRGB leds[NUM_LEDS];

// Button pin
#define BTN D1

// Maximum button press delay value in ms
#define MAX_DELAY 600
// Lower bound for random delay in ms
#define RANDOM_DELAY_LOW 500
// Upper bound for random delay in ms
#define RANDOM_DELAY_HIGH 5000

// Number of successes required to win
#define WIN_COUNT 5

// Number of failure required to lose
#define LOSS_COUNT 5

// LED states
bool w_LED_state = LOW;
bool d_LED_state = LOW;

// Button state (connected to 3.3V via a pull-up resistor)
bool btnState = HIGH;

// Game variables
unsigned long time_taken;
unsigned long best_time = ULONG_MAX;
int victory_count = 0;
int failure_count = 0;

// Function to measure time until button press
// Waits for delay_time milliseconds and returns the time taken to press 
// the button or the delay time given as an input, whichever is smaller
unsigned long timeUntilButtonPress(int delay_time) {
  unsigned long startTime = millis();
  while (digitalRead(BTN) == HIGH) {
    if (millis() - startTime > delay_time) {break;}
  }
  unsigned long endTime = millis();
  return endTime - startTime;
}

void setup() {

  // Initialize serial communication at 115200 baud
  Serial.begin(115200);

  // Neopixel setup
  FastLED.addLeds<NEOPIXEL, FEEDBACK_LED>(leds, NUM_LEDS);
  FastLED.setBrightness(NEOPIXEL_BRIGHTNESS);
  pinMode(NEOPIXEL_POWER, OUTPUT);
  digitalWrite(NEOPIXEL_POWER, HIGH);
  delay(10);

  // Map pins
  pinMode(W_LED, OUTPUT);
  pinMode(D_LED, OUTPUT);
  pinMode(PIN_LED_R, OUTPUT);
  pinMode(PIN_LED_G, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);
  pinMode(BTN, INPUT);

  // Set initial LED states
  digitalWrite(PIN_LED_R, HIGH);
  digitalWrite(PIN_LED_G, HIGH);
  digitalWrite(PIN_LED_B, HIGH);

  digitalWrite(W_LED, w_LED_state);
  digitalWrite(D_LED, d_LED_state);

  // Visual countdown for player to get ready
  leds[0] = CRGB::Red;
  FastLED.show();
  delay(1000);

  leds[0] = CRGB::Yellow;
  FastLED.show();
  delay(1000);

  leds[0] = CRGB::Green;
  FastLED.show();
  delay(1000);

  leds[0] = CRGB::Black;
  FastLED.show();
}

void loop() {

  // Random delay before one of the LEDs turns on
  int random_delay = random(RANDOM_DELAY_LOW, RANDOM_DELAY_HIGH);
  time_taken = timeUntilButtonPress(random_delay);
  // If the button is pressed before the target LED lights up, the
  // feedback LED flashes red and the player gets a failure point
  if (time_taken < random_delay) {
    Serial.println("Too early!");
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(MAX_DELAY);
    leds[0] = CRGB::Black;
    FastLED.show();
    failure_count++;
  }

  // Randomly selects one of the LEDs to turn on after the random delay time
  switch (random(0, 2))
  {
  case 0:
    // Turn on the decoy LED and wait if a button press is detected while it is on
    d_LED_state = HIGH;
    digitalWrite(D_LED, d_LED_state);
    time_taken = timeUntilButtonPress(MAX_DELAY);
    d_LED_state = LOW;
    digitalWrite(D_LED, d_LED_state);
    // If the button is pressed while the decoy LED is on, the feedback 
    // LED flashes red and the player gets a failure point
    if (time_taken < MAX_DELAY) {
      Serial.println("Wrong LED!");
      leds[0] = CRGB::Red;
      FastLED.show();
      delay(MAX_DELAY);
      leds[0] = CRGB::Black;
      FastLED.show();
      failure_count++;
    }
    break;
  case 1:
    // Turn on the target LED and wait if a button press is detected while it is on
    w_LED_state = HIGH;
    digitalWrite(W_LED, w_LED_state);
    time_taken = timeUntilButtonPress(MAX_DELAY);
    w_LED_state = LOW;
    digitalWrite(W_LED, w_LED_state);
    // If the button is pressed while the target LED is on and faster than the previous time, 
    // the feedback LED flashes green and the player gets a victory point
    if (time_taken < best_time && time_taken < MAX_DELAY) {
      // Prints the new best time taken to press the button and the previous best time if it exists
      Serial.print("New best time_taken: " + String(time_taken) + "ms"); if (best_time != ULONG_MAX) {Serial.print(" (previous best: " + String(best_time) + "ms)");} Serial.println();
      best_time = time_taken;
      leds[0] = CRGB::Green;
      FastLED.show();
      delay(MAX_DELAY);
      leds[0] = CRGB::Black;
      FastLED.show();
      victory_count++;
      // If the button is pressed while the target LED is on but slower than the previous time,
      // the feedback LED flashes yellow and the player gets a message to keep trying
    } else {
      // Prints the keep on trying message and the current best time if it exists
      Serial.print("keep on trying!"); if (best_time != ULONG_MAX) {Serial.print(" (Current best time: " + String(best_time) + "ms)");} Serial.println();
      leds[0] = CRGB::Yellow;
      FastLED.show();
      delay(MAX_DELAY);
      leds[0] = CRGB::Black;
      FastLED.show();
    }
  }  

  // If the player has WIN_COUNT victory points, they win the game, indicated 
  // by the final scoreboard and green LEDs that stay on
  if (victory_count >= WIN_COUNT) {
    Serial.println("You win with a score of " + String(victory_count) + " victories and " + String(failure_count) + " failures!");
    digitalWrite(PIN_LED_G, LOW);
    leds[0] = CRGB::Green;
    FastLED.show();
    delay(ULONG_MAX);
  }

  // If the player has LOSS_COUNT failure points, they lose the game, indicated
  // by the final scoreboard and red LEDs that stay on
  if (failure_count >= LOSS_COUNT) {
    Serial.println("You lose with a score of " + String(victory_count) + " victories and " + String(failure_count) + " failures!");
    digitalWrite(PIN_LED_R, LOW);
    leds[0] = CRGB::Red;
    FastLED.show();
    delay(ULONG_MAX);
  }

  delay(10);
}