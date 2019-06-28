#include <ESP8266WiFi.h>
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/station-class.html

IPAddress staticIP(192,168,1,112);
IPAddress gateway(192,168,1,1);
IPAddress subnet(255,255,255,0);

void setup(void)
{
  Serial.begin(9600);


//WiFi.config(staticIP, gateway, subnet, dns1, dns2);
WiFi.config(staticIP, gateway, subnet);
  WiFi.begin("EC Workshop", "svvvec2019");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
// WiFi.status returns
//  WL_CONNECTED after successful connection is established
//WL_NO_SSID_AVAIL in case configured SSID cannot be reached
//WL_CONNECT_FAILED if password is incorrect
//WL_IDLE_STATUS when Wi-Fi is in process of changing between statuses
//WL_DISCONNECTED if module is not configured in station mode
    
  Serial.println();
  Serial.printf("SSID: %s\n", WiFi.SSID().c_str());

  Serial.printf("Password is: %s\n", WiFi.psk().c_str() );

  Serial.printf("BSSID i.e access point mac addres: %s\n", WiFi.BSSIDstr().c_str());
  
  Serial.print("Connected, IP address: ");
  Serial.println(WiFi.localIP());

  uint8_t macAddr[6];
  WiFi.macAddress(macAddr);
  Serial.printf("Connected, mac address: %02x:%02x:%02x:%02x:%02x:%02x\n", macAddr[0], macAddr[1], macAddr[2], macAddr[3], macAddr[4], macAddr[5]);

  Serial.printf("Gataway IP: %s\n", WiFi.gatewayIP().toString().c_str());

  Serial.print("DNS #1, #2 IP: ");
  WiFi.dnsIP().printTo(Serial);
  Serial.print(", ");
  WiFi.dnsIP(1).printTo(Serial);
  Serial.println();

  Serial.print("Subnet mask: ");
  Serial.println(WiFi.subnetMask());
}

void loop() {}
