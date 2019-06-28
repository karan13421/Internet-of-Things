//https://github.com/esp8266/Arduino/blob/dd81336b79ddf15925876b983af13816d9d5807e/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.cpp
//http://jsonplaceholder.typicode.com/
#include <ESP8266WiFi.h>
#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>

ESP8266WiFiMulti WiFiMulti;

void setup() {

  Serial.begin(9600);

  for (uint8_t t = 10; t > 0; t--) {
    Serial.printf("[SETUP] WAIT %d...\n", t);
    Serial.flush();
    delay(1000);
  }

  WiFi.mode(WIFI_STA);
  WiFiMulti.addAP("karan_tech", "ramram786");

}

void loop() {
  // wait for WiFi connection
  if ((WiFiMulti.run() == WL_CONNECTED)) {

    WiFiClient client;
    HTTPClient http; //must be declared after WiFiClient for correct destruction order, because used by http.begin(client,...)

    Serial.print("begin\n");

    http.begin(client, "http://jigsaw.w3.org/HTTP/connection.html");
//      http.begin(client, "http://karanrathore.me");
  
    int httpCode = http.GET();
    
    if (httpCode > 0) {
      Serial.printf("Status: %d\n", httpCode);

      if (httpCode == HTTP_CODE_OK) {

        // get lenght of document (is -1 when Server sends no Content-Length header)
        int len = http.getSize();

        // create buffer for read
        uint8_t buff[128] = { 0 };

#if 0
        // with API
        Serial.println(http.getString());
#else
        // or "by hand"

        // get tcp stream
        
        WiFiClient * stream = &client;

        // read all data from server
//        while (http.connected() && (len > 0 || len == -1)) {
//          // read up to 128 byte
//          int c = stream->readBytes(buff, std::min((size_t)len, sizeof(buff)));
//          Serial.printf("readBytes: %d\n", c);
//          if (!c) {
//            Serial.println("read timeout");
//          }
//
//          // write it to Serial
//          Serial.write(buff, c);
//
//          if (len > 0) {
//            len -= c;
//          }
//        }

          http.writeToStream(&Serial);


          
          
#endif

        Serial.println();
        Serial.print("[HTTP] connection closed or file end.\n");
      }
    } else {
      Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
    }

    http.end();
  }

  delay(60000);
}
