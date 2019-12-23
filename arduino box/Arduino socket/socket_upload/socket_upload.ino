
#include <ESP8266WiFi.h>

char* ssid = "TP-LINK_6E06";
const char* password =  "jkz061128";

const uint16_t port = 8090;
const char * host = "192.168.0.103";

void setup()
{

  Serial.begin(115200);

  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.println("...");
  }

  Serial.print("WiFi connected with IP: ");
  Serial.println(WiFi.localIP());

}

void loop()
{
    WiFiClient client;
//
//    if (!client.connect(host, port)) {
//
//        Serial.println("Connection to host failed");
//
//        delay(1000);
//        return;
//    }
String a;
  if (Serial.available()){
//    Serial.println("Connected to server successful!");
    String a = Serial.readString();
    client.print(a);
//    Serial.println("Disconnecting...");

      Serial.println("Successfully sent：    " + a);
          client.stop();
}
}
