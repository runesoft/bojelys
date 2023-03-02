#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 12

#define NUM_COLORS 3 //number of colors to use
#define FPS 60
#define DELAY 1000/FPS
#define WINDOW 10.34
#define LPS 10.0
#define INCREASE LPS/FPS

CRGB leds[NUM_LEDS];
CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};


void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}

float current=-WINDOW;
CRGB color=CRGB::Red;

void loop() { 
  for(int i =0;i<NUM_LEDS;i++){
    if(i<=current || i>=current+WINDOW){
      leds[i]=CRGB::Black;
    } else {
      leds[i]=color;
      leds[i].maximizeBrightness((cos(3.14+(3.14*2)*(i-current) /WINDOW)+1)*127);
    }
  }
  current+=INCREASE;
  if(current>NUM_LEDS){
    current=-WINDOW;
    color=colors[random(6)];
  }
  FastLED.show();
  delay(DELAY);
}
