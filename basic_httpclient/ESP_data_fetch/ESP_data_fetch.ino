#include <ESP8266WiFi.h>
#include <ESP8266HTTPClient.h>
#include <WiFiClient.h>

//http://httpbin.org/#/Response_formats
//https://github.com/esp8266/Arduino/blob/master/libraries/ESP8266HTTPClient/src/ESP8266HTTPClient.h
//https://links2004.github.io/Arduino/dd/d8d/class_h_t_t_p_client.html
//https://techtutorialsx.com/2016/07/17/esp8266-http-get-requests/


  WiFiClient client;
  HTTPClient http;

  const char * headerKeys[] = {"date", "server"} ;
  const size_t numberOfHeaders = 2;

void setup() {
  Serial.begin(9600);

  WiFi.mode(WIFI_STA);
  WiFi.begin("karan_tech","ramram786");

  while(WiFi.status() != WL_CONNECTED ) {
    delay(500);
    Serial.print(".");
  }
  // ***********************************************
}

void loop(){

      int stat = http.begin(client, "http://192.168.1.100:5000/");

      Serial.print("Status");
      Serial.println(stat);

      if(stat){

#if 1

//        http.collectHeaders(headerKeys, numberOfHeaders);

        int httpstatus = http.GET();

        Serial.print("Http response:");
        Serial.println(httpstatus);

        if( httpstatus >0){

          if (httpstatus == HTTP_CODE_OK || httpstatus == HTTP_CODE_MOVED_PERMANENTLY) {
          String data = http.getString();
          Serial.print("body");
          Serial.println(data);


//          for(int i = 0; i< http.headers(); i++){
//             Serial.println(http.header(i));
//              }

//          String headerDate = http.header("date");
//                  Serial.println(headerDate);
// 
//          String headerServer = http.header("server");
//          Serial.println(headerServer);
              
          }
          
        } 
        else 
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpstatus).c_str()); 
        http.end();

#else 
      http.addHeader("Content-Type", "application/x-www-form-urlencoded");  //Specify content-type header
 
      int httpCode = http.POST("kush acha bejo");   //Send the request
      String payload = http.getString();                  //Get the response payload
 
       Serial.println(httpCode);   //Print HTTP return code
       Serial.println(payload);    //Print request response payload
 
       http.end(); 

#endif
        
      } else {
        Serial.print("unable to connect");
      }

      delay(10000);


     
  
}
