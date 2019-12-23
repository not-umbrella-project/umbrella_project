//Arduino code
#include <SoftwareSerial.h>
SoftwareSerial s(5,6);//(Rx, Tx)
 
void setup() {
s.begin(9600);
}
 
void loop() {
int data=50;
if(s.available()>0)
{ 
  char c = s.read();
  if(c=='s'){
    s.write(c);
  }
 
}
}
