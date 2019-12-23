#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5);
//设备需要设置Nodemcu
#include <ArduinoJson.h>
 
void setup() {
  // Initialize Serial port
  Serial.begin(9600);
  s.begin(9600);
  while (!Serial) continue;
 
}
void loop() {
  StaticJsonBuffer<1000> jsonBuffer;
  JsonObject& root = jsonBuffer.parseObject(s);
  if (root == JsonObject::invalid())
    return;
  Serial.println("JSON received and parsed");
  root.prettyPrintTo(Serial);
  Serial.println(" ");
}
