// Arduino RBD Timer Library v1.3.0 Example - A three second interval timer that prints to serial.
// https://github.com/alextaujenis/RBD_Timer
// Copyright 2016 Alex Taujenis
// MIT License

#include <RBD_Timer.h> // https://github.com/alextaujenis/RBD_Timer

RBD::Timer Ontimer;
RBD::Timer Offtimer;
bool ON_STATUS_ARRAY[15000];
bool OFF_STATUS_ARRAY[15000];
int ON_index = 0;
int OFF_index = 0;
bool flag = false;
void setup() {
  Serial.begin(115200);
  Ontimer.setTimeout(1000);
  Offtimer.setTimeout(1000);
}

void loop() {
if(flag == true){
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
else{
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
}
