# ESP8266 Debug Utility

This is a small set of diagnostics and debugging tools for the ESP8266. It's meant to help solve problems around Wifi and I2C.

The utility includes Wifi and I2C scanners and can report basic information about the board you're using.

Running it you'll be presented with a menu:
```
Hello World
1. Show ESP information
2. Enter wifi credentials
3. Connect to wifi network
4. Current wifi info
5. Scan wifi networks
6. Scan I2C devices
0. Restart
```

##1 Show ESP Infiormation

##2 Enter Wifi credentials

You'll enter an SSID and password, each up to 64 characters, ending with the RETURN key. You can use backspace or delete to go back a character.

The SSID and password are not stored in flash and should not persist across reboots.

## I2C Scanner

The I2C scanner probes each I2C address and reports which addresses respond.

It also contains a list of known I2C devices by address and will report the known uses of each responding address.

Currently this list is woefully incomplete.

## SPI Scanner

There is no SPI scanner. SPI devices are individually selected - SPI doesn't have addresses. Which leaves us no way to scan for SPI devices. So, no SPI scanner; sorry.


## ESP32 Support

