/*
  To upload through terminal you can use: curl -u admin:admin -F "image=@firmware.bin" esp8266-webupdate.local/firmware
*/

// https://medium.com/@jgillard/marrying-esp8266-aws-iot-69f1ab219c2

#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <ESP8266HTTPUpdateServer.h>



// ***************************************************************
    
      #include "FS.h"
    #include <PubSubClient.h>
    #include <NTPClient.h>
    #include <WiFiUdp.h>

// *****************************************************************


#ifndef STASSID
#define STASSID "SSID"
#define STAPSK  "PASSWORD"
#endif

const char* host = "karan";
const char* update_path = "/firmware";
const char* update_username = "admin";
const char* update_password = "admin";
const char* ssid = STASSID;
const char* password = STAPSK;

ESP8266WebServer httpServer(80);
ESP8266HTTPUpdateServer httpUpdater;


  // *****************************************************************
      WiFiUDP ntpUDP;

      NTPClient timeClient(ntpUDP, "pool.ntp.org");


      const char* AWS_endpoint = "xyz-ats.iot.us-east-1.amazonaws.com"; //MQTT broker ip
  // *****************************************************************


  void callback(char* topic, byte* payload, unsigned int length) {
      Serial.print("Message arrived [");
      Serial.print(topic);
      Serial.print("] ");
      for (int i = 0; i < length; i++) {
        Serial.print((char)payload[i]);
  }
  Serial.println();
  }



  WiFiClientSecure espClient;
PubSubClient client(AWS_endpoint, 8883, callback, espClient); //set  MQTT port number to 8883 as per //standard
long lastMsg = 0;
char msg[50];
int value = 0;



void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect("first")) {
      Serial.println("connected");
      // Once connected, publish an announcement...
      client.publish("device/shadow/update", "hello world");
      // ... and resubscribe
      client.subscribe("device/shadow/get");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");

      char buf[256];
      espClient.getLastSSLError(buf,256);
      Serial.print("WiFiClientSecure SSL error: ");
      Serial.println(buf);

      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}


void setup(void) {
  pinMode(LED_BUILTIN, OUTPUT); 

  Serial.begin(9600);


  espClient.setBufferSizes(512, 512);

  
  Serial.println();
  Serial.println("Booting Sketch...");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  
  while (WiFi.waitForConnectResult() != WL_CONNECTED) {
    WiFi.begin(ssid, password);
    Serial.println("WiFi failed, retrying.");
  }


    timeClient.begin();
  while(!timeClient.update()){
    timeClient.forceUpdate();
  }

  espClient.setX509Time(timeClient.getEpochTime());

    delay(1000);
  if (!SPIFFS.begin()) {
    Serial.println("Failed to mount file system");
    return;
  }

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());


  File cert = SPIFFS.open("/cert.der", "r"); //replace cert.crt eith your uploaded file name
  if (!cert) {
    Serial.println("Failed to open cert file");
  }
  else
    Serial.println("Success to open cert file");
  
    Serial.println(WiFi.localIP());

    delay(1000);

  if (espClient.loadCertificate(cert))
    Serial.println("cert loaded");
  else
    Serial.println("cert not loaded");

  // Load private key file
  File private_key = SPIFFS.open("/private.der", "r"); //replace private eith your uploaded file name
  if (!private_key) {
    Serial.println("Failed to open private cert file");
  }
  else
    Serial.println("Success to open private cert file");

  delay(1000);

  if (espClient.loadPrivateKey(private_key))
    Serial.println("private key loaded");
  else
    Serial.println("private key not loaded");



    // Load CA file
    File ca = SPIFFS.open("/ca.der", "r"); //replace ca eith your uploaded file name
    if (!ca) {
      Serial.println("Failed to open ca ");
    }
    else
    Serial.println("Success to open ca");

    delay(1000);

    if(espClient.loadCACert(ca))
    Serial.println("ca loaded");
    else
    Serial.println("ca failed");

  Serial.print("Heap: "); Serial.println(ESP.getFreeHeap());

  MDNS.begin(host, WiFi.localIP() );
  httpUpdater.setup(&httpServer, update_path, update_username, update_password);
  httpServer.begin();

  
  MDNS.addService("http", "tcp", 80);
  Serial.printf("HTTPUpdateServer ready! Open http://%s.local%s in your browser and login with username '%s' and password '%s'\n", host, update_path, update_username, update_password);

}

void loop(void) {
  httpServer.handleClient();
  MDNS.update();

    digitalWrite(LED_BUILTIN, LOW);   // Turn the LED on (Note that LOW is the voltage level
  // but actually the LED is on; this is because
  // it is active low on the ESP-01)
  delay(1000);                      // Wait for a second
  digitalWrite(LED_BUILTIN, HIGH);  // Turn the LED off by making the voltage HIGH
  delay(1000);                      // Wait for two seconds (to demonstrate the active low LED)

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  long now = millis();
  if (now - lastMsg > 2000) {
    lastMsg = now;
    ++value;
    snprintf (msg, 75, "hello world #%ld", value);
    Serial.print("Publish message: ");
    Serial.println(msg);
    client.publish("device/shadow/update", msg);
    Serial.print("Heap: "); Serial.println(ESP.getFreeHeap()); //Low heap can cause problems
  }

  
}
