// Control the OSCOLA connected lamp via the Arduino Yun Mailbox
// REST API: Try HTTP POST http://OSCOLA_LOCAL_IP/mailbox/rrggbb
// For remote Web & SSH access see https://yaler.net/arduino-yun

// Based on http://arduino.cc/en/Tutorial/MailboxReadMessage
// and NeoPixel Ring simple sketch, Copyright (c) 2013, Shae Erisson
// and https://github.com/CasaJasmina/OSCOLA/ (c) 2015, Jesse Howard,
// Stefano Paradiso and Lorenzo Romagnoli

// Copyright (c) 2015, @tamberg
// Licensed under GPLv3

#include <Mailbox.h>
#include <Adafruit_NeoPixel.h>

#define PIN 6
#define NUMPIXELS 47

Adafruit_NeoPixel pixels = Adafruit_NeoPixel(
  NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

int color[3] = {0, 0, 0};

void convertHexColor(String hexColor) {
  long c = (long) strtol(&hexColor[0], NULL, 16);
  color[0] = c >> 16;
  color[1] = c >> 8 & 0xFF;
  color[2] = c & 0xFF;
}

void setPixelsColor(int r, int g, int b) {
  for (int i = 0; i < NUMPIXELS; i++) {
    pixels.setPixelColor(i, pixels.Color(r, g, b));
  }
  pixels.show();
}

void setup() {
  pixels.begin();
  for (int i = 0; i < 100; i++) {
    setPixelsColor(i, i, i);
    delay(100);
  }
  Bridge.begin();
  Mailbox.begin();
  Serial.begin(9600);
  //while (!Serial);
}

void loop() {
  String message;
  while (Mailbox.messageAvailable()) {
    Mailbox.readMessage(message);
    Serial.println(message);
    convertHexColor(message);
    setPixelsColor(color[0], color[1], color[2]);
  }
}
