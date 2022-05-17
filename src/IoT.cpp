/*
  IoT.cpp firmware updates retrieved from a server.
  Based on:
  Wifi secure connection example for ESP32
  Running on TLS 1.2 using mbedTLS
  Suporting the following chipersuites:
  "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384","TLS_DHE_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_AES_256_CCM","TLS_DHE_RSA_WITH_AES_256_CCM",
  "TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384","TLS_DHE_RSA_WITH_AES_256_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA",
  "TLS_DHE_RSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8","TLS_DHE_RSA_WITH_AES_256_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384",
  "TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256",
  "TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256","TLS_DHE_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CCM",
  "TLS_DHE_RSA_WITH_AES_128_CCM","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256","TLS_DHE_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA",
  "TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA","TLS_DHE_RSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8","TLS_DHE_RSA_WITH_AES_128_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256",
  "TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","
  TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA",
  "TLS_DHE_PSK_WITH_AES_256_GCM_SHA384","TLS_DHE_PSK_WITH_AES_256_CCM","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384","TLS_DHE_PSK_WITH_AES_256_CBC_SHA384","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA",
  "TLS_DHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_DHE_WITH_AES_256_CCM_8",
  "TLS_DHE_PSK_WITH_AES_128_GCM_SHA256","TLS_DHE_PSK_WITH_AES_128_CCM","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256","TLS_DHE_PSK_WITH_AES_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA",
  "TLS_DHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_DHE_WITH_AES_128_CCM_8",
  "TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_RSA_WITH_AES_256_GCM_SHA384","TLS_RSA_WITH_AES_256_CCM","TLS_RSA_WITH_AES_256_CBC_SHA256","TLS_RSA_WITH_AES_256_CBC_SHA",
  "TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384",
  "TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA","TLS_RSA_WITH_AES_256_CCM_8","TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA",
  "TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384",
  "TLS_RSA_WITH_AES_128_GCM_SHA256","TLS_RSA_WITH_AES_128_CCM","TLS_RSA_WITH_AES_128_CBC_SHA256","TLS_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256",
  "TLS_ECDH_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA","TLS_RSA_WITH_AES_128_CCM_8",
  "TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256",
  "TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA",
  "TLS_RSA_PSK_WITH_AES_256_GCM_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384",
  "TLS_RSA_PSK_WITH_AES_128_GCM_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256",
  "TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA","TLS_PSK_WITH_AES_256_GCM_SHA384","TLS_PSK_WITH_AES_256_CCM","TLS_PSK_WITH_AES_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CBC_SHA","TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384",
  "TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CCM_8","TLS_PSK_WITH_AES_128_GCM_SHA256","TLS_PSK_WITH_AES_128_CCM","TLS_PSK_WITH_AES_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CBC_SHA",
  "TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CCM_8","TLS_PSK_WITH_3DES_EDE_CBC_SHA","TLS_EMPTY_RENEGOTIATION_INFO_SCSV"
  2017 - Evandro Copercini - Apache 2.0 License.
*/

#include "IoT.h"
#include "cert.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

// Global variables
int totalLength;       //total size of firmware
int currentLength = 0; //current size of written firmware

WiFiClientSecure WiFi_client;
char macStr[18] = { 0 };
unsigned long macLong = 0;
bool fwDownloadDone=false;

bool WiFi_setup() {
  int tries = 0;
  #ifdef USE_SERIAL
  //Initialize serial and wait for port to open:
  Serial.begin(115200);
  delay(100);
  #endif
  #if defined USE_SERIAL && DEBUG>=2
  Serial.print("Attempting to connect to SSID: ");
  Serial.println(ssid);
  #endif
  WiFi.begin(ssid, password);

  // attempt to connect to Wifi network:
  while ((WiFi.status() != WL_CONNECTED) && (tries<MAX_WIFI_CONNECT_ATTEMPTS)) {
#ifdef USE_SERIAL
    Serial.print(".");
#endif
    // wait 1 second for re-trying
    delay(1000);
    tries++;
  }

  uint8_t mac[6];

  WiFi.macAddress(mac);
  sprintf(macStr, "%02X:%02X:%02X:%02X:%02X:%02X", mac[0], mac[1], mac[2], mac[3], mac[4], mac[5]);
  if (tries >= MAX_WIFI_CONNECT_ATTEMPTS) return false;

#ifdef USE_SERIAL
  Serial.println();
  Serial.print(macStr);
  Serial.print(" connected to ");
  Serial.println(ssid);
#endif
  return true;
}

int fwUpdateFromServer()
{
  // connect to the server
  if(!WiFi_client.connected())
  {
    WiFi_client.setCACert(root_ca);
    if (!WiFi_client.connect(fwserver,443))
    {
      #ifdef USE_SERIAL
      Serial.print("ERROR: connecting to server ");
      Serial.println(fwserver);
      #endif
      return -1;
    }
  }

  if(WiFi_client.connected())
  {
    /*
    Send a GET to fw_update_check.php on the server with the custom header fields populated.
    The server will respond with:
    200 OK - returns the firmware file as an application/octet-stream
    304 Not Modified - running firmware matches what is on the server
    403 Forbidden - if something in the header is wrong
    404 File not found - if the firmware file required does not exist on the server
    500 ESP MAC not configured for updates - if the MAC passed is not in the approved list
    */
    fwDownloadDone = false;
    char sha256str[65] = {0};
    get_esp_sha256(sha256str);

    String client_request = (String(F("GET /fw_update_check.php HTTP/1.1\r\n")) +
                    "Host: " + fwserver + "\r\n" +
                    F("Content-Type: text/plain\r\n") +
                    F("User-Agent: ESP-http-Update\r\n") +
                    "X_ESP_STA_MAC: " + macStr + "\r\n" +
                    "X_ESP_RUNNING_SHA256: " + sha256str + "\r\n" +
                    "\r\n"); // blank line to indicate end of header
                    
    WiFi_client.print(client_request);

    #if defined USE_SERIAL && DEBUG>=2
    Serial.print("--------------client_request START-------------\n[");
    Serial.print(client_request);
    Serial.print("]\n--------------client_request END-------------\n");
    #endif
  }

  totalLength = 0;
  bool firmware_available = false;

  // get status line
  if(WiFi_client.connected())
  {
    String line = WiFi_client.readStringUntil('\n');
    // first line is the Status-Line https://www.w3.org/Protocols/rfc2616/rfc2616-sec6.html#sec6.1
    // Status-Line = HTTP-Version SP Status-Code SP Reason-Phrase CRLF
    // HTTP/<major version>.<minor version> <integer> <string>\r\n

    #if defined USE_SERIAL && DEBUG>=2
    Serial.print("Status-Line: ");
    Serial.println(line);
    #endif
    int first_separator = line.indexOf(" ");
    int second_separator = line.indexOf(" ", first_separator+1);
    String http_version = line.substring(0,first_separator);
    int status_code = line.substring(first_separator+1,second_separator).toInt();
    String reason_phrase = line.substring(second_separator+1);
    switch(status_code)
    {
      case 200: // 200 OK - returns the firmware file as an application/octet-stream
        firmware_available = true;
        Serial.println(F("firmware update sent from server"));
        break;
      case 404:
        Serial.println(F("firmware file not found on server"));
      default: // anything other than 200 means an error
        Serial.println(reason_phrase);
        break;
    }
  }
  // get the rest of the header
  while (WiFi_client.connected()) {
    String line = WiFi_client.readStringUntil('\n');
    #if defined USE_SERIAL && DEBUG>=2
    Serial.print("header-line: ");
    Serial.println(line);
    #endif
    if (line == "\r") {
      break;
    }
    else
    {
      // need to parse the line looking for content-length to set totalLength for firmware update
      //   content-length: 65
      if(line.indexOf("content-length")>=0)
        totalLength = line.substring(line.indexOf(" ")).toInt();

      //  date: Fri, 13 May 2022 17:20:00 GMT
      if(line.indexOf("date")>=0)
      {
        // parse the date string and set the time to whatever the server gives us
      }
    }
  }

  // get the firmware and update yourself
  if(firmware_available)
  {
    #if defined(USE_SERIAL) && DEBUG>0
    Serial.print("\nFirmware length = ");
    Serial.println(totalLength);
    Serial.println();
    #endif

    Update.begin(UPDATE_SIZE_UNKNOWN);
    uint8_t buf[FW_DOWNLOAD_BLOCK_SIZE] = { 0 };
    int total_bytes=0;
    int num_bytes_in=0;

    while (WiFi_client.connected() && !fwDownloadDone)
    {
      num_bytes_in = WiFi_client.read(buf,sizeof(buf));

      if(num_bytes_in>0) 
      {
        updateFirmware(buf,num_bytes_in);
      }
      delay(1);
    }
  }
  if (WiFi_client.connected())
  { 
    WiFi_client.stop();  // DISCONNECT FROM THE SERVER
    #ifdef USE_SERIAL
    Serial.println("\nDisconnected from server");
    #endif
  }
  return 0;
  
} // end of fwUpdateFromServer

void hexdump(uint8_t *data, size_t len)
{
  for(int i=0;i<len;i++)
  {
    #ifdef ASCII
    Serial.print((char)data[i]);
    #else
    Serial.printf("%02X ",data[i]);
    if((i+1)%32==0) Serial.println();
    #endif
  }
}

// Function to update firmware incrementally
// write in chunks equal to the buffer size
// firmware is written to device until server closes
void updateFirmware(uint8_t *data, size_t len)
{
  Serial.print(".");
  Update.write(data, len);
  // Print dots as a status update while waiting for update to finish
  currentLength += len;
  // if current length of written firmware is not equal to total firmware size, return and get the next chunk
  if(currentLength < totalLength) return;
  Update.end(true); // This MUST happen to validate the firmware upload
  Serial.printf("\nUpdate Success, Total Size: %u\n", currentLength);
  // Restart ESP32 to see changes
  delay(100); // wait X ms before restarting. Might not be required...?
  ESP.restart(); // HAVE to reboot or the ESP won't change app partitions
}

int get_esp_sha256(char * sha256str)
{
  const esp_partition_t *running_partition;
  uint8_t sha256[32] = {0};
  running_partition = esp_ota_get_running_partition();
  esp_err_t err = esp_partition_get_sha256(running_partition, sha256);
  if(err==ESP_OK)
  {
    for(int i=0;i<32;i++)
    {
      char hexChars[3];
      sprintf(hexChars,"%02X", sha256[i]);
      strcat(sha256str,hexChars);
    }
    return 0;
  }
  else
  {
    sprintf(sha256str,"esp_partition_get_sha256: error getting partition information");
    return -1;
  }
}
