#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(80);
 
void setup() {
 
    Serial.begin(9600);
    WiFi.begin("karan_tech", "ramram786");  //Connect to the WiFi network
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP


    server.on("/", root) ; //call root funtion
 
    server.on("/body", handleBody); //Associate the handler function to the path

    
    server.begin(); //Start the server
    Serial.println("Server listening");
 
}
 
void loop() {
 
    server.handleClient(); //Handling of incoming requests
 
}

void root(){

    String lalodata = "<h1>Kuch tum bhi to karo</h1>";
    server.send(200, "text/html", makePage("Give me title bro", lalodata));
  
}
 
void handleBody() { //Handler for the body path
 
//      if (server.hasArg("plain")== false){ //Check if body received
//            server.send(200, "text/plain", "Body not received");
//            Serial.println(server.args());
//            return;
//  
//      }
 
      String message = "Body received:\n";
             message += server.arg("plain");
             message += "\n";
 
      server.send(200, "text/plain", message);
      Serial.println(message);
}

String makePage(String title, String contents) {
  String s = "<!DOCTYPE html><html><head>";
  s += "<meta name=\"viewport\" content=\"width=device-width,user-scalable=0\">";
  s += "<title>";
  s += title;
  s += "</title><style>body{ background-color= blue;} </style></head><body>";
  s += contents;
  s += "</body></html>";
  return s;
}
