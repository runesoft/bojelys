#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 12

#define NUM_PROGS 6 //number of leds that can be lit at the same time
#define NUM_COLORS 3 //number of colors to use

#define OFF 0
#define UP 1
#define ON 2
#define DOWN 3


CRGB leds[NUM_LEDS];
int delays [NUM_PROGS]; //for every program, counter to figure out when to do something next time.
int progs [NUM_PROGS];  //Current led that each program is interacting with 
int states [NUM_PROGS];
int hues [NUM_PROGS];

CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};


void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);  
}

bool isPartOf(int led){
  for(int i = 0;i<NUM_PROGS;i++){
    if(progs[i]==led){
      return true;
    }
  }
  return false;  
}
void loop() { 
  for(int i =0; i<NUM_PROGS;i++){
    delays[i]= delays[i]-1;
    if(states[i]==UP){
      if(hues[i]>255-10){
        leds[progs[i]].maximizeBrightness(255);;
        states[i]=ON;
        delays[i]= 4+random(15); // set random delay until it is turned off
      }else{
        hues[i]+=10;
        leds[progs[i]].maximizeBrightness(hues[i])
      }  
    } else if(states[i]==DOWN){
      if(hues[i]<10){
        leds[progs[i]].maximizeBrightness(0);
        leds[progs[i]]=CRGB::Black;
        progs[i]= NUM_LEDS + 1;
        states[i]=OFF;
        delays[i]= 4+random(15); // set random delay until it is turned on
      } else {
        hues[i]-=10;
        leds[progs[i]].maximizeBrightness(hues[i])

      }
    }
    else if(delays[i]<0){
      int led = progs[i];
      if(states[i]==ON){ //turn of led
        states[i]=DOWN;
       }else{
        int nxtled = random(NUM_LEDS); //pick a random next LED
        if(!isPartOf(nxtled)){ // if not already active
           states[i]=UP;
       
          progs[i] = nxtled; //store led number in program
          leds[progs[i]]=colors[random(NUM_COLORS)]; //set random color
          leds[progs[i]].maximizeBrightness(hues[i]);
          delays[i]= 4+random(15); // set random delay until it is turned off
        }
      } 
    }  
  }
  FastLED.show();
  delay(500);
}
