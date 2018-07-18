#include <Wire.h>
#include <Arduino.h>

static struct i2c_device {
  byte addr1;
  byte addr2;
  byte addr3;
  byte addr4;
  const char* name;
  const char* function;
} known_addresses[] = {
  { 0x0e, 0x00, 0x00, 0x00, "MAG3110", "3-axis magnetometer" },

  { 0x11, 0x63, 0x00, 0x00, "Si4713", "FM transmitter" },
  { 0x13, 0x00, 0x00, 0x00, "VCNL40x0", "Proximity/ambient light sensor" },
  { 0x18, 0x19, 0x1a, 0x1b, "MCP9808", "Temperature sensor" },
  { 0x1c, 0x1d, 0x1e, 0x1f, "MCP9808", "Temperature sensor" },
  { 0x18, 0x19, 0x00, 0x00, "LIS3DH", "Low power 3-axis accelerometer" },
  { 0x18, 0x19, 0x00, 0x00, "LSM303", "3-axis accelerometer/magnetometer" },
  { 0x1c, 0x1d, 0x00, 0x00, "MMA845x", "accelerometer" },
  { 0x1c, 0x1d, 0x1e, 0x1f, "FXOS8700", "3-Axis accelerometer" },
  { 0x1c, 0x1d, 0x00, 0x00, "MMA7455L", "3-axis accelerometer" },
  { 0x1d, 0x1e, 0x6a, 0x6b, "LSM9DS0", "3D accelerometer/gyroscope/magnetometer" },
  { 0x1d, 0x53, 0x00, 0x00, "ADXL345", "3-axis accelerometer" },
  { 0x1e, 0x00, 0x00, 0x00, "HMC5883", "3-Axis Magnetometer" },

  { 0x20, 0x21, 0x00, 0x00, "FXAS21002", "3-axis gyroscope" },
  { 0x20, 0x00, 0x00, 0x00, "Chirp! Water Sensor", "Water sensor" },
  { 0x20, 0x21, 0x22, 0x23, "MCP23008", "8 pin I/O expander" },
  { 0x24, 0x25, 0x26, 0x27, "MCP23008", "8 pin I/O expander" },
  { 0x20, 0x21, 0x22, 0x23, "MCP23017", "16 pin I/O expander" },
  { 0x24, 0x25, 0x26, 0x27, "MCP23017", "16 pin I/O expander" },
  { 0x28, 0x29, 0x00, 0x00, "BNO055", "9-axis orientation sensor" },
  { 0x28, 0x29, 0x2a, 0x2b, "CAP1188", "Capacitive touch sensor" },
  { 0x2c, 0x2d, 0x00, 0x00, "CAP1188", "Capacitive touch sensor" },
  { 0x29, 0x00, 0x00, 0x00, "TCS34725", "RGB color sensor" },
  { 0x29, 0x39, 0x49, 0x00, "TSL2561", "Luminosity sensor" },
  { 0x29, 0x00, 0x00, 0x00, "TSL2591", "Luminosity sensor" },
  { 0x29, 0x00, 0x00, 0x00, "VL53L0x", "Time-of-Flight distance sensor" },
  { 0x29, 0x00, 0x00, 0x00, "VL6180x", "Proximity/gesture/ambient light sensor" },

  { 0x38, 0x39, 0x00, 0x00, "VEML6070", "UV Sensor" },
  { 0x38, 0x00, 0x00, 0x00, "FT6x06", "Capacitive touch panel controller" },
  { 0x39, 0x00, 0x00, 0x00, "APDS9960", "Proximity/Light/RGB sensor" },
  { 0x3c, 0x3d, 0x00, 0x00, "SSD1305", "OLED/PLED driver" },
  { 0x3c, 0x3d, 0x00, 0x00, "SSD1306", "OLED/PLED driver" }
};
		  
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
  for(unsigned i = 0; i < sizeof(known_addresses)/sizeof(struct i2c_device); i++) {
    struct i2c_device *k = &known_addresses[i];
    if(k->addr1 == address || k->addr2 == address || k->addr3 == address || k->addr4 == address)
      Serial.printf("at 0x%0x found %s (%s)\n", address, k->name, k->function);
  }
}
