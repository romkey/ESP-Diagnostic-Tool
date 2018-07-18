#include <Arduino.h>

void blink_start(int pin) {
  pinMode(pin, OUTPUT);

  int current = LOW;

  while(1) {
      digitalWrite(pin, current);
      if(current == LOW)
	current = HIGH;
      else
	current = LOW;

      if(Serial.read() != -1)
	return;

      delay(500);
    }
}

