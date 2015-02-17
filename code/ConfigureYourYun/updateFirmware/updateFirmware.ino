/*
This sketch can be used to set the update the firmware of your Arduino YUN
It assumes that you already downloaded the last version of OpenWrt for Arduino YUN from http://arduino.cc/en/Main/Software
INSTRUCTIONS:

-> download the latest Openwrt image from http://arduino.cc/en/Main/Software
-> extract the archive and copy openwrt-ar71xx-generic-yun-16M-squashfs-sysupgrade.bin to the root of an usb drive
-> connect the usb drive after that the yun is running
-> and upload this sketch!
-> the blue led will start blinking and will stop once the upgrade is finished

This code is in the public domain.

Use this code at your own risk!

17 feb 2015
by Lorenzo Romagnoli assisted by Federico Fissore
*/

#include <Bridge.h>
#include <Process.h>

Process p;


void setup() {
  Serial.begin(9600);  // initialize serial communication
  //while (!Serial);     // do nothing until the serial monitor is opened

  Serial.println("Starting bridge...\n");
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Bridge.begin();
  Serial.println("bridge started");
  Serial.println("Running sys upgrade script please wait...");

  p.runShellCommand("cp /mnt/sda1/openwrt-ar71xx-generic-yun-16M-squashfs-sysupgrade.bin /tmp || exit 1");
  p.runShellCommand("blink-start 100");
  p.runShellCommand("exec sysupgrade -n /tmp/openwrt-ar71xx-generic-yun-16M-squashfs-sysupgrade.bin");

}

void loop() {

}


