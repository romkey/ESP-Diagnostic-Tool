#include <Arduino.h>

#define MAX_WIFI_SSID_LENGTH 64
#define MAX_WIFI_PASSWORD_LENGTH 64

static char wifi_ssid[MAX_WIFI_SSID_LENGTH+1]         = "";
static char wifi_password[MAX_WIFI_PASSWORD_LENGTH+1] = "";

#ifdef ADC_MODE
ADC_MODE(ADC_VCC);
#endif

void i2c_begin(), i2c_scan(), blink_start(int), wifi_begin(), wifi_scan(), wifi_info(), esp_output(), wifi_disconnect(), wifi_connect(const char*, const char*);
bool wifi_connected();

void output_menu() {
  Serial.println("1. Show ESP information");

  Serial.println("2. Enter wifi credentials");

  if(wifi_connected())
    Serial.printf("3. Disconnect from wifi network %s\n", wifi_ssid);
  else
    Serial.printf("3. Connect to wifi network %s\n", strlen(wifi_ssid) > 0 ? wifi_ssid : "(enter SSID to be able to connect)");
    
  Serial.println("4. Current wifi info");
  Serial.println("5. Scan wifi networks");
  Serial.println("6. Scan I2C devices");
  Serial.println("0. Restart");
}


void setup(){
  wifi_begin();
  i2c_begin();

  Serial.begin(115200);
  Serial.println();
  Serial.println();
  Serial.println("Hello World");

  output_menu();
}

void input_wifi_credentials();

void loop() {
  if (Serial.available() > 0) {
    char cmd[2];

    Serial.readBytes(cmd, 1);
    
    switch(cmd[0]) {
    case '1':
      esp_output();
      break;

    case '2':
      input_wifi_credentials();
      break;

    case '3':
      if(wifi_connected())
	wifi_disconnect();
      else {
	if(strlen(wifi_ssid) > 0)
	  wifi_connect(wifi_ssid, wifi_password);
	else
	  Serial.println("You must enter a Wifi SSID first");
      }

      break;

    case '4':
      if(strlen(wifi_ssid) > 0) {
	Serial.printf("Entered SSID: %s\n", wifi_ssid);
	Serial.printf("Entered password: %s\n", wifi_password);
      } else {
	Serial.println("No SSID entered");
      }

      Serial.println();

      wifi_info();

      Serial.println();
      Serial.println();
      break;

    case '5':
      wifi_scan();
      break;

    case '6':
      i2c_scan();
      break;

    case '0':
      Serial.println("RESTART ESP");
      ESP.restart();
      break;

    case 'h':
    case '?':
    case '\n':
      output_menu();
      break;

    default:
      Serial.printf("Unknown command '%c'\n", cmd[0]);
    }
  }
}

/* basic line reading function which handles backspace and delete
 * can't believe I had to write this; I must be missing something...
 */
int serial_read_line(char* buf, int length) {
  int n = 0;

  while(1) {
    if(Serial.available() == 0) {
      yield();
      continue;
    }

    char c = Serial.read();

    //    Serial.printf("%d", (int)c);

    if(c == -1 || c == '\n') {
      yield();
      continue;
    }

    if(c == '\b' || c == 0x7f) {
      n--;
      buf[n] = '\0';
      Serial.print('\b');
      continue;
    }

    if(n == length) {
      Serial.print("\07");
      continue;
    }
    
    if(c == '\r') {
      Serial.println();
      return n;
    }

    Serial.print(c);

    buf[n++] = c;
    buf[n] = '\0';
  }
}


void input_wifi_credentials() {
  Serial.println("Enter wifi SSID");

  serial_read_line(wifi_ssid, MAX_WIFI_SSID_LENGTH);

  Serial.println("Enter wifi password");

  serial_read_line(wifi_password, MAX_WIFI_PASSWORD_LENGTH);

  Serial.println();
  Serial.println();

  Serial.printf("SSID %s\n", wifi_ssid);
  Serial.printf("Password %s\n", wifi_password);

  Serial.println();
  Serial.println();
}
