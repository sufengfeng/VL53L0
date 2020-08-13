#include "Arduino.h"

int g_nID=0;

const int ID00 = 5;
const int ID01 = 6;
const int ID02 = 7;
int init_pin(void ){
  pinMode(ID00,INPUT);  
  pinMode(ID01,INPUT);  
  pinMode(ID02,INPUT);  
  return 0;  
}
//读取设备ID
int ReadID(int &gid){
  gid=0;
  gid=gid+digitalRead(ID02);  
  gid=gid<<1;

  gid=gid+digitalRead(ID01);  
  gid=gid<<1;
  
  gid=gid+digitalRead(ID00);  
  gid=gid<<1;
  
  return 0;
}




