//JSON data transmission from ESP to arduino
#include <SoftwareSerial.h>
//SoftwareSerial s(D6,D5);
////设备需要设置Nodemcu
//#include <ArduinoJson.h>
// 
//void setup() {
//  // Initialize Serial port
//  Serial.begin(9600);
//  s.begin(9600);
//  while (!Serial) continue;
// 
//}
//void loop() {
//  StaticJsonBuffer<1000> jsonBuffer;
//  JsonObject& root = jsonBuffer.parseObject(s);
//  if (root == JsonObject::invalid())
//    return;
//  Serial.println("JSON received and parsed");
//  root.prettyPrintTo(Serial);
//  Serial.print("Data 1 ");
//  Serial.println("");
//  int data1=root["data1"];
//  Serial.print(data1);
//  Serial.print("   Data 2 ");
//  int data2=root["data2"];
//  Serial.print(data2);
//  Serial.println("");
//  Serial.println("---------------------xxxxx--------------------");
// 
//}



///////////////////////////////////////////////////////////////////


#include <SoftwareSerial.h>
SoftwareSerial s(D6,D5); //RX,TX
char data;
void setup() {
s.begin(9600);
Serial.begin(9600);
 pinMode(LED_BUILTIN, OUTPUT);
}
 
void loop() {
  s.write("s");
  if (s.available()>0)
  {
    data=s.read();
    Serial.println(data);
    digitalWrite(LED_BUILTIN, HIGH);
    delay(1);
  }
 digitalWrite(LED_BUILTIN, LOW); 

}
