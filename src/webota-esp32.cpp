/* WebOTA.ino
 *  
 * by Roland Pelayo 
 * PlatformIO update by Cam Strandlund
 * 
 * Update ESP32 firmware via external web server
 */
 
#include "IoT.h"
#include "fwupdate.h"

#define VERSION_STRING "1.1.6"

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
    Serial.printf("\n\nVersion %s  Compiled on %s %s\n\n",VERSION_STRING,__DATE__, __TIME__);
  }
}

void hibernate(uint64_t time_in_us) {
  // deep sleep with all this stuff explicitly turned off is called hibernation
  // ESP32 current draw in hibernation is about 5uA
  // Lolin32-Lite save more mA by disabling LED1 by removing R6 (2kohm)
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH,   ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_OFF);
  esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL,         ESP_PD_OPTION_OFF);

  esp_sleep_enable_timer_wakeup(time_in_us);
  esp_deep_sleep_start();
}

void setup() {
  Serial.begin(115200);
  printVersion();

  if(WiFi_setup())
    fwUpdateFromServer(macStr);
  if(TIME_TO_SLEEP/uS_TO_S_FACTOR < 3600)
    Serial.printf("hibernating %d seconds until the next check for firmware\n",TIME_TO_SLEEP/uS_TO_S_FACTOR);
  else
    Serial.printf("hibernating %.1f hours until the next check for firmware\n",float(TIME_TO_SLEEP/HOUR_IN_uS));
  hibernate(TIME_TO_SLEEP);
}

void loop() {} // because of the deep sleep, this will never run
