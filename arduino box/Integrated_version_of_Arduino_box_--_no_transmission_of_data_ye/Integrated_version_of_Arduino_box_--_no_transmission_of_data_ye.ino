// this is the code for the integrated sensors in 
// the arduino box (not included the transmission of data yet)
//-> 12.7
//-> 12.17 functionality finish
/* The pin declarations: 
 *  Humidity: 7
 *  Lock: 4
 *  Crash: 6
 *  Ultrasonic1: A0,A1
 *  Ultrasonic2: A2,A3
 *  
 */
/*Import following Libraries*/
#include <Ultrasonic.h>
#include <Wire.h> 
#include <LiquidCrystal.h>
#include <dht.h>
#include "HX711.h"
#include <ArduinoJson.h>
dht DHT;
HX711 scale;

#define HORIZONTAL_LENGTH 100 //unit = cm
#define CRASH_PIN 6 
#define LOCK_PIN  4
#define DHT11_PIN 7
#define Width_UPPER_LIMIT 15
#define Width_LOWER_LIMIT 10
#define Weight_UPPER_LIMIT 400 //gram
#define Weight_LOWER_LIMIT 250 //gram
#define threshold 90 //threshold of the score
#define Weight_PUNISHMENT 0.5
#define Crash_PUNISHMENT 0.5
#define Width_PUNISHMENT 0.5
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
 const int LOADCELL_DOUT_PIN = 2;
 const int LOADCELL_SCK_PIN = 3;
 LiquidCrystal LOCK_SCREEN(0x27,rs, en, d4, d5, d6, d7); 
  LiquidCrystal HUMIDITY_SCREEN(rs, en, d4, d5, d6, d7); 
  Ultrasonic ultrasonic_low(A0, A1);
  Ultrasonic ultrasonic_high(A2, A3);
  StaticJsonDocument<300> JSON; // create a JSON object with a static storage
int distance1,distance2,crash_value;
void setup() {
  // put your setup code here, to run once:
    
  Serial.begin(9600);
  pinMode(CRASH_PIN, INPUT);     // declare Micro switch as input
  pinMode(LOCK_PIN, OUTPUT);
  digitalWrite(LOCK_PIN, LOW);
  LOCK_SCREEN.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  HUMIDITY_SCREEN.begin(16,2);//Defining 16 columns and 2 rows of lcd display
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
    Serial.println("Initializing the scale");
  // Initialize library with data output pin, clock input pin and gain factor.
  // Channel selection is made by passing the appropriate gain:
  // - With a gain factor of 64 or 128, channel A is selected
  // - With a gain factor of 32, channel B is selected
  // By omitting the gain factor parameter, the library
  // default "128" (Channel A) is used here.
  scale.begin(LOADCELL_DOUT_PIN, LOADCELL_SCK_PIN);
  Serial.println("Before setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());     // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));   // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight (not set yet)

  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);  // print the average of 5 readings from the ADC minus tare weight (not set) divided
            // by the SCALE parameter (not set yet)
  scale.set_scale(2280.f);                      // this value is obtained by calibrating the scale with known weights; see the README for details
  scale.tare();               // reset the scale to 0
  Serial.println("After setting up the scale:");
  Serial.print("read: \t\t");
  Serial.println(scale.read());                 // print a raw reading from the ADC
  Serial.print("read average: \t\t");
  Serial.println(scale.read_average(20));       // print the average of 20 readings from the ADC
  Serial.print("get value: \t\t");
  Serial.println(scale.get_value(5));   // print the average of 5 readings from the ADC minus the tare weight, set with tare()
  Serial.print("get units: \t\t");
  Serial.println(scale.get_units(5), 1);        // print the average of 5 readings from the ADC minus tare weight, divided
            // by the SCALE parameter set with set_scale
  Serial.println("Readings:");
}
bool LOCKER_OPEN(){
  int SCORE = 100;
  bool umbrella_status = false;
  crash_value = digitalRead(CRASH_PIN);  // read input value //the value is either HIGH or LOW
  distance1 = ultrasonic_low.Ranging(CM);
  distance2 = ultrasonic_high.Ranging(CM);
  int object_width = HORIZONTAL_LENGTH - distance1 - distance2;
   long object_weight = scale.read(); // Weight_LOWER_LIMIT
  if(crash_value == HIGH){
    //object bumps to the end of the box successfully
    //wechat returns the user a notification that the umbrella is not inserted in the box successfully
    SCORE = threshold-0.1; // the umbrella is inserted incorrectly
    Serial.println("Umbrella is not inserted correctly. It does not touch the crash sensor"); // return the notification via wechat program
    return false;
  }
  if(object_width > Width_LOWER_LIMIT && object_width < Width_UPPER_LIMIT){
    // object width satisfies the requirements

  }
  else if(object_width>Width_UPPER_LIMIT){
    SCORE -= (object_width - Width_UPPER_LIMIT) * Width_PUNISHMENT;
  }
  else{
    SCORE -= (Width_LOWER_LIMIT - object_width) * Width_PUNISHMENT;
  }
  if(object_weight > Weight_LOWER_LIMIT && object_weight < Weight_UPPER_LIMIT){
    //object weight satisfies the requirements

  }
  else if(object_weight > Weight_UPPER_LIMIT){
    SCORE -= (object_weight - Weight_UPPER_LIMIT) * Weight_PUNISHMENT;
  }
  else {
    SCORE -= (Weight_LOWER_LIMIT - object_weight) * Weight_PUNISHMENT;
  }
  
  if(SCORE > threshold){
    umbrella_status = true;
  }
  JSON_Object_Packing_ALGORITHM(umbrella_status,crash_value,distance1,distance2,object_width,SCORE,object_weight);
  return umbrella_status;
}
void loop() {
  // put your main code here, to run repeatedly:
  bool umbrella_status = false;
//  int LOCK_STATUS = digitalRead(LOCK_PIN);
  int LOCK_STATUS = HIGH;
  if(LOCK_STATUS == HIGH){
    LOCK_SCREEN.setCursor(0,0); //Defining positon to write from first row,first column .
    LOCK_SCREEN.print("Locker is: "); //You can write 16 Characters per line .
    LOCK_SCREEN.setCursor(0,1);
    LOCK_SCREEN.print("OPEN");

    HUMIDITY_SCREEN.setCursor(0,0); //Defining positon to write from first row,first column .
    HUMIDITY_SCREEN.print("Temp is: "); //You can write 16 Characters per line .
    HUMIDITY_SCREEN.print(DHT.temperature);
    HUMIDITY_SCREEN.println("°C");
    HUMIDITY_SCREEN.setCursor(0,1);
    HUMIDITY_SCREEN.print("Humidity is: "); //You can write 16 Characters per line .
    HUMIDITY_SCREEN.print(DHT.humidity);
    HUMIDITY_SCREEN.print("%");
    umbrella_status = LOCKER_OPEN();
    if(umbrella_status == false)
      Serial.println("The umbrella is not successfully inserted");
    else
      Serial.println("The umbrella is successfully inserted");
  }
  else{
    LOCK_SCREEN.setCursor(0,0); //Defining positon to write from first row,first column .
    LOCK_SCREEN.print("Locker is: "); //You can write 16 Characters per line .
    LOCK_SCREEN.setCursor(0,1);
    LOCK_SCREEN.print("CLOSED");
    JSON_Object_Packing_LOOP();
  }
  delay(10); //0.01 second delay, this is a place that can increase the responsiveness
  scale.power_down();              // put the ADC in sleep mode
  scale.power_up();
//  serializeJsonPretty(JSON, Serial);
}
void JSON_Object_Packing_ALGORITHM(bool umbrella_status, bool crash_value, int distance1, int distance2, int object_width,int SCORE, int object_weight){
  JSON["umbrella_status"] = umbrella_status;
  JSON["crash_value"] = crash_value;
  JSON["distance1"] = distance1;
  JSON["distance2"] = distance2;
  JSON["object_width"] =object_width;
  JSON["SCORE"] = SCORE;
  JSON["object_weight"] = object_weight;
}
void JSON_Object_Packing_LOOP(){
  JSON["LOCK_STATUS"] = false;
  //initialize all of the variables as default, use server to deal with the NAN or NULL or 0 variables and objects 
  JSON["umbrella_status"] = false;
  JSON["crash_value"] = false;
  JSON["distance1"] = 0;
  JSON["distance2"] = 0;
  JSON["object_width"] =0;
  JSON["SCORE"] = 0;
  JSON["object_weight"] = 0;
}
