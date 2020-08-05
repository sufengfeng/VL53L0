#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial Slave(10, 11);  
char val;
int DE_RE=2;

void setup_485() {
  
  Slave.begin(38400);
  pinMode(DE_RE,OUTPUT);   
  digitalWrite(DE_RE,LOW);
}

void loop_485() {
  
  digitalWrite(DE_RE,HIGH);
  Slave.write(val);
    
  digitalWrite(DE_RE,LOW);
  while(Slave.available()) {
    val = Slave.read();
  }
  
}
