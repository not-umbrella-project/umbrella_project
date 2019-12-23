
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
