#ifndef IOT_H
#define IOT_H

#include <WiFiClientSecure.h>
#include <Update.h>
#include "esp_ota_ops.h"

#define USE_SERIAL
#define DEBUG 1

int postDataToServer(float howMoist, float batteryV);
bool WiFi_setup();
int fwVersionFromServer();
int fwUpdateFromServer();
void updateFirmware(uint8_t *data, size_t len);
void sha256_2_string(uint8_t *sha256, char *sha256str);
esp_err_t running_sha256(uint8_t *sha256);
bool check_fw_from_server(char *sha256fromServer);

#endif