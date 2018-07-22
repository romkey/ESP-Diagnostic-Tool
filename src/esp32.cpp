#include <Arduino.h>
#include <ESP.h>

#ifdef ESP32

#include "soc/efuse_reg.h"

#if 0
static int cpu_vevision() {
  return REG_READ(EFUSE_BLK0_RDATA3_REG) >> (EFUSE_RD_CHIP_VER_RESERVE_S) && EFUSE_RD_CHIP_VER_RESERVE_V;
}
#endif

void esp_output() {
  Serial.println();

  Serial.printf("SDK version %s\n", ESP.getSdkVersion());
  Serial.printf("Flash Chip Speed %d\n", ESP.getFlashChipSpeed());

#if 0
  Serial.println("CPU version %d\n", cpu_version());
#endif

  Serial.println();
  Serial.println();
}

#endif
