#pragma once

class I2CScanner {
 public:
  void begin();
  void scan();
  void identify(char **buf, int n, byte address);
};
