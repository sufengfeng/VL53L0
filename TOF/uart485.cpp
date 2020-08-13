#include "Arduino.h"
#include <SoftwareSerial.h>

SoftwareSerial Slave(10, 11);  
char val;
int DE_RE=2;
int RE_DE=3;

void setup_485() {
  Serial.begin(38400);   
  Serial.println("Slave is ready!");
  Slave.begin(38400);
  pinMode(DE_RE,OUTPUT);   
  digitalWrite(DE_RE,LOW);
  pinMode(RE_DE,OUTPUT);   
  digitalWrite(RE_DE,LOW);
  
}
//如果读取错误，报错
int read_485(char strBuf[],int &lenRet){
  lenRet=0;
  digitalWrite(DE_RE,LOW);
  digitalWrite(RE_DE,LOW);
   while (Slave.available()) {
    val = Slave.read();
    strBuf[lenRet++] = val;
  }
  return 0;
 }
 
int write_485(char strBuf[],int dataLen){
  digitalWrite(DE_RE,HIGH);
  digitalWrite(RE_DE,HIGH);
  for(int i=0;i<dataLen;i++){
      Slave.write(strBuf[i]);   
  }
  digitalWrite(DE_RE,LOW);
  digitalWrite(RE_DE,LOW);
  return 0;
 }


void loop_485test() {
  char strBuf[235];
  memset(strBuf,0,sizeof(strBuf));
  int len;
  int ret=read_485(strBuf,len);
  Serial.println(ret);
  Serial.println(strBuf);
  
  int i=0;
  memset(strBuf,0,sizeof(strBuf));
  while(Serial.available()) {
    val = Serial.read();
    strBuf[i++]=val;
  }
  Serial.println(strBuf);
  write_485(strBuf,strlen(strBuf));
}
extern int g_nID;
extern int g_nPeriod;
extern uint32_t g_nCurrentDistance;

//标定值
uint16_t g_nStandardizationArray[]={0,100,200,300,400,500,600,700,800,900,1000,1100,1200,1300,1400,1500,1600,1700,1800,1900,2000};

int standardization(int tmpValue){        //数据标定
  g_nStandardizationArray[tmpValue/100]=g_nCurrentDistance;
}
int handle_cmd(char strBuf[],int len){
  for(int i=0;i<len-2;i++){
    if(strBuf[i]==0xFF&&strBuf[i+1]==0xFE){
      if(strBuf[i+2]!=g_nID){   //如果不是本设备的命令，则过滤掉
        i=i+1;
        continue;
        }
        else{                   //响应本设备命令
            switch(strBuf[i+2]){
              case 0x01:
                g_nPeriod=strBuf[i+3];
                g_nPeriod=g_nPeriod<<3;
                g_nPeriod=g_nPeriod+strBuf[i+4];
                Serial.println(g_nPeriod);
              break;
              case 0x02:
                int tmpValue;
                tmpValue=strBuf[i+3];
                tmpValue=tmpValue<<3;
                tmpValue=tmpValue+strBuf[i+4];
                standardization(tmpValue);    //数据标定
                Serial.println(tmpValue);
              break;
              default:
                Serial.println(strBuf);
                Serial.println("Not support");
              break;
              }
          }
      }
    }
  return 0;  
}
//循环读取串口数据，并处理串口数据，响应服务器发送数据
void loop_485() {
  char strBuf[235];
  int len=0;
  memset(strBuf,0,sizeof(strBuf));
  int ret=read_485(strBuf,len);
  Serial.println(len);
  Serial.println(strBuf);
  handle_cmd(strBuf,len);
}


