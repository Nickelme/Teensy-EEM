#include "EEMManager.h"
EEMManager EEMMan(MacAddress("00-11-22-33-44-55"));

void setup() {
  Serial.begin(9600);
}


void loop(){
  EEMMan.Loop();
}
    
