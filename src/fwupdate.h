#ifndef FWUPDATE_H
#define FWUPDATE_H

#include <Update.h>
#include <HTTPClient.h>
#include <WiFiClientSecure.h>
#include "esp_ota_ops.h"

#define FW_DOWNLOAD_BLOCK_SIZE 4096 // 8192 causes a stack overflow

int fwUpdateFromServer(char *macStr);
void updateFirmware(uint8_t *data, size_t len);
int get_esp_sha256(char * sha256str);

#endif