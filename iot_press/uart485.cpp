#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial Slave(10, 11);  
char val;
int DE_RE=2;

void setup_uart() {
  Slave.begin(115200);
}

void loop_uart() {
  
 
  Slave.write("tesst");
    

  while(Slave.available()) {
    val = Slave.read();
    Serial.println(val); 
  }
  
}
