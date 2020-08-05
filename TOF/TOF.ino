
#include "timer_handle.h"

extern void init_vl53l0() ;
extern int GetVl53l0Value(uint16_t &acnt,uint16_t &scnt,uint16_t &dist,byte &DeviceRangeStatusInternal) ;
extern void setup_485() ;
extern void loop_485() ;
void setup() {
  // initialize serial communications at 9600 bps:
  InitTimer();    //初始化定时器
  init_vl53l0();
  setup_485();
  Serial.begin(9600);//保证串口必须可用
}

void loop() {
  uint16_t acnt;
  uint16_t scnt;
  uint16_t dist;
  byte DeviceRangeStatusInternal;
  int ret=GetVl53l0Value(acnt,scnt,dist,DeviceRangeStatusInternal);
  if(ret!=0){
    Serial.println("not ready");  
  }else
  {
    Serial.print("ambient count: "); Serial.println(acnt);    
    Serial.print("signal count: ");  Serial.println(scnt);
    Serial.print("distance ");       Serial.println(dist);
    Serial.print("status: ");        Serial.println(DeviceRangeStatusInternal);  
  }
  loop_485();
  delay(1000);              // delay in between reads for stability
//  Serial.println("_running..."); 
}

