#ifdef ESP32

#include <Arduino.h>
#include <Esp.h>

void esp_output() {
  Serial.println();

  Serial.print("ESP-IDF version "); Serial.println(esp_get_idf_version());
  Serial.print("Arduino Core version "); Serial.print(ESP_ARDUINO_VERSION_MAJOR); Serial.print("."); Serial.print(ESP_ARDUINO_VERSION_MINOR); Serial.print("."); Serial.println(ESP_ARDUINO_VERSION_PATCH);
  Serial.print("Flash Chip Speed "); Serial.println(ESP.getFlashChipSpeed());
  Serial.print("Model "); Serial.print(ESP.getChipModel()); Serial.print(" revision "); Serial.println(ESP.getChipRevision());
  Serial.print("Cores "); Serial.println(ESP.getChipCores());
  Serial.print("PSRAM "); Serial.println(ESP.getPsramSize());

  uint64_t mac_addr = ESP.getEfuseMac();
  Serial.print("WIFI MAC address ");
  Serial.print(mac_addr & 0xFF, HEX); Serial.print(":");
  Serial.print((mac_addr >> 8) & 0xFF, HEX); Serial.print(":");
  Serial.print((mac_addr >> 16) & 0xFF, HEX); Serial.print(":");
  Serial.print((mac_addr >> 24) & 0xFF, HEX); Serial.print(":");
  Serial.print((mac_addr >> 32) & 0xFF, HEX); Serial.print(":");
  Serial.println((mac_addr >> 40) & 0xFF, HEX);

  Serial.println();
  Serial.println();
}

#endif
