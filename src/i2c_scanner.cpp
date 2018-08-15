#include <Wire.h>
#include <Arduino.h>

#include "i2c_scanner.h"
		  
void i2c_begin() {
  Wire.begin();
}

byte i2c_try_address(byte address) {
  Wire.beginTransmission(address);
  return Wire.endTransmission();
}

void i2c_identify(byte);

void i2c_scan() {
  byte error, address;
  int nDevices;
 
  Serial.println("Scanning...");
 
  nDevices = 0;
  for(address = 1; address < 127; address++ )  {
    error = i2c_try_address(address);
    if(error == 0) {
      Serial.printf("I2C device found at address 0x%0x\n", address);
      i2c_identify(address);
      nDevices++;
    } else if(error==4) {
      Serial.printf("Unknown error at address 0x%0x\n", address);
    }
  }

  if(nDevices == 0)
    Serial.println("No I2C devices found\n");
  else
    Serial.println("done\n");
}


void i2c_identify(byte address) {
  for(int i = 0; i < i2c_scanner_known_devices_length; i++) {
#if 0
    Serial.printf("  checking %d %s has %d addresses\n", i, i2c_scanner_known_devices[i].name, strlen((char *)i2c_scanner_known_devices[i].addrs));
    Serial.printf("  want to match %02x\n", (int)address);
#endif

    int j = 0;
    while(1) {
#if 0
      Serial.printf("     checking char index %d is %02x\n", j, (int)i2c_scanner_known_devices[i].addrs[j]);
#endif

      if(i2c_scanner_known_devices[i].addrs[j] == '\0')
	break;

      if(i2c_scanner_known_devices[i].addrs[j] == address) {
	Serial.printf("    at 0x%0x might be %s (%s)\n", address, i2c_scanner_known_devices[i].name, i2c_scanner_known_devices[i].function);
	break;
      }

      j++;
    }
  }
}
