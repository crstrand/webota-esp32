#ifndef IOT_H
#define IOT_H

#include <Arduino.h>
//#include <WiFi.h>
#include <WiFiClientSecure.h>

#define USE_SERIAL
#define DEBUG 2
#define MAX_WIFI_CONNECT_ATTEMPTS 30

extern char macStr[18];

bool WiFi_setup();

#endif