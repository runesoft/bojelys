#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 12

#define NUM_COLORS 3 //number of colors to use
#define FPS 60
#define LOOPTIME 5.0
#define INCREMENT (2*PI)/(FPS*LOOPTIME)
#define DELAY 1000/FPS
#define WINDOW 10.34
#define LPS 10.0
#define INCREASE LPS/FPS

CRGB leds[NUM_LEDS];
CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};


void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, GRB>(leds, NUM_LEDS);
}

float loopp=0;
float current=-WINDOW;
CRGB color=CRGB::Red;

void loop() { 
  for(int i =0;i<NUM_LEDS;i++){
    if(i<=current || i>=current+WINDOW){
      leds[i]=CRGB::Black;
    } else {
      leds[i]=color;
      leds[i].maximizeBrightness((cos(PI+(PI*2)*(i-current) /WINDOW)+1)*127);
    }
  }
  //current+=INCREASE;
  loopp+=INCREMENT;
  current=(cos(loopp)+1)/2*(NUM_LEDS-WINDOW);

  if(loopp>PI){
    loopp-=2*PI;
    //current=-WINDOW;
    color=colors[random(6)];
  }
  FastLED.show();
  delay(DELAY);
}
