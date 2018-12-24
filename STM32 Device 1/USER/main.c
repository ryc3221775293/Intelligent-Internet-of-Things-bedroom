#include "led.h"
#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"
#include "pwm.h"
#include "beep.h"
#include "rc522.h"
#include "dht11.h" 
#include "adc.h"
#include "lsens.h"
#include "bjdj.h"
#include "audio.h"
#include "timer.h"
#include "usart3.h"
#include "gizwits_product.h" 
dataPoint_t currentDataPoint;
u8 wifi_sta=0;
void Gizwits_Init(void)
{	
	TIM3_Int_Init(9,7199);//1MS????
    usart3_init(9600);//WIFI???
	memset((uint8_t*)&currentDataPoint, 0, sizeof(dataPoint_t));//??????????
	gizwitsInit();//??????
}
 int main(void)
 {	 
	u8 temperature;  	    
	u8 humidity;
	u8 adcx;
	u16 adcxx;
	float temp;
	u8 smog;
	int key=0;
	extern u8 AUDIO_SECOPEN[6];
	u8 AUDIO_BUF[6] = {0xAA, 0x07, 0x02, 0x00, 0x07, 0xBA};
	u8 AUDIO_COPY[6] = {0xAA, 0x07, 0x02, 0x00, 0x02, 0xB5};
	extern u8 AUDIO_OPENLIGHT[6];
	extern u8 AUDIO_CLOSELIGHT[6];
	extern u8 AUDIO_OPEN[6];
	u8 AUDIO_PLAYME[6] = {0xAA, 0x07, 0x02, 0x00, 0x06, 0xB9};
	u8 AUDIO_PLAYSONG[6] = {0xAA, 0x07, 0x02, 0x00, 0x10, 0xC3};
	u8 AUDIO_PLAYMAX30100[6] = {0xAA, 0x07, 0x02, 0x00, 0x11, 0xC4};
	u8 AUDIO_PLAYHCSR04[6] = {0xAA, 0x07, 0x02, 0x00, 0x0E, 0xC1};
	u8 AUDIO_PLAYRATE[6] = {0xAA, 0x07, 0x02, 0x00, 0x08, 0xBB};
	extern u8 AUDIO_OPENFAN[6];
	extern u8 AUDIO_CLOSEFAN[6];
	delay_init();	    	  
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	uart_init(9600);
	Gizwits_Init();         //?????	
 	LED_Init();
	KEY_Init();          //按键初始化	
	InitRc522();				//初始化射频卡模块
	BEEP_Init();
	DHT11_Init();
	Lsens_Init();
	Adc_Init();
	TIM2_Init();
	ServoInit();
	Moto_Init();
	AUDIO_VOL();
	AUDIO_PLAY(AUDIO_BUF);
  delay_ms(500);
	printf("--------IOT-DHT11----------\r\n");
	printf("KEY1:AirLink????\t KEY_UP:??\r\n\r\n");
	    while(1)
   {  
			adcxx=Get_Adc_Average(ADC_Channel_1,10);
			temp=(float)adcxx*(3.3/4096);
			smog = (int)(temp*10);
			DHT11_Read_Data(&temperature,&humidity);
			adcx=Lsens_Get_Val();
			currentDataPoint.valueTemperature = temperature;//Add Sensor Data Collection
			currentDataPoint.valueHumidity = humidity;//Add Sensor Data Collection
			currentDataPoint.valueLight = adcx;//Add Sensor Data Collection
			currentDataPoint.valueAir = smog;//Add Sensor Data Collection
			gizwitsHandle((dataPoint_t *)&currentDataPoint);//????
			RC522_Handel();
		 if(LD0 == 0)
		 {
				AUDIO_PLAY(AUDIO_COPY);
		 }
		 if(LD1 == 0)
		 {
				LED0 = 0;
				AUDIO_PLAY(AUDIO_OPENLIGHT);
		 }
		 if(LD2 == 0)
		 {
				LED0 = 1;
				AUDIO_PLAY(AUDIO_CLOSELIGHT);
		 }
		 if(LD3 == 0)
		 {
				Open();
				AUDIO_PLAY(AUDIO_OPEN);
				delay_ms(1000);
				Close();
		 }
		 if(LD4 == 0)
		 {
				AUDIO_PLAY(AUDIO_PLAYME);			
		 }
		 if(LD5 == 0)
		 {
				LED1 = 0;
				AUDIO_PLAY(AUDIO_OPENFAN);
		 }
		 if(LD6 == 0)
		 {
				LED1 = 1;
				AUDIO_PLAY(AUDIO_CLOSEFAN);
		 }
		 if(LD7 == 0)
		 {
				AUDIO_PLAY(AUDIO_PLAYSONG);			
		 }
		 if(Y1 == 0)
		 {
				AUDIO_PLAY(AUDIO_PLAYMAX30100);			
		 }
		 if(Y2 == 0)
		 {
				AUDIO_PLAY(AUDIO_PLAYHCSR04);			
		 }
		 if(Y3 == 0)
		 {
				AUDIO_PLAY(AUDIO_PLAYRATE);			
		 }
		 if(Y0==0)
		 {
				Motorcw_angle(90,500);
				AUDIO_PLAY(AUDIO_SECOPEN);
		 }
			key = KEY_Scan(0);
			if(key==KEY1_PRES)//KEY1??
			{
				printf("WIFI??AirLink????\r\n");
				gizwitsSetMode(WIFI_AIRLINK_MODE);//Air-link????
			}			
			if(key==WKUP_PRES)//KEY_UP??
			{  
				printf("WIFI??,???????\r\n");
				gizwitsSetMode(WIFI_RESET_MODE);//WIFI??
				wifi_sta=0;//??wifi???
			}
   }

 }

