#include <Arduino.h>

#include "menu.h"

Menu::Menu(int max_items) {
  _items = (struct _menu_item *)malloc(sizeof(struct _menu_item) * max_items);
}

void Menu::add_item(char command, char *text, void (*callback)()) {
  
}

void Menu::run() {
  if(Serial.available() == 0)
    return;

  char command = Serial.read();
  for(int i = 0; i < _current_items; i++)
    if(_items[i]._command == command) {
      _items[i]._callback();
      return;
    }
}
