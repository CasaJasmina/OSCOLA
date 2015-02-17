/*
this sketch can be used to set the wifi properties of an Arduino YUN. 
It works on wpa2 networks. 
Use it at your own risk.

This example code is in the public domain.

17 feb 2015
by Lorenzo Romagnoli
*/

#include <Bridge.h>
#include <Process.h>

String ssid = "yourSSIS";
String psw = "yourPSW!";

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
  p.runShellCommand("uci set wireless.@wifi-iface[0].encryption='psk2'");
  p.runShellCommand("uci set wireless.@wifi-iface[0].mode='sta'");
  p.runShellCommand("uci set wireless.@wifi-iface[0].ssid='" + ssid + "'");
  p.runShellCommand("uci set wireless.@wifi-iface[0].key='" + psw + "'");
  p.runShellCommand("uci set wireless.radio0.channel='auto'");
  p.runShellCommand("uci set wireless.radio0.country='IT'");
  p.runShellCommand("uci delete network.lan.ipaddr");
  p.runShellCommand("uci delete network.lan.netmask");
  p.runShellCommand("uci set network.lan.proto='dhcp'");
  p.runShellCommand("uci commit");
  p.runShellCommand("/etc/init.d/network restart");

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


