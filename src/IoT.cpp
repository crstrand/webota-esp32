/*
  Wifi secure connection example for ESP32
  Running on TLS 1.2 using mbedTLS
  Suporting the following chipersuites:
  "TLS_ECDHE_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_AES_256_GCM_SHA384","TLS_DHE_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_AES_256_CCM","TLS_DHE_RSA_WITH_AES_256_CCM","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA384","TLS_DHE_RSA_WITH_AES_256_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_256_CBC_SHA","TLS_DHE_RSA_WITH_AES_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_256_CCM_8","TLS_DHE_RSA_WITH_AES_256_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDHE_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_AES_128_GCM_SHA256","TLS_DHE_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CCM","TLS_DHE_RSA_WITH_AES_128_CCM","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA256","TLS_DHE_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDHE_ECDSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_RSA_WITH_AES_128_CBC_SHA","TLS_DHE_RSA_WITH_AES_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_AES_128_CCM_8","TLS_DHE_RSA_WITH_AES_128_CCM_8","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDHE_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_DHE_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDHE_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_RSA_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_AES_256_GCM_SHA384","TLS_DHE_PSK_WITH_AES_256_CCM","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA384","TLS_DHE_PSK_WITH_AES_256_CBC_SHA384","TLS_ECDHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_AES_256_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_DHE_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_DHE_WITH_AES_256_CCM_8","TLS_DHE_PSK_WITH_AES_128_GCM_SHA256","TLS_DHE_PSK_WITH_AES_128_CCM","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA256","TLS_DHE_PSK_WITH_AES_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_AES_128_CBC_SHA","TLS_DHE_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_DHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDHE_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_DHE_WITH_AES_128_CCM_8","TLS_ECDHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_DHE_PSK_WITH_3DES_EDE_CBC_SHA","TLS_RSA_WITH_AES_256_GCM_SHA384","TLS_RSA_WITH_AES_256_CCM","TLS_RSA_WITH_AES_256_CBC_SHA256","TLS_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_RSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_RSA_WITH_AES_256_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_AES_256_CBC_SHA","TLS_RSA_WITH_AES_256_CCM_8","TLS_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_256_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_RSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_GCM_SHA384","TLS_ECDH_ECDSA_WITH_CAMELLIA_256_CBC_SHA384","TLS_RSA_WITH_AES_128_GCM_SHA256","TLS_RSA_WITH_AES_128_CCM","TLS_RSA_WITH_AES_128_CBC_SHA256","TLS_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_RSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_RSA_WITH_AES_128_CBC_SHA","TLS_ECDH_ECDSA_WITH_AES_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_AES_128_CBC_SHA","TLS_RSA_WITH_AES_128_CCM_8","TLS_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_CAMELLIA_128_CBC_SHA","TLS_ECDH_RSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_RSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_GCM_SHA256","TLS_ECDH_ECDSA_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_RSA_WITH_3DES_EDE_CBC_SHA","TLS_ECDH_ECDSA_WITH_3DES_EDE_CBC_SHA","TLS_RSA_PSK_WITH_AES_256_GCM_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_256_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_RSA_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_RSA_PSK_WITH_AES_128_GCM_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA256","TLS_RSA_PSK_WITH_AES_128_CBC_SHA","TLS_RSA_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_RSA_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_RSA_PSK_WITH_3DES_EDE_CBC_SHA","TLS_PSK_WITH_AES_256_GCM_SHA384","TLS_PSK_WITH_AES_256_CCM","TLS_PSK_WITH_AES_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CBC_SHA","TLS_PSK_WITH_CAMELLIA_256_GCM_SHA384","TLS_PSK_WITH_CAMELLIA_256_CBC_SHA384","TLS_PSK_WITH_AES_256_CCM_8","TLS_PSK_WITH_AES_128_GCM_SHA256","TLS_PSK_WITH_AES_128_CCM","TLS_PSK_WITH_AES_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CBC_SHA","TLS_PSK_WITH_CAMELLIA_128_GCM_SHA256","TLS_PSK_WITH_CAMELLIA_128_CBC_SHA256","TLS_PSK_WITH_AES_128_CCM_8","TLS_PSK_WITH_3DES_EDE_CBC_SHA","TLS_EMPTY_RENEGOTIATION_INFO_SCSV"]
  2017 - Evandro Copercini - Apache 2.0 License.
*/

#include "IoT.h"
#include "cert.h"
#include <sstream>
#include <iostream>
#include <string>
using namespace std;

#define HOME
#ifdef HOME
const char* ssid     = "Strandlund_IoT";     // your network SSID (name of wifi network)
const char* password = "3066962933"; // your network password
#else
const char* ssid     = "Attaguest";     // your network SSID (name of wifi network)
const char* password = "Antonina"; // your network password
#endif

const char*  server = "botany.strantech.ca";  // Server URL
const char*  fwserver = "fw.strantech.ca";  // Server URL

// Global variables
int totalLength;       //total size of firmware
int currentLength = 0; //current size of written firmware

WiFiClientSecure WiFi_client;
char server_reply[2000]="\0";
static char sensorID[32] = { 0 };
char macStr[18] = { 0 };
unsigned long macLong = 0;
bool fwDownloadDone=false;

#define MAX_WIFI_CONNECT_ATTEMPTS 30

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
  strcpy(sensorID,macStr);
  if (tries >= MAX_WIFI_CONNECT_ATTEMPTS) return false;

#ifdef USE_SERIAL
  Serial.println();
  Serial.print(sensorID);
  Serial.print(" connected to ");
  Serial.println(ssid);
#endif
  return true;
}

int postDataToServer(float howMoist, float batteryV)
{
  int i=0;
  char data[64];
  sprintf(data,"sid1=%s&moist1=%s&bat1=%s",macStr,String(howMoist,1),String(batteryV,2));
#ifdef USE_SERIAL
  Serial.println(data);
#endif
  // connect to the server, post the data then disconnect
  WiFi_client.setCACert(strantech_root_ca);
  if (WiFi_client.connect(server,443)) {
    
    String client_request = (String("POST /add.php HTTP/1.1\r\n") +
                     "Host: " + server + "\r\n" +
                     "Content-Type: application/x-www-form-urlencoded\r\n" +
                     "Content-Length: " + strlen(data) + "\r\n\r\n" + data + "\r\n\r\n");
    WiFi_client.print(client_request);
    delay(1000); // wait for a second for add.php to run

    #if defined USE_SERIAL && DEBUG>=2
    Serial.println("--------------client_request START-------------");
    Serial.print(client_request);
    Serial.println("\n--------------client_request END-------------\n");
    #endif
  } 
  else
  {
    #ifdef USE_SERIAL
    Serial.print("ERROR: connecting to server ");
    Serial.println(server);
    #endif
    return -1;
  }

  // Wait a second for server to start sending reply string so we don't miss some of it
  delay(1000);
  // create buffer for read
  Update.begin(UPDATE_SIZE_UNKNOWN);
  uint8_t buff[128] = { 0 };
  i=0;
  while (WiFi_client.available()) {
    int num_bytes_in = WiFi_client.read(buff,128);
    updateFirmware(buff,num_bytes_in);
  }
  server_reply[i]=0; // null terminate the string
  #if defined USE_SERIAL && DEBUG>=2
  Serial.print("reply length= ");
  Serial.println(strlen(server_reply));
  Serial.println("--------------server_reply START-------------");
  Serial.print(server_reply);
  Serial.println("\n--------------server_reply END-------------\n");
  #endif

  if (WiFi_client.connected()) { 
    WiFi_client.stop();  // DISCONNECT FROM THE SERVER
    #if defined USE_SERIAL && DEBUG>=2
    Serial.println("\nDisconnected from server");
    #endif
  }
  return 0;
} // end of postDataToServer

/*
  --------------server_reply START-------------
  HTTP/1.1 200 OK\n
  Connection: Keep-Alive
  Keep-Alive: timeout=5, max=100
  content-type: text/plain
  last-modified: Fri, 13 May 2022 17:02:10 GMT
  etag: "41-627e8f12-2db9be8dd9eec45d;;;"
  accept-ranges: bytes
  content-length: 65
  date: Fri, 13 May 2022 17:20:00 GMT
  x-powered-by: PleskLin
  alt-svc: h3=":443"; ma=2592000, h3-29=":443"; ma=2592000, h3-Q050=":443"; ma=2592000, h3-Q046=":443"; ma=2592000, h3-Q043=":443"; ma=2592000, quic=":443"; ma=2592000; v="43,46"\n
  \r
  2E51197EBC54E73D6C1C9E43AF06556B3BAF140B0CFCCFF9E92BC1114B4310A1\n

  --------------server_reply END-------------
*/
int checkForNewFirmware()
{
  // Connect to external web server
  WiFi_client.setCACert(fw_strantech_root_ca);
  if (WiFi_client.connect(fwserver,443))
  {
    String client_request = (String("GET /esp32/")+macStr+"/sha256.txt HTTP/1.1\r\n" +
                    "Host: " + fwserver + "\r\n" +
                    "Content-Type: text/plain\r\n" +
                    "User-Agent: esp32/2022-05-12 webota-esp32\r\n\r\n");
    WiFi_client.print(client_request);

    #if defined USE_SERIAL && DEBUG>=2
    Serial.print("--------------client_request START-------------\n[");
    Serial.print(client_request);
    Serial.print("]\n--------------client_request END-------------\n");
    #endif

  } 
  else
  {
    #ifdef USE_SERIAL
    Serial.print("ERROR: connecting to server ");
    Serial.println(fwserver);
    #endif
    return -1;
  }

  // read header line by line.  end of header is \r
  // date: Sat, 14 May 2022 16:40:08 GMT\n
  // content-length: 1475\n
  while (WiFi_client.connected()) {
    String line = WiFi_client.readStringUntil('\n');
    if (line == "\r")
      break;
  }

  // get the rest of the transmission (payload?, body?)
  int i=0;
  while (WiFi_client.available() && (i<sizeof(server_reply)-1)) {
    char c = WiFi_client.read();
    server_reply[i++]=c;
  }
  server_reply[i]=0; // null terminate the string
  #if defined USE_SERIAL && DEBUG>=2
  Serial.print("reply length= ");
  Serial.println(strlen(server_reply));
  Serial.print("--------------server_reply START-------------\n[");
  Serial.print(server_reply);
  Serial.print("]\n--------------server_reply END-------------\n");
  #endif
  // SHA256 should only be 64 characters long so truncate at index 64 (0-63 is the SHA256 string)
  server_reply[64] = 0;
  if(!check_fw_from_server(server_reply))
  {
    // different firmware on server.  Consider updating
    Serial.println("firmware update required");
    fwUpdateFromServer();
  }

  if (WiFi_client.connected())
  { 
    WiFi_client.stop();  // DISCONNECT FROM THE SERVER
    #if defined USE_SERIAL && DEBUG>=2
    Serial.println("\nDisconnected from server");
    #endif
  }
  return 0;
}

int fwUpdateFromServer()
{
  // connect to the server
  if(!WiFi_client.connected())
  {
    WiFi_client.setCACert(fw_strantech_root_ca);
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
    fwDownloadDone = false;
    String client_request = (String("GET /esp32/")+macStr+"/firmware.bin HTTP/1.1\r\n" +
                    "Host: " + fwserver + "\r\n" +
                    "Content-Type: application/octet-stream\r\n" +
                    "User-Agent: esp32/2022-05-12 webota-esp32\r\n\r\n");// +
    WiFi_client.print(client_request);

    #if defined USE_SERIAL && DEBUG>=2
    Serial.print("--------------client_request START-------------\n[");
    Serial.print(client_request);
    Serial.print("]\n--------------client_request END-------------\n");
    #endif
  }

  // read header line by line.  end of header is \r
  // date: Sat, 14 May 2022 16:40:08 GMT\n
  // content-length: 1475\n
  totalLength = 0;
  bool firmware_available = false;

  while (WiFi_client.connected()) {
    String line = WiFi_client.readStringUntil('\n');
    if (line == "\r") {
      Serial.println("headers received");
      break;
    }
    else
    {
      #if defined USE_SERIAL && DEBUG>=2
      Serial.print("line: ");
      Serial.println(line);
      #endif
      // need to parse the line looking for content-length to set totalLength for firmware update
      if(line.indexOf("content-length")>=0)
      {
        String content_str = line.substring(line.indexOf(" "));
        totalLength = content_str.toInt();
      }
      if(line.indexOf("404 Not Found")>=0)
      {
        firmware_available = false;
        Serial.println("no firmware.bin file found on server");
      }
      if(line.indexOf("200 OK")>=0)
      {
        firmware_available = true;
        Serial.println("firmware.bin found on server");
      }

    }
  }
  if(firmware_available)
  {
    #ifdef USE_SERIAL
    Serial.print("\n############\ntotalLength = ");
    Serial.println(totalLength);
    Serial.println();
    #endif

    #if DEBUG==0
    Update.begin(totalLength);
    #endif
    uint8_t buf[128] = { 0 };
    int total_bytes=0;
    int num_bytes_in=0;
    while (WiFi_client.connected() && !fwDownloadDone) //WiFi_client.available()) {
    {
      num_bytes_in = WiFi_client.read(buf,sizeof(buf));

      if(num_bytes_in>0) 
      {
        //Serial.print("bytes read: ");
        //Serial.print(num_bytes_in);
        updateFirmware(buf,num_bytes_in);
      }
      //else
        //Serial.print("0");
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
  //Serial.println("hexdump:");
  // while debugging, we're just using text so let's just print it as-is
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
// Buffer is declared to be 128 so chunks of 128 bytes
// from firmware is written to device until server closes
void updateFirmware(uint8_t *data, size_t len){

  #if DEBUG>=2
  hexdump(data,len);
  #elif DEBUG==0
  Update.write(data, len);
  // Print dots as a status update while waiting for update to finish
  #endif
  Serial.print(".");
  currentLength += len;
  // if current length of written firmware is not equal to total firmware size, repeat
  if(currentLength < totalLength) return;
  //Update.end(true);
  Serial.printf("\nUpdate Success, Total Size: %u\nRebooting...\n", currentLength);
  Update.end();
  // Restart ESP32 to see changes
  #if DEBUG>0
  currentLength = 0;
  fwDownloadDone = true;
  #else
  ESP.restart();
  #endif
}

void hex_2_string(uint8_t *sha256, char *sha256str)
{
  for(int i=0;i<32;i++)
  {
    char hexChars[3];
    sprintf(hexChars,"%02X", sha256[i]);
    strcat(sha256str,hexChars);
    //if((i+1)%2==0) strcat(sha256str," ");
  }
}

esp_err_t running_sha256(uint8_t *sha256)
{
  const esp_partition_t *running_partition;
  running_partition = esp_ota_get_running_partition();
  esp_err_t err = esp_partition_get_sha256(running_partition, sha256);
  return err;
}

bool check_fw_from_server(char *sha256fromServer)
{
  uint8_t run_sha256[32] = {0};
  char sha256str[128];
  memset(sha256str,0,sizeof(sha256str));
  const esp_partition_t *running_partition;
  bool fw_match = true;
  running_partition = esp_ota_get_running_partition();
  esp_err_t err = esp_partition_get_sha256(running_partition, run_sha256);
  if(err==ESP_OK)
  {
    hex_2_string(run_sha256,sha256str);
    // compare SHA256 sums
    for(int i=0;i<sizeof(run_sha256)*2;i++)
      fw_match &= (sha256fromServer[i]==sha256str[i]);
    if(err!=ESP_OK) fw_match = false;
    #ifdef USE_SERIAL
    Serial.printf("running_partition: %s\n",  running_partition->label);
    Serial.print(sha256str);
    Serial.println(" running firmware SHA256");
    if(strcmp(sha256fromServer,"none")!=0)
    {
      Serial.print(sha256fromServer);
      Serial.println(" server SHA does not match");
    }
    #endif
  }
  else strcpy(sha256str,"Error reading parition SHA256");

  return fw_match;
}

