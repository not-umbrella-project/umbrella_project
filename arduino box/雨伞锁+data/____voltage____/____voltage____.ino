int inputPin = 3;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
}
char rx_byte;
void loop() {
  // put your main code here, to run repeatedly:
if (Serial.available() > 0) {    // is a character available?
    rx_byte = Serial.read(); 
if ((rx_byte >= '0') && (rx_byte <= '9')) {
      Serial.print("Number received: ");
      Serial.println(rx_byte);
    }
}
}
