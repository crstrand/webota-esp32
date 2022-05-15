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
#define VERSION_STRING "1.0.4"

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
  //fwUpdateFromServer();
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
      default:
        Serial.println("r - read firmware version from server");
    }
  }
  #endif
  delay(100);
}
