/*
this sketch can be used to set the wifi properties of an Arduino YUN.
It works on wpa2 networks.
Use it at your own risk.

This example code is in the public domain.

17 feb 2015
by Lorenzo Romagnoli assisted by Federico Fissore
*/

#include <Bridge.h>
#include <Process.h>
#include "password.h"

void setup() {
  Serial.begin(9600);  // initialize serial communication
  while (!Serial);     // do nothing until the serial monitor is opened

  Serial.println("Starting bridge...\n");
  pinMode(13, OUTPUT);
  digitalWrite(13, LOW);

  Bridge.begin();
  Serial.println("bridge started");
  Serial.println("Running WIFI configuration scripts, please wait...");
  Process p;



  p.runShellCommand("blink-start 100"); //start the blue blink

  p.runShellCommand("hostname " + yunName); //change the current hostname
  p.runShellCommand("uci set system.@system[0].hostname='" + yunName+"'"); //change teh hostname in uci
  
  p.runShellCommand("arduino.@arduino[0].access_point_wifi_name='"+ wifiAPname+ "'");

//this block resets the wifi psw
  p.runShellCommand("uci set wireless.@wifi-iface[0].encryption='psk2'");
  p.runShellCommand("uci set wireless.@wifi-iface[0].mode='sta'");
  p.runShellCommand("uci set wireless.@wifi-iface[0].ssid='" + wifissid + "'");
  p.runShellCommand("uci set wireless.@wifi-iface[0].key='" + wifipsw + "'");
  p.runShellCommand("uci set wireless.radio0.channel='auto'");
  p.runShellCommand("uci set wireless.radio0.country='IT'");
  p.runShellCommand("uci delete network.lan.ipaddr");
  p.runShellCommand("uci delete network.lan.netmask");
  p.runShellCommand("uci set network.lan.proto='dhcp'");

  p.runShellCommand("echo -e \"" + yunPsw + "\n" + yunPsw + "\" | passwd root"); //change the passwors

  p.runShellCommand("uci commit"); //save the mods done via UCI

  p.runShellCommand("/etc/init.d/network restart");

  p.runShellCommand("/etc/init.d/avahi-daemon restart"); // restart the avahi daemon so that the board reannounce itself on the network


  p.runShellCommand("blink-stop");

  Serial.println("WIFI configuration finished... just wait for the white led to show up!");

}

void loop() {
  Process wifiCheck;

  wifiCheck.runShellCommand("/usr/bin/pretty-wifi-info.lua");

  while (wifiCheck.available() > 0) {
    char c = wifiCheck.read();
    Serial.print(c);
  }

  Serial.println();

  delay(5000);
}


