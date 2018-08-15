# ESP8266 Diagnostic Utility

This is a small set of diagnostics and debugging tools for the ESP8266. It's meant to help solve problems around Wifi and I2C.

The utility includes Wifi and I2C scanners and can report basic information about the board you're using.


## Usage:

The utility runs the serial port at 115,200 bps. You'll want to use some kind of terminal program to interact with it.

The utility will display a menu when it starts:
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

### 1 Show ESP Infiormation

This shows information about the ESP SDK and Arduino core that the utility was built with as well as information about the CPU it's running on.

```
SDK version 2.2.1(cfd48f3)
Arduino Core version 2_4_1
VCC 3013
Chip ID 283132
Flash Chip ID 1458208
Flash Chip Speed 40000000
Sketch Size 276032
Free heap 43496
Free sketch space 2867200
Reset reason External System
```

### 2 Enter Wifi credentials

You'll enter an SSID and password, each up to 64 characters, ending with the RETURN key. You can use backspace or delete to go back a character.

The SSID and password are not stored in flash and should not persist across reboots.

### 3 Connect to wifi network

This item will attempt to connect the ESP to a wifi network or will disconnect from the current network. You must enter wifi credentials before you can connect.

As it attempts to connect you should see wifi-related events.

A connection attempt using a non-existent SSID should look like:

```
Connecting...............[wifi] 1, Disconnected - Status 6, Disconnected
............................................................................................................
```

at this time you'll need to reset the CPU to get out of it. 

A connection attempt with an invalid passwords hould look like:
```
Connecting........[wifi] 2, AuthMode Change
............................[wifi] 1, Disconnected - Status 6, Disconnected
............................................................................
```

at this time you'll need to reset the CPU to get out of it. 

A successful connection attempt should look like:

```
Connecting....[wifi] 2, AuthMode Change
............[wifi] 0, Connected
.........[wifi] 3, Got IP

WiFi connected
```




### 4 Current wifi info

When connect to a wifi network, this will show how the ESP was configured by DHCP and the RSSI for the wifi network. It will always show you the ESP's MAC address.

```
Connected
Hostname ESP_0223FC
MAC address 38:2B:78:02:23:FC
IP address 10.0.1.206
Subnet mask 255.255.255.0
router IP 10.0.1.1
first DNS server 10.0.1.1
SSID YOUR WIFI NETWORK
RSSi -51
```


### 5 Scan wifi networks

This will show you a list of wifi networks that the ESP can currently see. The list may seem very random. Only nearby access points will show up reliably.

Remember that current ESPs are 2.4GHz devices. They support 802.11b/g/n but only the 2.4GHz band for n. They will never be able to see 5GHz 802.11a, 802.11n or 802.11ac networks.

Scan network output will look like this:
```
About to scan wifi networks

Wifi scan done
10 networks found
                            SSID CHN RSS        MAC address Encryption
                       HOME-2001   1 -84  E8:3E:FC:23:23:23 WPA/WPA2/PSK
    you better know your dumplng   1 -58  44:D9:E7:23:23:23 CCMP
                 CenturyLink2061   1 -92  58:8B:F3:23:23:23 WPA/WPA2/PSK
                       NETGEAR69   3 -35  9C:3D:CF:23:23:23 CCMP
  HP-Print-28-Officejet Pro 8600   4 -87  A0:D3:C1:23:23:23 none
              extra cashew sauce   4 -66  8C:3B:AD:23:23:23 CCMP
      tell me about the dumpling   5 -53  80:2A:A8:23:23:23 CCMP
                     xfinitywifi   6 -93  F6:AA:A0:23:23:23 none
                  BAKINGINDAKITC   6 -92  EC:AA:A0:23:23:23 CCMP
           Internet of Dumplings  11 -52  88:1F:A1:23:23:23 WPA/WPA2/PSK
```

The MAC address is the MAC address of the access point.

Encryption will be [WEP](https://en.wikipedia.org/wiki/Wired_Equivalent_Privacy), [TKIP](https://en.wikipedia.org/wiki/Temporal_Key_Integrity_Protocol), [CCMP](https://en.wikipedia.org/wiki/CCMP_(cryptography)), [WPA/WPA2/PSK](https://en.wikipedia.org/wiki/Wi-Fi_Protected_Access) or none.

### 6 I2C Scanner

The I2C scanner probes each I2C address and reports which addresses respond.

It also contains a list of known I2C devices by address and will report the known uses of each responding address.

The list needs a lot of work and should eventually be stored in flash and not in the heap.

An I2C scan with no I2C device should look like this:
```
Scanning...
No I2C devices found
```

A successful I2C scan might look like this:
```
Scanning...
I2C device found at address 0x18
    at 0x18 might be LIS3DH (3-axis accelerometer)
    at 0x18 might be LSM303 (Triple-axis Accelerometer+Magnetometer (Compass))
    at 0x18 might be MCP9808 (temp sensor)
I2C device found at address 0x39
    at 0x39 might be APDS-9960 (IR/Color/Proximity Sensor)
    at 0x39 might be TSL2561 (light sensor)
    at 0x39 might be VEML6070 (UV Index)
I2C device found at address 0x53
    at 0x53 might be ADXL345 (3-axis accelerometer)
    at 0x53 might be MB85RC (Ferroelectric RAM)
    at 0x53 might be PCA9685 (16-channel PWM driver default address)
I2C device found at address 0x5b
    at 0x5b might be CCS811 (VOC sensor)
    at 0x5b might be MPR121 (12-point capacitive touch sensor)
    at 0x5b might be PCA9685 (16-channel PWM driver default address)
I2C device found at address 0x76
    at 0x76 might be BME280 (Temp/Barometric/Humidity)
    at 0x76 might be BMP280 (Temp/Barometric)
    at 0x76 might be HT16K33 (LED Matrix Driver)
    at 0x76 might be MS5607/MS5611 (Barometric Pressure)
    at 0x76 might be PCA9685 (16-channel PWM driver default address)
    at 0x76 might be TCA9548 (1-to-8 I2C Multiplexer)
done
```

An I2C scan with malfunctioning hardware might look like this:
```
Scanning...  
Unknown error at address 0x01
Unknown error at address 0x02
Unknown error at address 0x03 
Unknown error at address 0x04
...
```

This means something is interfering with signalling on the I2C SDA and SDC lines. It's most likely an electrical or wiring problem but could possibly be a defective I2C device.

The device list is generated by the web site https://i2cdevices.org/devices

#### SPI Scanner

There is no SPI scanner. SPI devices are individually selected - SPI doesn't have addresses. Which leaves us no way to scan for SPI devices. So, no SPI scanner; sorry.

### 0 Restart

Resets the ESP. It should very quickly restart and present the menu again.

### H, ? and Newline

These will all re-display the menu.

## Building and Installation

You currently have to build the firmware yourself using [PlatformIO](https://platformio.org/). You can find installation instructions for it [on its site](https://platformio.org/get-started).

1. Clone the repository
```
git clone git@github.com:romkey/ESP-Diagnostic-Tool.git
```
2. If the board you want to run on isn't currently in `platformio.ini`, add it.

3. Build it and upload it:
```
platformio run -e YOUR_BOARD_ID -t upload
```

Replace `YOUR_BOARD_ID` with the id for your board - for instance, Wemos D1 mini is listed in the shipping `platformio.ini` as `d1_mini`.

4. Run the serial monitor to interact with the utility.
```
platformio device monitor
```

If you missed the menu try typing `?` or `h` to see it.

## ESP32 Support

The utility has very limited ESP32 support. It can't currently report Wifi events and can't give much information about the board.

Bluetooth support looks problematic. The [Bluetooth library is so large](https://github.com/espressif/arduino-esp32/issues/1075) that it makes the firmware too big to load using the default flash partitioning scheme. You can work around this by [changing partitioning](https://desire.giesecke.tk/index.php/2018/01/30/change-partition-size/) but this is non-trivial.

## Roadmap

1. Add more I2C devices

2. Build under Arduino IDE

3. Add timeout to Wifi connect attempt

4. Support AP and STA_AP wifi modes

5. mDNS publish and resolve

6. Move I2C device names list to Flash storage.

7. Improve ESP32 support

8. ESP32 Bluetooth scanning? (not likely due to Bluetooth library size issues)

## License

This code is published under the [MIT License](https://romkey.mit-license.org/).
