#pragma once

class Menu {
 public:
  Menu(int);
  void add_item(char command, char *text, void (*callback)());
  void run();
  void show();
 private:
  int _max_items;
  int _current_items = 0;

  struct _menu_item {
    char _command;
    char *_menu_text;
    void (*_callback)();
  } *_items;
};
