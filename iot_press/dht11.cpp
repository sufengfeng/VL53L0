#include "Arduino.h"
int temp;//温度
int humi;//湿度
int check;//校对码
unsigned int time_count;
int dat[40] = {0};
unsigned long time;

#define pin 8

void setup_dht11()
{
  // put your setup code here, to run once:
  Serial.begin(9600);
}

void loop_dht11()
{
  // put your main code here, to run repeatedly:
begin:
  delay(2000);
//设置2号接口模式为：输出
//输出低电平20ms（>18ms）
//输出高电平40μs
  pinMode(pin,OUTPUT);
  digitalWrite(pin,LOW);
  delay(20);
  digitalWrite(pin,HIGH);
  delayMicroseconds(40);
  digitalWrite(pin,LOW);
//设置2号接口模式：输入
  pinMode(pin,INPUT);
//高电平响应信号
  time_count=10000;
  while(digitalRead(pin) != HIGH)
  {
    if(time_count-- == 0)
    {
    //如果长时间不返回高电平，输出个提示，重头开始。
      Serial.println("HIGH");
      goto begin;
    }
  }
//低电平响应信号
  time_count = 30000;
  while(digitalRead(pin) != LOW)
  {
    if(time_count-- == 0)
    {
      // 如果长时间不返回低电平，输出个提示，重头开始。
      Serial.println("LOW");
      goto begin;
    }
  }
//开始读取bit1-40的数值
  for(int i=0;i<40;i++)
  {
    while(digitalRead(pin) == LOW)
    {}
//当出现高电平时，记下时间“time”
    time = micros();
    while(digitalRead(pin) == HIGH)
    {}
//当出现低电平，记下时间，再减去刚才储存的time
//得出的值若大于50μs，则为‘1’，否则为‘0’
//并储存到数组里去
    if (micros() - time >50)
    {
      dat[i]=1;
    }
    else
    {
      dat[i]=0;
    }
  }

//湿度，8位的bit，转换为数值
  humi = dat[0]*128+dat[1]*64+dat[2]*32+dat[3]*16+dat[4]*8+dat[5]*4+dat[6]*2+dat[7];
//温度，8位的bit，转换为数值
  temp = dat[16]*128+dat[17]*64+dat[18]*32+dat[19]*16+dat[20]*8+dat[21]*4+dat[22]*2+dat[23];
//校对码，8位的bit，转换为数值
  check = dat[32]*128 + dat[33]*64+dat[34]*32+dat[35]*16+dat[36]*8+dat[37]*4+dat[38]*2+dat[39];
//输出：温度、湿度、校对码
  Serial.print("temp:");
  Serial.println(temp);
  Serial.print("humi:");
  Serial.println(humi);
  Serial.print("check:");
  Serial.println(check);
}
