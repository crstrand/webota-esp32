#pragma once
#include <stdint.h>
#include <stddef.h>

int fwUpdateFromServer(char *macStr);
void updateFirmware(uint8_t *data, size_t len);
int get_esp_sha256(char * sha256str);
