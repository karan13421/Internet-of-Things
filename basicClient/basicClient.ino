#include <ESP8266WiFi.h>
//https://arduino-esp8266.readthedocs.io/en/latest/esp8266wifi/client-class.html
//https://www.w3.org/Protocols/rfc2616/rfc2616-sec5.html
//https://www.tutorialspoint.com/http/http_requests.htm
//https://developer.mozilla.org/en-US/docs/Web/HTTP/Methods/POST

const char* host = "192.168.0.100";
const uint16_t port = 5004;

void setup(void)
{
  Serial.begin(9600);
  WiFi.mode(WIFI_STA);
  WiFi.begin("EC Workshop", "svvvec2019");
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
    
}

void loop() {

  WiFiClient client;

  Serial.printf("\n[Connecting to %s ... ", host);
  if (client.connect(host, port))
  {
    Serial.println("connected]");

    Serial.println("[Sending a request]");
    
    client.print(String("GET /") + " HTTP/1.1\r\n" +
                 "Host: " + host + "\r\n" +
                 "Connection: close\r\n" +
                 "\r\n"
                );

//      client.print(String("POST /hello ") + " HTTP/1.1\r\n" +
//                 "Host: " + host + "\r\n" +
//                 "Content-Type: application/x-www-form-urlencoded" + "\r\n" +
//                 "Content-Length: 10" + "\r\n" +
//                 "Connection: keep-alive\r\n\n" + "name=karan"
//                );



//  client.print("method /any_directory?key=data&key2=data2 http version\r\n Host: hostname \r\n Connection: close\r\n"); 

//Connection: keep-alive
//Connection: close

//Content-Type: text/plain
//Content-Type: application/x-www-form-urlencoded
//Content-Type: multipart/form-data;boundary="boundary"



    Serial.println("[Response:]");
    while (client.connected() || client.available())
    {
      if (client.available())
      {
        String line = client.readStringUntil('\n');
        Serial.println(line);
      }
    }
    client.stop();
    Serial.println("\n[Disconnected]");
  }
  else
  {
    Serial.println("connection failed!]");
    client.stop();
  }
  delay(5000);
  
  }
