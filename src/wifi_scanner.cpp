#ifdef ESP32
#include <WiFi.h>
#endif

#ifdef ESP8266
#include <ESP8266WiFi.h>
#endif

static const char* wifi_enc_type(int code) {
#ifdef ESP32
  static char buf[6];
  snprintf(buf, 6, "%d", code);
  return buf;
#else

  switch(code) {
  case ENC_TYPE_WEP:
    return "WEP";
  case ENC_TYPE_TKIP:
    return "TKIP";
  case ENC_TYPE_CCMP:
    return "CCMP";
  case ENC_TYPE_NONE:
    return "none";
  case ENC_TYPE_AUTO:
    return "WPA/WPA2/PSK";
  default:
    return "unknown";
  }
#endif
}


void wifi_scan() {
  WiFi.disconnect();

  Serial.println("About to scan wifi networks");

  int n = WiFi.scanNetworks();

  Serial.println();
  Serial.println("Wifi scan done");
  if(n == 0) {
    Serial.println("no networks found");
  } else {
    Serial.printf("%d networks found\n", n);
    Serial.printf("%32s %3s %3s %18s %s\n", "SSID", "CHN", "RSS", "MAC address", "Encryption");
    for (int i = 0; i < n; ++i) {
      Serial.printf("%32s %3d %3d %18s %s\n",
		    WiFi.SSID(i).c_str(),
		    WiFi.channel(i),
		    WiFi.RSSI(i),
		    WiFi.BSSIDstr(i).c_str(),
		    wifi_enc_type(WiFi.encryptionType(i)));
    }

    Serial.println();
  }
}

