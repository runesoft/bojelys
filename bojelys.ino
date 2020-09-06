#include <FastLED.h>

#define NUM_LEDS 50
#define DATA_PIN 12

#define NUM_PROGS 6 //number of leds that can be lit at the same time
#define NUM_COLORS 3 //number of colors to use

CRGB leds[NUM_LEDS];
int delays [NUM_PROGS]; //for every program, counter to figure out when to do something next time.
int progs [NUM_PROGS];  //Current led that each program is interacting with 
CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};


void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS);
  for(int i =0; i<NUM_PROGS;i++){ //initiate programs with a delay so they start gradually
      delays[i]= random(30);
  }
  int nums=3;
  //control run to test that all lights work
  for(int i =0; i< NUM_LEDS+(nums*(NUM_COLORS+1)); i++){ //for every LED + the windows lighting up
    for(int color=0; color<=NUM_COLORS; color++){ //for every color+1
      int current = i - (color*nums);// look back from current
      if(current>=0 && current<NUM_LEDS){ //only do stuff if it is an actual LED
        if(color<NUM_COLORS){
          leds[current]= colors[color];
        } else{// turn off LED if not a color
          leds[current]= CRGB::Black;
        } 
      }
    }  
    FastLED.show();
    delay(100);
  }  
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
    if(delays[i]<0){
      int led = progs[i];
      if(led<NUM_LEDS && led>=0){ //turn of led
        leds[progs[i]]=CRGB::Black;
        progs[i]= NUM_LEDS + 1;
        delays[i]= 4+random(15);
      }else{
        int nxtled = random(NUM_LEDS); //pick a random next LED
        if(!isPartOf(nxtled)){ // if not already active
          progs[i] = nxtled; //store led number in program
          leds[progs[i]]=colors[random(NUM_COLORS)]; //set random color
          delays[i]= 4+random(15); // set random delay until it is turned off
        }
      } 
    }  
  }
  FastLED.show();
  delay(500);
}
