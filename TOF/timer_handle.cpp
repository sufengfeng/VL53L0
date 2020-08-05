#include "FlexiTimer2.h"
#include "Arduino.h"
const int LED = LED_BUILTIN;

void UpdateLED(){
  static boolean output=HIGH;
  digitalWrite(LED,output);  
  output=!output;  
}
int g_nAinValue=0;//  AIn输入信号，用于示波器显示当前值

void TimerHandle()
{
  static uint32_t counter=0;
  counter++;
  if(counter>20){      //设定20ms软定时器
    counter=0;
    UpdateLED();                    //LED闪烁
  }
}
//设置定时器基准为1/9600ms
void InitTimer(){
  pinMode(LED,OUTPUT);
  FlexiTimer2::set(20, 1.0/1000, TimerHandle); // call every 20 1ms "ticks"
  FlexiTimer2::start();
}

