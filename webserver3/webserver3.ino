//https://github.com/esp8266/Arduino/blob/master/libraries/DNSServer/src/DNSServer.cpp
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/soft-access-point-class.html
#include <ESP8266WiFi.h>
#include <DNSServer.h>  // DNS library by arduino
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

const IPAddress apIP(192, 168, 1, 4);
const IPAddress gateway(192, 168, 1, 1);
const char* apSSID = "ESP8266 SSID";
String lalodata = "ok";

DNSServer dnsServer;
ESP8266WebServer webServer(80);  // webServer(PORT_NUMBER)
int data = 0;

void setup() {
  Serial.begin(9600);
  delay(10);
  WiFi.mode(WIFI_AP);
  WiFi.softAPConfig(apIP, gateway, IPAddress(255, 255, 255, 0));  //sof
  WiFi.softAP(apSSID);
  dnsServer.start(53, "meriwebsite.karan", apIP);  //(PORT, "domainname", "ip")
  Serial.print("begin");
  startWebServer();
}

void loop() {
  dnsServer.processNextRequest();
  webServer.handleClient();

  

  if (Serial.available() > 0)
  {
    data = Serial.read();
    data = data - 48;
    //  if(data == 100)
    lalodata = data;
  }
}

void startWebServer() {
    //webServer.on("/", function());


  webServer.on("/", []() {
String data1="<p><karan rathore<br> <div style=\"color:red;\"> Rollno:"+lalodata+"</div></p>";
    webServer.send(200, "text/html", makePage("Give me title", data1));
  });
  
    webServer.on("/info", []() {
    webServer.send(200, "text/html", makePage("Give me title", lalodata));
  });


  webServer.begin();
}


String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}
