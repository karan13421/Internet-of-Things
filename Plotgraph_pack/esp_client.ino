#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>


WiFiClient client;
HTTPClient http;

const int sesnor = 3

void setup() {
  Serial.begin(9600);
  pinMode(sensor, INPUT);
  WiFi.mode(WIFI_STA);
  WiFi.begin("karan_tech","ramram786");

  while(WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  // ***********************************************
}

void loop(){
        
        int data = digitalRead(sesnor);
        data = map(data, 1, 100, 1, 10 );
        http.begin(client, "http://192.168.1.100:5006/sesnor1/"+data);
        int httpstatus = http.GET();
        if( httpstatus >0){
          String data = http.getString();
          Serial.println(data); 
        } 
        else 
        Serial.printf("[HTTP] GET... failed");
        
        http.end();  
        
      delay(3000);
}
