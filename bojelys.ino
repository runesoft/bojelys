#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 12

#define NUM_PROGS 6 //number of leds that can be lit at the same time
#define NUM_COLORS 3 //number of colors to use

CRGB leds[NUM_LEDS];
CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};


void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
}

void loop() {
  for(int i = 0; i<NUM_LEDS;i++){
    leds[i]=CRGB::Black;
  } 
  for(int i=0;i<3;i++){
    leds[random(NUM_LEDS)]=CRGB::White;
  }
  FastLED.show();
  delay(50);
}
