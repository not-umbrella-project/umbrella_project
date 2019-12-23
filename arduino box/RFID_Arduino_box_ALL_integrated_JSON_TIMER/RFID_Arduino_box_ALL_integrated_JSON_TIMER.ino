

/*
 * --------------------------------------------------------------------------------------------------------------------
 * Example sketch/program showing how to read new NUID from a PICC to serial.
 * --------------------------------------------------------------------------------------------------------------------
 * This is a MFRC522 library example; for further details and other examples see: https://github.com/miguelbalboa/rfid
 * 
 * Example sketch/program showing how to the read data from a PICC (that is: a RFID Tag or Card) using a MFRC522 based RFID
 * Reader on the Arduino SPI interface.
 * 
 * When the Arduino and the MFRC522 module are connected (see the pin layout below), load this sketch into Arduino IDE
 * then verify/compile and upload it. To see the output: use Tools, Serial Monitor of the IDE (hit Ctrl+Shft+M). When
 * you present a PICC (that is: a RFID Tag or Card) at reading distance of the MFRC522 Reader/PCD, the serial output
 * will show the type, and the NUID if a new card has been detected. Note: you may see "Timeout in communication" messages
 * when removing the PICC from reading distance too early.
 * 
 * @license Released into the public domain.
 * 
 * Typical pin layout used:
 * -----------------------------------------------------------------------------------------
 *             MFRC522      Arduino       Arduino   Arduino    Arduino          Arduino
 *             Reader/PCD   Uno/101       Mega      Nano v3    Leonardo/Micro   Pro Micro
 * Signal      Pin          Pin           Pin       Pin        Pin              Pin
 * -----------------------------------------------------------------------------------------
 * RST/Reset   RST          9             5         D9         RESET/ICSP-5     RST
 * SPI SS      SDA(SS)      10            53        D10        10               10
 * SPI MOSI    MOSI         11 / ICSP-4   51        D11        ICSP-4           16
 * SPI MISO    MISO         12 / ICSP-1   50        D12        ICSP-1           14
 * SPI SCK     SCK          13 / ICSP-3   52        D13        ICSP-3           15
 */

#include <SPI.h>
#include <MFRC522.h>
#include <ArduinoJson.h>
#include <RBD_Timer.h>

#define SS_PIN 53
#define RST_PIN 5
 
MFRC522 rfid(SS_PIN, RST_PIN); // Instance of the class

StaticJsonDocument<300> JSON; // create a JSON object with a static storage
MFRC522::MIFARE_Key key; 
RBD::Timer timer;
// Init array that will store new NUID 
byte store[4];
RBD::Timer Ontimer;
RBD::Timer Offtimer;
bool ON_STATUS_ARRAY[15000];
bool OFF_STATUS_ARRAY[15000];
int ON_index = 0;
int OFF_index = 0;
bool flag = false;
void setup() { 
  Serial.begin(9600);
  SPI.begin(); // Init SPI bus
  rfid.PCD_Init(); // Init MFRC522 
 Ontimer.setTimeout(1000);
  Offtimer.setTimeout(1000);
  for (byte i = 0; i < 6; i++) {
    key.keyByte[i] = 0xFF;
  }

  Serial.println(F("This code scan the MIFARE Classsic NUID."));
  Serial.print(F("Using the following key:"));
  printHex(key.keyByte, MFRC522::MF_KEY_SIZE);
}
 
void loop() {

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  bool flag;
  if ( ! rfid.PICC_IsNewCardPresent()){
    flag = false;
  } 
  else{
    flag = true;
  }
if(flag == true){
  JSON["status"] = true;
  RBD_Flag_TRUE();
  Serial.print(F("PICC type: "));
  MFRC522::PICC_Type piccType = rfid.PICC_GetType(rfid.uid.sak);
  Serial.println(rfid.PICC_GetTypeName(piccType));

  // Check is the PICC of Classic MIFARE type
  if (piccType != MFRC522::PICC_TYPE_MIFARE_MINI &&  
    piccType != MFRC522::PICC_TYPE_MIFARE_1K &&
    piccType != MFRC522::PICC_TYPE_MIFARE_4K) {
    Serial.println(F("Your tag is not of type MIFARE Classic."));
    return;
  }
   for (byte i = 0; i < 4; i++) {
      store[i] = rfid.uid.uidByte[i];
      JsonArray BYTE_data_of_RFID = JSON.createNestedArray("BYTE_data_of_RFID");
      BYTE_data_of_RFID.add(store);
    }
    // Store NUID into nuidPICC array
    Serial.println(F("The NUID tag is:"));
    Serial.print(F("In hex: "));
    printHex(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
    Serial.print(F("In dec: "));
    printDec(rfid.uid.uidByte, rfid.uid.size);
    Serial.println();
  // Stop encryption on PCD
    rfid.PCD_StopCrypto1();
    
}
else{
  Serial.println("No Card");
  RBD_Flag_FALSE();
  JSON["status"] = false;
  for (byte i = 0; i < 4; i++) {
      store[i] = 0xFF;
      JsonArray BYTE_data_of_RFID = JSON.createNestedArray("BYTE_data_of_RFID");
      BYTE_data_of_RFID.add(store);
    }
   
}
}
/**
 * Helper routine to dump a byte array as hex values to Serial. 
 */
void RBD_Flag_TRUE(){
  if(Ontimer.onActive()==false && Offtimer.onActive()==false){
    Ontimer.restart();
    ON_index = 0;
    ON_STATUS_ARRAY[ON_index] = true;
    ON_index++;
  }
  else if(Ontimer.onActive() == true && Offtimer.onActive()==false){
    ON_STATUS_ARRAY[ON_index] = true;
    ON_index++;
  }
  else if(Offtimer.onActive()==true && Ontimer.onActive()==false){
    OFF_STATUS_ARRAY[OFF_index] = true;
    OFF_index++;
  }
}
void RBD_Flag_FALSE(){
if(Offtimer.onActive()==false && Ontimer.onActive()==false){
    Offtimer.restart();
    OFF_index = 0;
    OFF_STATUS_ARRAY[OFF_index] = true;
    OFF_index++;
  }
  else if(Offtimer.onActive() == true && Ontimer.onActive()==false){
    OFF_STATUS_ARRAY[OFF_index] = true;
    OFF_index++;
  }
  else if(Ontimer.onActive()==true && Offtimer.onActive()==false){
    ON_STATUS_ARRAY[ON_index] = true;
    OFF_index++;
  }
}
int countTrueStatus(int index,bool[] b){
  
}
double percentageTrue(int total){
  
}
double percentageFalse(int total){
  
}
void printHex(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], HEX);
  }
}
/**
 * Helper routine to dump a byte array as dec values to Serial.
 */
void printDec(byte *buffer, byte bufferSize) {
  for (byte i = 0; i < bufferSize; i++) {
    Serial.print(buffer[i] < 0x10 ? " 0" : " ");
    Serial.print(buffer[i], DEC);
  }
}
////
//#include <SPI.h>
//#include <MFRC522.h>
//#include <SoftwareSerial.h>
//
//#define SS_PIN 10
//#define RST_PIN 9
//MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance.
//
//SoftwareSerial BTserial(0, 1); // RX | TX
//int sensorPin = A0;
//int sensorValue = 0;
//String lastBlock="";
//void setup() {
//    Serial.begin(9600); // Initialize serial communications with the PC
//SPI.begin();            // Init SPI bus
//mfrc522.PCD_Init(); // Init MFRC522 card
////mfrc522.setPassiveActivationRetries(0x9A); // for example
////Serial.println("Scan PICC to see UID and type...");
//BTserial.begin(9600); 
//Serial.println("Scan PICC to see UID and type...");
//}
//boolean flag=false;
//int counter=0;
//void loop() {
//// Look for new cards
//BTserial.println("Scan PICC to see UID and type...");
//if ( !mfrc522.PICC_IsNewCardPresent()) {
//  if(mfrc522.PICC_IsNewCardPresent()){
//    if(!flag){
//    byte sector         = 1;
//byte blockAddr      = 4;
//byte dataBlock[]    = {
//    0x01, 0x02, 0x03, 0x04, //  1,  2,   3,  4,
//    0x05, 0x06, 0x07, 0x08, //  5,  6,   7,  8,
//    0x08, 0x09, 0xff, 0x0b, //  9, 10, 255, 12,
//    0x0c, 0x0d, 0x0e, 0x0f  // 13, 14,  15, 16
//};
//
//byte trailerBlock   = 7;
//byte status;
//byte buffer[18];
//byte size = sizeof(buffer);
//status = mfrc522.MIFARE_Read(blockAddr, buffer, &size);
//dump_byte_array(buffer, 16);
//    flag=true;
//    }
//  }
//  else{
//    if(flag){
//    flag=false;
//    }
//  }
//      return;
//}  
//}
//
//void dump_byte_array(byte *buffer, byte bufferSize) {
//String a=String((char)buffer[9]);
//String b=String((char)buffer[10]);
//String c=String((char)buffer[11]);
//String d=String((char)buffer[12]);
//String str="";
//str+=a;
//str+=b;
//str+=c;
//str+=d;
//lastBlock=str;
//Serial.println(str);
//BTserial.println(str);
//}
