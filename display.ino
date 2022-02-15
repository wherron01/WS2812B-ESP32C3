#include <SPI.h>
#include <SD.h>
#include <FastLED.h>

#define NUM_LEDS 256
CRGB leds[NUM_LEDS];

String fileName = "/colors";

void setup() {
  // put your setup code here, to run once:
  FastLED.addLeds<WS2812B,8,GRB>(leds, NUM_LEDS).setCorrection(TypicalLEDStrip);
  FastLED.setBrightness(255);
  Serial.begin(115200);
  while(!SD.begin()) {
    for(int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB(random8(),0,0);
    FastLED.show();
  }
}

void loop() {
  File colors = SD.open(fileName);
  if(!colors) for(int i = 0; i < NUM_LEDS; i++) leds[i] = CRGB(random8(),0,random8());
  while(colors.available()) {
    for(int i = 0; i < NUM_LEDS; i++) {
      leds[i] = CRGB(colors.read(), colors.read(), colors.read()); 
      yield();
    }
    FastLED.show();
  }
  delay(1);
  colors.close();
}
