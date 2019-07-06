//https://www.getpostman.com/downloads/
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
 
ESP8266WebServer server(80);
 
void setup() {
 
    Serial.begin(9600);
    WiFi.mode(WIFI_STA);
    WiFi.begin("karan_tech", "ramram786");  //Connect to the WiFi network
 
    while (WiFi.status() != WL_CONNECTED) {  //Wait for connection
 
        delay(500);
        Serial.println("Waiting to connect...");
 
    }
 
    Serial.print("IP address: ");
    Serial.println(WiFi.localIP());  //Print the local IP


    server.on("/", root) ; //call root funtion

    server.on("/form", form);
 
    server.on("/result", handleBody); //send here post request

    
    server.begin(); //Start the server
    Serial.println("Server listening");
 
}
 
void loop() {
 
    server.handleClient(); //Handling of incoming requests
 
}

void root(){

    String lalodata = "<h1>Main Page</h1><p><a href=\"/form\">Form Link</a></p>";
    server.send(200, "text/html", makePage("Welcome", lalodata));
}

void form(){
  String createform = "<h1>Fill Form</h1><br>";
  createform += "<form method=\"get\" action=\"/result\">";
  createform += "<h3>Name :</h3><br><input name=\"name\" type=\"text\" > <br>";
  createform += "<input type=\"submit\" value=\"Submit\">";

  server.send(200, "text/html", makePage("Fill From", createform));
}
 
void handleBody() { //Handler for the body path
 
      if (server.hasArg("name")== false){ //Check if body received
            server.send(200, "text/plain", "Name value not present");
            return;
      }
 
      String message = "Name received:";
             message += server.arg("name");
 
      server.send(200, "text/plain", makePage("Result", message));
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
