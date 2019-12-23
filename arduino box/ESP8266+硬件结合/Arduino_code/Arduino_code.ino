#include <SoftwareSerial.h>
#include <ArduinoJson.h>
SoftwareSerial s(5,6);
int inputPin = 3; //crash sensor input pin
void setup() {
  // put your setup code here, to run once:
pinMode(inputPin, INPUT);
s.begin(9600);
}
void loop() {
 StaticJsonBuffer<1000> jsonBuffer;
 JsonObject& root = jsonBuffer.createObject();
int val = digitalRead(inputPin);  // read input value
  if (val == HIGH) {                // check if the input is HIGH
      root["umbrella status"] = false;
  } else {
      root["umbrella status"] = true;
  }

if(s.available()>0)
{
 root.printTo(s);

    }
}
