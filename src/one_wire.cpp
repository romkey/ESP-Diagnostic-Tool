#if 0

#include <Arduino.h>

#include <OneWire.h>

#include "one_wire.h"


void one_wire_scan(uint8_t pin) {
  OneWire oneWire(pin);
  byte i;
  byte addr[8];

  for(int scan_count = 0; scan_count < 10; scan_count++) {
    if(!oneWire.search(addr)) {
      Serial.println(" No more addresses.");
      Serial.println();
      oneWire.reset_search();
      delay(250);
      continue;
    }
    Serial.print(" ROM =");
    for(i = 0; i < 8; i++) {
      Serial.write(' ');
      Serial.print(addr[i], HEX);
    }  
  }
}

#endif
