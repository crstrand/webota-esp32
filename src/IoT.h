#ifndef IOT_H
#define IOT_H

#include <WiFiClientSecure.h>
#include <Update.h>
#include <HTTPClient.h>
#include "esp_ota_ops.h"

#define USE_SERIAL
//#define DEBUG 0
#define MAX_WIFI_CONNECT_ATTEMPTS 30
#define FW_DOWNLOAD_BLOCK_SIZE 4096 // 8192 causes a stack overflow

bool WiFi_setup();
int fwUpdateFromServer();
void updateFirmware(uint8_t *data, size_t len);
int get_esp_sha256(char * sha256str);

#endif