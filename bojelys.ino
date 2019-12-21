#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 12

#define NUM_PROGS 6
#define NUM_COLORS 3

CRGB leds[NUM_LEDS];
int delays [NUM_PROGS];
int progs [NUM_PROGS];
CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};


void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  for(int i =0; i<NUM_PROGS;i++){
      delays[i]= random(30);
  
  }
}

bool isPartOf(int led){
  for(int i = 0;i<NUM_PROGS;i++){
    if(progs[i]==led){
      return false;
    }
  }
  return true;  
}
void loop() { 
  for(int i =0; i<NUM_PROGS;i++){
    delays[i]= delays[i]-1;
    if(delays[i]<0){
      int led = progs[i];
      if(led<NUM_LEDS && led>=0){
        //turn of led
        leds[progs[i]]=CRGB::Black;
        progs[i]= NUM_LEDS + 1;
        delays[i]= 4+random(15);
      }else{
        int nxtled = random(NUM_LEDS);
        if(!isPartOf(nxtled)){
          progs[i] = nxtled; 
          leds[progs[i]]=colors[random(NUM_COLORS)];
          delays[i]= 4+random(15);
        }
      }
      
        
    }  
    
  }
  FastLED.show();
  delay(500);
}
