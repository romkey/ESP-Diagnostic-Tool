#pragma once

#include <Arduino.h>

/* i2c_device struct consists of a pointer to a name, a pointer
 * to a char* describing the function of the device, and a null
 * terminated byte array of addresses that the device responds to.
 */
typedef struct i2c_device {
  const char* name;
  const char* function;
  const byte *addrs;
} i2c_device_t;

extern i2c_device_t i2c_scanner_known_devices[];
extern int i2c_scanner_known_devices_length;
