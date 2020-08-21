
#include "timer_handle.h"

extern void setup_uart() ;
extern void loop_uart() ;
extern void setup_bmp180();
extern void loop_bmp180();
extern void loop_dht11();
extern int SlaveSend(char *buf);
extern float temperature;  
extern double pressure;   
extern double altitude;  

extern int temp;
extern int humi;

extern int g_nID;
extern int ReadID(int &gid);

int sensorPin01 = A0;    // select the input pin for the potentiometer
int sensorPin02 = A0;    // select the input pin for the potentiometer

extern int init_pin(void );

void setup() {
  // initialize serial communications at 9600 bps:
  InitTimer();    //初始化定时器
  init_pin();     //标识设备ID
  setup_uart();
  setup_bmp180();
  Serial.begin(9600);//保证串口必须可用
}


int sensorValue01 = 0;  // variable to store the value coming from the sensor
int sensorValue02 = 0;  // variable to store the value coming from the sensor
//#define JSON_TEMPLATE "{\"g_id\":%d,\"m_id\":%d,\"press01\":%d,\"press02\":%d,\"temperature\":%lu,\"pressure\":%lu,\"altitude\":%lu,\"temp\":%d,\"humi\":%d}"
#define JSON_TEMPLATE "{\"g_id\":%d,\"m_id\":%d,\"press01\":%d,\"press02\":%d,\"temperature\":%lu,\"pressure\":%lu,\"altitude\":%lu,\"temp\":%d,\"humi\":%d}"
char g_aSendBuf[128];
void BuildJSON(void){
  static uint32_t messageID=0;
  messageID++;
  
  Serial.println(sensorValue01); 
  uint32_t n_temperature=(uint32_t ) temperature;
  uint32_t n_pressure =(uint32_t )pressure;
  uint32_t n_altitude =(uint32_t )altitude;
  char tmpBuf[64];  
  
  memset(g_aSendBuf,0,128);
  memset(tmpBuf,0,64);
  
  sprintf(g_aSendBuf,"{\"g_id\":%d,\"m_id\":%d,",g_nID,messageID);
  
  sprintf(tmpBuf,"\"press01\":%d,\"press02\":%d,",sensorValue01,sensorValue02);
  strcat(g_aSendBuf,tmpBuf);
  
  sprintf(tmpBuf,"\"temperature\":%lu,\"pressure\":%lu,",n_temperature,n_pressure,n_temperature);
  strcat(g_aSendBuf,tmpBuf);

  sprintf(tmpBuf,"\"altitude\":%lu,",n_temperature);
  strcat(g_aSendBuf,tmpBuf);
  
  sprintf(tmpBuf,"\"temp\":%d,\"humi\":%d}",temp,humi);
  strcat(g_aSendBuf,tmpBuf);
  //,n_pressure, n_altitude,temp,humi);
}
void loop() {
  Serial.println("_running..."); 
  sensorValue01 = analogRead(sensorPin01);  //读取压力传感器
  sensorValue02 = analogRead(sensorPin02);  
  loop_bmp180();                            //bmp180测试通过
  Serial.print("Temperature: ");
  Serial.print(temperature, 1);                            //10 hexadecimal
  Serial.println(" C");
  Serial.print("Pressure: ");
  Serial.print(pressure, 0);                               //10 hexadecimal
  Serial.println(" Pa");
  Serial.print("altitude:");
  Serial.print(altitude);
  Serial.println("m");
  loop_dht11();
//  loop_uart();                              //无线模块
  //sprintf(tmpBuf,JSON_TEMPLATE,g_nID,messageID,sensorValue01,sensorValue02,n_temperature,n_pressure, n_altitude,temp,humi);
  BuildJSON();      //直接sprintf输出有问题
  SlaveSend(g_aSendBuf);
  Serial.println(g_aSendBuf); 
  delay(1000);              // delay in between reads for stability
  
}

