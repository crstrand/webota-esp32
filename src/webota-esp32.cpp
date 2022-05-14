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

void setup() {
  Serial.begin(115200);

  WiFi_setup();
//  fwVersionFromServer();
  fwUpdateFromServer();
}

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
        fwVersionFromServer();
        break;
      default:
        Serial.println("r - read firmware version from server");
    }
  }
  #endif
  delay(100);
}
