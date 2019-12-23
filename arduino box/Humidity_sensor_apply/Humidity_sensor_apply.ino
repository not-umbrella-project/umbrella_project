#include <dht.h>


dht DHT;
#define DHT11_PIN 7
void setup(){
  Serial.begin(9600);
}
void loop(){
  int chk = DHT.read11(DHT11_PIN);
  Serial.print("Temperature = ");
  Serial.print(DHT.temperature);
  Serial.println("°C");
  Serial.print("Humidity = ");
  Serial.print(DHT.humidity);
  Serial.println("% humidity");
  delay(2000);
}
