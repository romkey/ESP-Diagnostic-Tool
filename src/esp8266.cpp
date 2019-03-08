#ifdef ESP8266

#include <Arduino.h>
#include <Esp.h>

extern "C" {
#include <lwipopts.h>
};

#ifndef ESP32

void esp_output() {
  Serial.println();

  Serial.printf("SDK version %s\n", ESP.getSdkVersion());
#ifndef ESP32
  Serial.printf("Arduino Core version %s\n", ESP.getCoreVersion().c_str());
  Serial.printf("VCC %d\n", ESP.getVcc());
  Serial.printf("Chip ID %d\n", ESP.getChipId());
  Serial.printf("Flash Chip ID %d\n", ESP.getFlashChipId());
#endif
  Serial.printf("Flash Chip Speed %d\n", ESP.getFlashChipSpeed());
#ifndef ESP32
  Serial.printf("Sketch Size %d\n", ESP.getSketchSize());
  Serial.printf("Free heap %d\n", ESP.getFreeHeap());
  Serial.printf("Free sketch space %d\n", ESP.getFreeSketchSpace());
  Serial.printf("Reset reason %s\n", ESP.getResetReason().c_str());
#endif

  Serial.printf("Maximum TCP connections %d\n", MEMP_NUM_TCP_PCB);

  Serial.println();
  Serial.println();
}

#endif

#endif
