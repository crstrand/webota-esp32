/* WebOTA.ino
 *  
 * by Roland Pelayo 
 * 
 * Update ESP32 firmware via external web server
 */
 
#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include "IoT.h"
#define VERSION_STRING "1.1.0"

#define uS_TO_S_FACTOR (uint64_t)1000000  /* Conversion factor for micro seconds to seconds */
#define uS_IN_M_FACTOR (uint64_t)60*uS_TO_S_FACTOR
#define _30S_in_uS uint64_t(30)*uS_TO_S_FACTOR        /* Time ESP32 will go to sleep (in seconds) */
#define HOUR_IN_uS uint64_t(3600)*uS_TO_S_FACTOR
#ifdef DEBUG
#define TIME_TO_SLEEP _30S_in_uS
#else
#define TIME_TO_SLEEP HOUR_IN_uS
#endif

void printVersion()
{
  if(Serial)
  {
    Serial.printf("Version %s  Compiled on %s %s\n",VERSION_STRING,__DATE__, __TIME__);
  }
}

void setup() {
  Serial.begin(115200);
  printVersion();

  WiFi_setup();
  checkForNewFirmware();
  // prep deep sleep
  Serial.printf("sleeping %d seconds until the next check for firmware\n",TIME_TO_SLEEP/uS_TO_S_FACTOR);
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP);
  esp_deep_sleep_start();

}

char none[5]={"none"};

void loop() 
{
  #ifdef USE_SERIAL
  char cmd;
  if(Serial.available())
  {
    cmd = Serial.read();
    switch (cmd)
    {
      case 'r':
        Serial.println("Checking server for fw...\n");
        checkForNewFirmware();
        break;
      case 'v':
        printVersion();
        break;
      case 's':
        check_fw_from_server(none);
        break;
      case 'b':
        ESP.restart(); // HAVE to reboot or the ESP won't change app partitions
        break;
      default:
        Serial.println("r - read firmware version from server\ns - get sha256 sum of running partition\nv - print version string\nb - reboot ESP\n");
    }
  }
  #endif
  delay(100);
}
