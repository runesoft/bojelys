#include <FastLED.h>

#define NUM_LEDS 100
#define DATA_PIN 12

#define NUM_PROGS 15 //number of leds that can be lit at the same time
#define NUM_COLORS 3 //number of colors to use

#define OFF 0
#define UP 1
#define ON 2
#define DOWN 3



#define FADETIME 2000
#define FPS 60
#define DELAY 1000/FPS
#define FADESTEP 255/((FADETIME/1000)*FPS)
#define MIN_PERIOD 2000
#define MAX_PERIOD 15000
#define FLEX_PERIOD MAX_PERIOD-MIN_PERIOD


CRGB leds[NUM_LEDS];
struct Program{
  int delay;
  int led;
  char state;
  int hue;
};
Program programs [NUM_PROGS];

CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};

void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS); 
  Serial.begin(115200); // open the serial port at 9600 bps:
  for(int i =0;i<NUM_PROGS;i++){
    programs[i]={0,NUM_LEDS+1,OFF,0};
  }
}

bool isPartOf(int led){
  for(int i = 0;i<NUM_PROGS;i++){
    if(programs[i].led==led){
      return true;
    }
  }
  return false;  
}
void loop() { 
  
  for(int i =0; i<NUM_PROGS;i++){
    Program current=programs[i];
    current.delay-=DELAY;
    if(current.state==UP){
      if(current.hue>(255-FADESTEP)){
        current.state =ON;
        current.delay = MIN_PERIOD + random(FLEX_PERIOD); // set random delay until it is turned off
      }else{
        current.hue+=FADESTEP;
        //set color?
        leds[current.led].maximizeBrightness(current.hue);
      }  
    } else if(current.state==DOWN){
      if(current.hue<FADESTEP){  
        //leds[progs[i]].maximizeBrightness(0);
        leds[current.led] = CRGB::Black;
        current.led = NUM_LEDS + 1;
        current.state = OFF;
        current.delay = MIN_PERIOD+random(FLEX_PERIOD); // set random delay until it is turned on
      } else {
        current.hue-=FADESTEP;
        leds[current.led].maximizeBrightness(current.hue);

      }
    }
    else if(current.delay<0){
      if(current.state==ON){ //turn of led
        current.state=DOWN;
       }else{
        int nxtled = random(NUM_LEDS); //pick a random next LED
        if(!isPartOf(nxtled)){ // if not already active
          current.state=UP;
          current.led = nxtled; //store led number in program
          leds[current.led]=colors[random(NUM_COLORS)]; //set random color
          current.hue=FADESTEP;
          leds[current.led].maximizeBrightness(FADESTEP);
        }
      } 
    }
    programs[i]=current;
    
  }
  FastLED.show();
  delay(DELAY);
}
