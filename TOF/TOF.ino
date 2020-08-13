
#include "timer_handle.h"

extern void init_vl53l0() ;
extern int GetVl53l0Value(uint16_t &acnt,uint16_t &scnt,uint16_t &dist,byte &DeviceRangeStatusInternal) ;
extern int GetDistance();
extern void setup_485() ;
extern void loop_485() ;
extern int g_nCurrentDistance;
extern int g_nID;
extern int ReadID(int &gid);
int init_pin(void );

void setup() {
  // initialize serial communications at 9600 bps:
  InitTimer();    //定时器处理优先级较高的事务
  init_vl53l0();
  init_pin();     //标识设备ID
  setup_485();
  ReadID(g_nID);
}

void loop() {
  GetDistance();  //定时进行获取TOF数据，并进行均值滑动滤波
 Serial.println(g_nCurrentDistance); 
  loop_485();
  delay(10);              // delay in between reads for stability
}



