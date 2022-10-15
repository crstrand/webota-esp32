#include "IoT.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

// Global variables
const char* ssid     = "BELL197";    // your network SSID (name of wifi network)
const char* password = "FD44C6C97555";        // your network password

char macStr[18] = { 0 };
unsigned long macLong = 0;

bool WiFi_setup() {
  int tries = 0;
  #ifdef USE_SERIAL
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);
  #endif
  #if defined USE_SERIAL && DEBUG>=2
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  #endif
  WiFi.begin(ssid, password);
/*
  //WiFiManager
  //Local intialization. Once its business is done, there is no need to keep it around
  ESP_WiFiManager wifiManager;
  //reset saved settings
  wifiManager.resetSettings();
  
  //set custom ip for portal
  //wifiManager.setAPStaticIPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

  //fetches ssid and pass from eeprom and tries to connect
  //if it does not connect it starts an access point with the specified name
  //here  "AutoConnectAP"
  //and goes into a blocking loop awaiting configuration
  wifiManager.autoConnect("LonelyInukShuk","secret");
  //or use this for auto generated name ESP + ChipID
  //wifiManager.autoConnect();
*/
  // attempt to connect to Wifi network:
  while ((WiFi.status() != WL_CONNECTED) && (tries<MAX_WIFI_CONNECT_ATTEMPTS)) {
#ifdef USE_SERIAL
    Serial.print(".");
#endif
    // wait 1 second for re-trying
    delay(1000);
    tries++;
  }
  if (tries >= MAX_WIFI_CONNECT_ATTEMPTS)
  {
#ifdef USE_SERIAL
    Serial.printf("\nWiFi connection failed after %i seconds\n",tries);
#endif
    return false;
  } 

  uint8_t mac[6];

  WiFi.macAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);

#ifdef USE_SERIAL
  Serial.println("");
  Serial.print(macStr);
  Serial.print(" connected to ");
  Serial.println(ssid);
#endif
  return true;
}

