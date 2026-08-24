#include "stm32f10x.h"                  // Device header
#include "Serial.h"
#include "Delay.h"

//定义每个需要的值
//#define WIFIID huawei
//#define WIFIMIMA guoyaodong4518...
//#define DIZHI 192.168.43.1
//#define DUANKOU 9999
//#define USERNAME 66534f1e6bc31504f06c08d5_4518
//#define PASSWORD f91d73ef3ef34446a7c302cef4638ed82b9a0c1e3c7ef1df18494f773119de09

void ESP8266_Init(void)
{
	printf("AT\r\n");
	Delay_ms(20);
	printf("AT+CWMODE=1\r\n");
	Delay_s(1);
	printf("AT+RST\r\n");	
	Delay_s(1);
	printf("AT\r\n");
	Delay_ms(20);
	printf("AT+CWJAP=\"iQOO Neo9S Pro\",\"guoyaodong4518...\"\r\n");
	Delay_s(3);
	printf("AT+CIPMUX=0\r\n");
	Delay_ms(20);
	printf("AT+CIPMODE=1\r\n");
	Delay_ms(20);
	printf("AT+CIPSTART=\"TCP\",\"192.168.43.1\",9999\r\n");
	Delay_s(1);
	printf("AT+CIPSEND\r\n");
}

void ESP8266_Huaweiyun_Init(void)
{
	printf("AT+CWMODE=1\r\n");
	Delay_ms(200);
	printf("AT+RST\r\n");	
	Delay_ms(100);
	printf("AT+CWJAP=\"iQOO Neo9S Pro\",\"guoyaodong4518...\"\r\n");
	Delay_ms(300);
	printf("AT+MQTTUSERCFG=0,1,\"NULL\",\"667f82db6bc31504f0711afb_ximenzi\",\"04987be5d5dbc8408cc80b23709eb26de658a18c31fe23749011df7d27b61d32\",0,0,\"\"\r\n");
	Delay_ms(300);
	printf("AT+MQTTCLIENTID=0,\"667f82db6bc31504f0711afb_ximenzi_0_0_2024062903\"\r\n");
	Delay_ms(500);
	printf("AT+MQTTCONN=0,\"33af8f4e16.st1.iotda-device.cn-north-4.myhuaweicloud.com\",1883,1\r\n");
	Delay_ms(200);
	printf("AT+MQTTSUB=\"$oc/devices/ximenzi/sys/properties/report\",1\r\n");
	Delay_ms(100);
}

