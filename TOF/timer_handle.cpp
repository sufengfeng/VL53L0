#include "FlexiTimer2.h"
#include "Arduino.h"
const int LED = LED_BUILTIN;

void UpdateLED(){
  static boolean output=HIGH;
  digitalWrite(LED,output);  
  output=!output;  
}

int g_nPeriod=1000;
extern int g_nID;
extern uint32_t g_nCurrentDistance;
extern int write_485(char strBuf[],int dataLen);
char sendBuf[]={0xFF,0xFE,0x01,0xff,0xff,0xef,0xff};
extern uint16_t g_nStandardizationArray[];
uint32_t noramal(uint32_t currentDistance){
  int index=currentDistance/100;
  if(index>19)  //不在标定值范围内，则直接输出数据
    return currentDistance;
  uint32_t retDistance=(g_nStandardizationArray[index+1] -g_nStandardizationArray[index] )/100*(currentDistance-index*100)+g_nStandardizationArray[index];
  return  retDistance;
}
int SendTOFData(){
  int max_counter=g_nPeriod/20;
  static uint32_t counter=0;
  if(counter>max_counter){
    counter=0;
    sendBuf[2]=   g_nID;                              //设备ID
    uint32_t tmpValue=noramal(g_nCurrentDistance);    //根据标定值，进行标准化
    sendBuf[3]=   tmpValue&0xFF;
    
    tmpValue=tmpValue>>8;
    sendBuf[4]=   tmpValue&0xFF;
    
    write_485(sendBuf,7);
   }
   counter++;
}

//中断处理函数
void TimerHandle()
{
  static uint32_t counter=0;
  counter++;
  if(counter>20){      //
    counter=0;
    UpdateLED();                    //LED更新
  }
  SendTOFData();
}
//开启20ms定时器
void InitTimer(){
  pinMode(LED,OUTPUT);
  FlexiTimer2::set(20, 1.0/1000, TimerHandle); // call every 20 1ms "ticks"
  FlexiTimer2::start();
}


