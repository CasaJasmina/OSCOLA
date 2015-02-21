// NeoPixel Ring simple sketch (c) 2013 Shae Erisson
// released under the GPLv3 license to match the rest of the AdaFruit NeoPixel library

// include process library
#include <Process.h>
#include "MQTTclient.h"

#define MQTT_HOST "85.119.83.194" // test.mosquitto.org


#include <Adafruit_NeoPixel.h>
#include <avr/power.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1
#define PIN            6

// How many NeoPixels are attached to the Arduino?
#define NUMPIXELS      60

// When we setup the NeoPixel library, we tell it how many pixels, and which pin to use to send signals.
// Note that for older NeoPixel strips you might need to change the third parameter--see the strandtest
// example for more information on possible values.
Adafruit_NeoPixel pixels = Adafruit_NeoPixel(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int delayval = 500; // delay for half a second

int color[3] = {100, 100, 100}; //the Array that defines the color of the light

void setup() {

  pixels.begin(); // This initializes the NeoPixel library.
  changeAllLedColors(0, 0, 0);
  for (int i = 0; i < 100; i++) {
    changeAllLedColors(i, i, i);
    delay(100);
  }

  //Serial.begin(9600);
  pinMode(13, OUTPUT);

  Bridge.begin();
  changeAllLedColors(0, 0, 0);
  delay(10);
  changeAllLedColors(100, 100, 100);


  delay(10000);//because we wait for the wifi to connect!!

  mqtt.begin(MQTT_HOST, 1883);
  mqtt.subscribe("oscola/23981479834/changeColor", colorChange);



}

void loop() {

  mqtt.monitor();

  Process wifiCheck;

  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");

  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }

  Serial.println();

  delay(5000);

}

void colorChange(const String& topic, const String& subtopic, const String& message) {
  //Serial.println(message);

  digitalWrite(13, HIGH);
  delay(100);
  digitalWrite(13, LOW);

  hexColorConverter(message);
  changeAllLedColors(color[0], color[1], color[2]);
}

void changeAllLedColors(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b)); // Moderately bright green color.
  }
  pixels.show();
}

void changeSinglePixel(int index, int r, int g, int b) {
  pixels.setPixelColor(index, pixels.Color(r, g, b)); // Moderately bright green color.
  pixels.show();
}

void hexColorConverter(String c) {


  String hexstring = c.substring(1);

  //Serial.print(hexstring);
  //Serial.print("-");

  long number = (long) strtol( &hexstring[0], NULL, 16);
  color[0] = number >> 16;
  color[1] = number >> 8 & 0xFF;
  color[2] = number & 0xFF;

  //  Serial.print(color[0]);
  //  Serial.print("-");
  //  Serial.print(color[1]);
  //  Serial.print("-");
  //  Serial.println(color[2]);

}


