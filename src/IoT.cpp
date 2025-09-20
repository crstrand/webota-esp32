#include "IoT.h"
//#include "cert.h"
#include "secrets.h"
#include <sstream>
#include <iostream>
#include <string>
//using namespace std;

// Global variables
char ssid[128] = {0};
char password[128] = {0};

//#define HOME

char server_reply[2000]="\0";
static char sensorID[32] = { 0 };
char macStr[18] = { 0 };
#define MAX_WIFI_CONNECT_SECONDS 10

bool WiFi_setup() {
#ifdef HOME
  strcpy(ssid,ssid_home);
  strcpy(password, pass_home);
#else
  strcpy(ssid,ssid_main);
  strcpy(password, pass_main);
#endif
  int connect_timeout = 0;
#ifdef USE_SERIAL
  Serial.print("\nAttempting to connect to SSID: ");
  Serial.println(ssid);
#endif
  // attempt to connect to Wifi network:
  WiFi.begin(ssid, password);
  while ((WiFi.status() != WL_CONNECTED) && (connect_timeout<MAX_WIFI_CONNECT_SECONDS)) {
#ifdef USE_SERIAL
    Serial.print(".");
#endif
    // wait 1 second for re-trying
    delay(1000);
    connect_timeout++;
  }

  if (connect_timeout >= MAX_WIFI_CONNECT_SECONDS) // try fallback AP
  {
    connect_timeout = 0;
    strcpy(ssid,ssid_fb);
    strcpy(password,pass_fb);
    // attempt to connect to Wifi network:
    Serial.print("\nAttempting to connect to SSID: ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);
    while ((WiFi.status() != WL_CONNECTED) && (connect_timeout<MAX_WIFI_CONNECT_SECONDS)) {
  #ifdef USE_SERIAL
      Serial.print(".");
  #endif
      // wait 1 second for re-trying
      delay(1000);
      connect_timeout++;
    }
  }

  if (connect_timeout >= MAX_WIFI_CONNECT_SECONDS) return false;

#ifdef USE_SERIAL
  uint8_t mac[6];
  WiFi.macAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  strcpy(sensorID,macStr);

  Serial.println();
  Serial.print(sensorID);
  Serial.print(" connected to ");
  Serial.println(ssid);
#endif
  return true;
}
