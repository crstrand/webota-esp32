#ifndef CERT_H
#define CERT_H

const char* ssid     = "ssid";      // your network SSID (name of wifi network)
const char* password = "password";  // your network password
const char* fwserver = "serverURL"; // Server URL

const char* root_ca= \
"-----BEGIN CERTIFICATE-----\n" \
"<web site root ca certificate in text form>" \
"TzELMAkGA1UEBhMCVVMxKTAnBgNVBAoTIEludGVybmV0IFNlY3VyaXR5IFJlc2Vh\n" \
"<lots of lines here>" \
"-----END CERTIFICATE-----\n";

#endif