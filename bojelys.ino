#include <FastLED.h>

#define NUM_LEDS 50
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
int delays [NUM_PROGS]; //for every program, counter to figure out when to do something next time.
int progs [NUM_PROGS];  //Current led that each program is interacting with 
char states [NUM_PROGS];
int hues [NUM_PROGS];

CRGB colors[]= {CRGB::Red,CRGB::Green,CRGB::Blue, CRGB::Yellow,CRGB::Purple,CRGB::White};

void setup() { 
  FastLED.addLeds<WS2811, DATA_PIN, RGB>(leds, NUM_LEDS); 
    Serial.begin(115200); // open the serial port at 9600 bps:
 for(int i =0;i<NUM_PROGS;i++){
  states[i]=OFF;
 }
 //Serial.print(FADESTEP);
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
    
    delays[i]-=DELAY;
    if(states[i]==UP){
      
      if(hues[i]>(255-FADESTEP)){
        Serial.print("I");

        //leds[progs[i]].maximizeBrightness(255);
        states[i]=ON;
        delays[i]= MIN_PERIOD + random(FLEX_PERIOD); // set random delay until it is turned off
      }else{
         // Serial.print("(");
         // Serial.print( hues[i]);
         // Serial.print(")");
        hues[i]+=FADESTEP;
        leds[progs[i]].maximizeBrightness(hues[i]);
      }  
    } else if(states[i]==DOWN){
      if(hues[i]<FADESTEP){
        Serial.print("O");
        
        //leds[progs[i]].maximizeBrightness(0);
        leds[progs[i]]=CRGB::Black;
        progs[i]= NUM_LEDS + 1;
        states[i]=OFF;
        delays[i]= MIN_PERIOD+random(FLEX_PERIOD); // set random delay until it is turned on
      } else {
        Serial.print("-");
        
        hues[i]-=FADESTEP;
        leds[progs[i]].maximizeBrightness(hues[i]);

      }
    }
    else if(delays[i]<0){
      int led = progs[i];
      if(states[i]==ON){ //turn of led
        states[i]=DOWN;
       }else{
        int nxtled = random(NUM_LEDS); //pick a random next LED
        if(!isPartOf(nxtled)){ // if not already active
          Serial.print("shifting to up");
          states[i]=UP;
          progs[i] = nxtled; //store led number in program
          Serial.print(random(NUM_COLORS));
          leds[progs[i]]=colors[random(NUM_COLORS)]; //set random color
          hues[i]=1;
          leds[progs[i]].maximizeBrightness(FADESTEP);
          //leds[progs[i]].fadeLightBy(1);
        }
      } 
    }  
  }
  FastLED.show();
  delay(DELAY);
}
