/* WebOTA.ino
 *  
 * by Roland Pelayo 
 * PlatformIO update by Cam Strandlund
 * 
 * Update ESP32 firmware via external web server
 */
 
#include <WiFi.h>
#include <HTTPClient.h>
#include <Update.h>
#include "IoT.h"
#define VERSION_STRING "1.1.5"

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
  fwUpdateFromServer();
  // prep deep sleep
  if(TIME_TO_SLEEP/uS_TO_S_FACTOR >= 3600)
    Serial.printf("sleeping %d seconds until the next check for firmware\n",TIME_TO_SLEEP/uS_TO_S_FACTOR);
  else
    Serial.printf("sleeping %.1f hours until the next check for firmware\n",float(TIME_TO_SLEEP/HOUR_IN_uS));
  esp_sleep_enable_timer_wakeup(TIME_TO_SLEEP);
  esp_deep_sleep_start();

}

void loop() {} // because of the deep sleep, this will never run
