#include <Arduino.h>

#ifdef ESP32
#include <WiFi.h>
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

#ifndef ESP32

const char* connectionStatus(int);

void eventWiFi(WiFiEvent_t event) {
  switch(event) {
  case WIFI_EVENT_STAMODE_CONNECTED:
    Serial.printf("[wifi] %d, Connected\n", event);
    break;
   
  case WIFI_EVENT_STAMODE_DISCONNECTED:
    Serial.printf("[wifi] %d, Disconnected - Status %d, %s\n", event, WiFi.status(), connectionStatus(WiFi.status()));
    break;
   
  case WIFI_EVENT_STAMODE_AUTHMODE_CHANGE:
    Serial.printf("[wifi] %d, AuthMode Change\n", event);
    break;
   
  case WIFI_EVENT_STAMODE_GOT_IP:
    Serial.printf("[wifi] %d, Got IP\n", event);
    break;
   
  case WIFI_EVENT_STAMODE_DHCP_TIMEOUT:
    Serial.printf("[wifi] %d, DHCP Timeout\n", event);
    break;
   
  case WIFI_EVENT_SOFTAPMODE_STACONNECTED:
    Serial.printf("[ap] %d, Client Connected\n", event);
    break;
   
  case WIFI_EVENT_SOFTAPMODE_STADISCONNECTED:
    Serial.printf("[ap] %d, Client Disconnected\n", event);
    break;
   
  case WIFI_EVENT_SOFTAPMODE_PROBEREQRECVED:
    Serial.printf("[ap] %d, Probe Request Recieved\n", event);
    break;
   
  default:
    Serial.printf("[GENERIC EVENT] %d\n", event);
  }
}

const char* connectionStatus(int status) {
  switch(status) {
  case WL_CONNECTED:
    return "Connected";

  case WL_NO_SSID_AVAIL:
    return "Network not availible";

  case WL_CONNECT_FAILED:
    return "Wrong password";

  case WL_IDLE_STATUS:
    return "Idle status";

  case WL_DISCONNECTED:
    return "Disconnected";
      
  default:
    return "Unknown";
  }
}
#endif

void wifi_begin() {
  WiFi.setAutoConnect ( false );                                             // Autoconnect to last known Wifi on startup
  WiFi.setAutoReconnect ( false );                                             

#ifndef ESP32
  WiFi.onEvent(eventWiFi);                                                    // Handle WiFi event
#endif

  WiFi.mode(WIFI_STA);                                                        // Station mode
}

void wifi_connect(const char* ssid, const char* password) {
  WiFi.begin(ssid, password);

  Serial.println();
  Serial.println();
  Serial.print("Connecting");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(200);
  }

  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    Serial.println();
    Serial.println("Fail connecting");
  }
 
  Serial.println("");
  Serial.println("WiFi connected");
}

void wifi_disconnect() {
  WiFi.disconnect();
}

bool wifi_connected() {
  return WiFi.status() == WL_CONNECTED;
}

void wifi_info() {
  if(WiFi.status() == WL_CONNECTED)
    Serial.println("Connected");
  else
    Serial.println("Not connected");

#ifndef ESP32
  Serial.println(String("Hostname ") + WiFi.hostname());
#endif
  Serial.println(String("MAC address ") + WiFi.macAddress());

  if(WiFi.status() == WL_CONNECTED) {
    Serial.println(String("IP address ") + WiFi.localIP().toString());
    Serial.println(String("Subnet mask ") + WiFi.subnetMask().toString());
    Serial.println(String("router IP ") + WiFi.gatewayIP().toString());
    Serial.println(String("first DNS server ") + WiFi.dnsIP(0).toString());
    Serial.println(String("SSID ") + WiFi.SSID());
    Serial.println(String("RSSi ") + WiFi.RSSI());
  }
}
