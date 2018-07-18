#include <Arduino.h>
#include <ESP.h>

#ifdef ESP32

void output_esp_info() {
  Serial.println();

  Serial.printf("SDK version %s\n", ESP.getSdkVersion());
  Serial.printf("Flash Chip Speed %d\n", ESP.getFlashChipSpeed());

  Serial.println();
  Serial.println();
}

#endif
