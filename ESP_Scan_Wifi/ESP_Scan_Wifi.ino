
#include "ESP8266WiFi.h"

//WiFi
//https://www.arduino.cc/en/Reference/WiFi
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html  

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.disconnect();
  delay(100);
}

void loop() {
  Serial.println("scan start");

  // WiFi.scanNetworks will return the number of networks found
  int n = WiFi.scanNetworks();
  Serial.println("scan done");
  if (n == 0) {
    Serial.println("no networks found");
  }
  else {
    Serial.print(n); // no of wifi access points
    Serial.println(" networks found");
    for (int i = 0; i < n; ++i) {
      Serial.print(i + 1);
      Serial.print(" | SSID: ");
      Serial.print(WiFi.SSID(i)); // Service Set Identification 
      Serial.print(" ( RSSI:");
      Serial.print(WiFi.RSSI(i));  // Recevied Signal Strength Indication  
      Serial.print(")");
      Serial.print("; Mac Address:");
      Serial.print(WiFi.BSSIDstr(i)); // Basic Serice Set Indentification; alt: BSSI()
      Serial.print("; Password:");
      Serial.print(WiFi.psk()); // password of connected wifi
      Serial.println((WiFi.encryptionType(i) == ENC_TYPE_NONE) ? " " : "*"); 
      /*
       * WiFi.encryptonType(int i)
       * return byte
       * WPA = 2
       * WEP = 5
       * CCMP(WPA) = 4
       * AUTO = 8
       * None = 7
       */
      delay(10);
    }
  }
  Serial.println("");

  delay(5000);
}
