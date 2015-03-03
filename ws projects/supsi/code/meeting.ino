// lamp for arduino lamp workshop in torino on 20/21.2.2015 in
// fabian frei
// fabian.frei@supsi.ch

// include process library
#include <Process.h>
#include "MQTTclient.h"
#include <Adafruit_NeoPixel.h>
#include <avr/power.h>


// define DEBUG for debug mode
# define DEBUG

// define AMOUNT of Pictures
#define GIF_AMOUNT 10

// define the delay after switching one led
#define DELAY 5

// define the shade of white for the reset
#define RESET 50

#define MQTT_HOST "85.119.83.194" // test.mosquitto.org


// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      67

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int color[3] = {100, 100, 100}; //the Array that defines the color of the light

// namespace and struct
// to store both the colors and the hits in one place
// we are going to stuff those structs into an array
// you can access this via lamp::rgbColorAndHits

namespace lamp {

    typedef struct {
      int r;
      int g;
      int b;
      int hits;
    } rgbColorAndHits;

  
  rgbColorAndHits hits[GIF_AMOUNT];
}

void setup() {

  #ifdef DEBUG
  Serial.begin(9600);
  delay(5000);
  Serial.println("Running in Debug mode");
  #endif

  pixels.begin(); // This initializes the NeoPixel library.
  delay(1000);

  // init all the hit structs
  for(int i = 0; i > GIF_AMOUNT; i++) {
    lamp::hits[i] = { 0, 0, 0, 0 };
  }

  #ifdef DEBUG
  Serial.println("all hit containers initialized");
  #endif

  pinMode(13, OUTPUT);

  #ifdef DEBUG
  Serial.println("Waiting for linux to boot");
  #endif
  Bridge.begin();

  #ifdef DEBUG
  Serial.println("Linux booted");
  Serial.println("Waiting for Wifi to connect");
  #endif

  delay(10000);//because we wait for the wifi to connect!!
  #ifdef DEBUG
  Serial.println("Waited 10 sec");
  #endif
  
  mqtt.begin(MQTT_HOST, 1883);
  mqtt.subscribe("oscola/fabian/changeColor", registerCheck);

  resetAllLeds();

  #ifdef DEBUG
  Serial.println("all leds reset");
  delay(2000);
  #endif
  
  // Process p;
  // p.runShellCommand("blink-start 100"); //start the blue blink

  #ifdef DEBUG
  // we display some debug colors
  // registerCheckTest("#F01616"); // red
  // delay(1000);
  // registerCheckTest("#0E6DEC"); // blue
  // delay(1000);
  // registerCheckTest("#17EC52"); // green
  #endif

}

void loop() {

  mqtt.monitor();

  #ifdef DEBUG

  // display some stuff regarding 
  Process wifiCheck;

  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");

  /*while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }*/

  //Serial.println();

  //delay(5000);

  #endif
}


void hexColorConverter(String c) {

  String hexstring = c.substring(1);

  #ifdef DEBUG
  Serial.print(hexstring);
  Serial.print("-");
  #endif

  long number = (long) strtol( &hexstring[0], NULL, 16);
  color[0] = number >> 16;
  color[1] = number >> 8 & 0xFF;
  color[2] = number & 0xFF;

  #ifdef DEBUG
  Serial.print(color[0]);
  Serial.print("-");
  Serial.print(color[1]);
  Serial.print("-");
  Serial.println(color[2]);
  #endif

}

// my stuff

void resetAllLeds() {
  for(int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(RESET, RESET, RESET));
    pixels.show();
    delay(DELAY);
  }
}

void registerCheck(const String& topic, const String& subtopic, const String& message) {
  #ifdef DEBUG
  Serial.println("got message:" + message);
  #endif

  registerCheckTest(message);
}

void registerCheckTest(String message) {
  #ifdef DEBUG
  Serial.println(message);
  Serial.println("checking all the hits");
  hexColorConverter(message);
  Serial.println(color[0]);
  Serial.println(color[1]);
  Serial.println(color[2]);
  Serial.println("checking all the hits");
  #endif

  for(int i = 0; i < GIF_AMOUNT; i++) {
    if(lamp::hits[i].r == color[0] && lamp::hits[i].g == color[1] && lamp::hits[i].b == color[2]) { // we have a hit
      lamp::hits[i].hits++;

      #ifdef DEBUG
      Serial.print("we found something, with ");
      Serial.println(lamp::hits[i].hits);
      #endif

      recalculateColors();
      return; // we return early because there is only one hit
    }
  }
  // we did not find the color, lets add it
  #ifdef DEBUG
  Serial.println("we found nothing, adding new color");
  #endif
  for(int i = 0; i < GIF_AMOUNT; i++) {
    if(lamp::hits[i].hits == 0) {
      lamp::hits[i].hits = 1;
      lamp::hits[i].r = color[0];
      lamp::hits[i].g = color[1];
      lamp::hits[i].b = color[2];
      recalculateColors();
      return; // we return early, we because only one new color
    }
  }
}

void recalculateColors() {
  int total = 0;
  int offset = 0;

  for(int i = 0; i < GIF_AMOUNT; i++) {
    if(lamp::hits[i].hits == 0) {
      break;
    }
    total += lamp::hits[i].hits;
  }

  #ifdef DEBUG
  Serial.print("total: ");
  Serial.println(total);
  #endif


  for(int i = 0; i < GIF_AMOUNT; i++) {

    int amount = floor(float(lamp::hits[i].hits) / float(total) * NUMPIXELS);

    #ifdef DEBUG
    Serial.print("amount: ");
    Serial.println(amount);
    Serial.print("offset: ");
    Serial.println(offset);
    #endif

    for(int y = offset; y < offset + amount && y < NUMPIXELS; y++) {
      #ifdef DEBUG
      Serial.print("painting pixel ");
      Serial.println(y);
      Serial.print("with color: ");
      Serial.print(lamp::hits[i].r);
      Serial.print("-");
      Serial.print(lamp::hits[i].g);
      Serial.print("-");
      Serial.println(lamp::hits[i].b);
      #endif

      pixels.setPixelColor(y, pixels.Color(lamp::hits[i].r, lamp::hits[i].g, lamp::hits[i].b));
      pixels.show();
      delay(DELAY);
    }
    offset += amount;
    // we return early when we reach the maximum amount of pixels
    if(offset == NUMPIXELS) {
      #ifdef DEBUG
      Serial.println("maximum offset reached");
      #endif
      return;
    }
    // we reached the last one, now we need to check if need to fill up
    if(i == GIF_AMOUNT - 1 && offset < NUMPIXELS) {
      #ifdef DEBUG
      Serial.print("we need to fill up: ");
      Serial.println(NUMPIXELS - offset);
      #endif

      for(;offset < NUMPIXELS; offset++) {
        pixels.setPixelColor(offset, pixels.Color(lamp::hits[i].r, lamp::hits[i].g, lamp::hits[i].b));
        pixels.show();
        delay(DELAY);
      }
    }
  }
}
