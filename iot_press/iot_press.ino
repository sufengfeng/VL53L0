
#include "timer_handle.h"

extern void setup_uart() ;
extern void loop_uart() ;
extern void setup_bmp180();
extern void loop_bmp180();
extern void loop_dht11();
int sensorPin01 = A0;    // select the input pin for the potentiometer
int sensorPin02 = A0;    // select the input pin for the potentiometer
extern int g_nID;
extern int ReadID(int &gid);
int init_pin(void );

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
void loop() {
  Serial.println("_running..."); 
//  sensorValue01 = analogRead(sensorPin01);  //读取压力传感器
//  sensorValue02 = analogRead(sensorPin02);  
//  Serial.println(sensorValue01);          
//  Serial.println(sensorValue02); 

//  loop_bmp180();                            //bmp180测试通过
//  loop_dht11();
//  loop_uart();                              //无线模块
  delay(1000);              // delay in between reads for stability
  
}

