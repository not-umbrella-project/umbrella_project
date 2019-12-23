int inputPin = 4;
void setup() {
  // put your setup code here, to run once:
Serial.begin(9600);
pinMode(inputPin, OUTPUT);
digitalWrite(inputPin, LOW);
}
char rx_byte=0;
void loop() {
  // put your main code here, to run repeatedly:
   // is a character available?
    rx_byte = Serial.read(); 
    digitalWrite(inputPin, LOW);
    Serial.println("input s to start");
    if (rx_byte == 's') {
        Serial.print("Number received: ");
        Serial.println(rx_byte);
        digitalWrite(inputPin, HIGH);
        delay(2000);
        while(1){
        Serial.println("input e to end");
        rx_byte = Serial.read();
        if(rx_byte == 'e'){
        digitalWrite(inputPin, LOW);
        Serial.println("End voltage");
        delay(2000);
        break;
        }

      }
   }
}
