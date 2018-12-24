#include "sys.h"
#include "delay.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "beep.h"	  
#include "malloc.h"   
#include "sdio_sdcard.h"       
#include "ff.h"  
#include "exfuns.h"    
#include "usart2.h"
#include "AS608.h"
#include "timer.h"
#include "led.h"
#include "oled.h"
#include "MAX30100.h"
#include "MAX30100_PulseOximeter.h"
#include "MAX30100_SpO2Calculator.h"
#include "MAX30100_Filters.h"
#include "timer3.h"
#include "myiic.h"
#include "hcsr04.h"
#define usart2_baund  57600//串口2波特率，根据指纹模块波特率更改

SysPara AS608Para;//指纹模块AS608参数
u16 ValidN;//模块内有效指纹个数
u8** kbd_tbl;


int main(void)
{
	vu8 key=0;	
	u8 ensure;
	char *str;	
	float result=0;
	int distance;
	int hcsr04 = 0;
	int max30100 = 0;
	int hcsr04flag = 0;
	int max30100flag = 0;
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//设置系统中断优先级分组2
	delay_init();  	//初始化延时函数
	uart_init(115200);	//初始化串口1波特率为115200，用于支持USMART
	usart2_init(usart2_baund);//初始化串口2,用于与指纹模块通讯
	PS_StaGPIO_Init();	//初始化FR读状态引脚
	BEEP_Init();  			//初始化蜂鸣器
	KEY_Init();					//按键初始化 	
	LED_Init();
	TIM3_Int_Init(100-1,720-1);//??1ms??
	IIC_Init();	
	SPO2_Init();
	NVIC_Configuration(); 
  GPIO_Configuration(); 
  TIM_Configuration(); 
	OLED_Init();			//初始化OLED
	OLED_ShowString(64,40,"Spo2:",16);
	OLED_ShowString(0,40,"Rate:",16);
	OLED_ShowChar(120,40,'%',16,1);
	OLED_ShowString(0,16,"Heiht:",16);
	OLED_ShowChar(96,16,'.',16,1);
	OLED_ShowString(112,16,"cm",16);
	OLED_Refresh_Gram();
	my_mem_init(SRAMIN);		//初始化内部内存池 
	exfuns_init();			//为fatfs相关变量申请内存  
 	f_mount(fs[1],"1:",1);  //挂载FLASH.
	
	/*加载指纹识别实验界面*/
	printf("\r\nAS608指纹识别模块测试程序\r\n");
	printf("\r\n与AS608模块握手....\r\n");
	while(PS_HandShake(&AS608Addr))//与AS608模块握手
	{
		delay_ms(400);
		printf("\r\n未检测到模块!!!\r\n");
		delay_ms(800);
		printf("\r\n尝试连接模块...\r\n");
	}
	printf("\r\n通讯成功!!!\r\n");
	str=mymalloc(SRAMIN,30);
	sprintf(str,"波特率:%d   地址:%x",usart2_baund,AS608Addr);
	ensure=PS_ValidTempleteNum(&ValidN);//读库指纹个数
	if(ensure!=0x00)
		ShowErrMessage(ensure);//显示确认码错误信息	
	ensure=PS_ReadSysPara(&AS608Para);  //读参数 
	if(ensure==0x00)
	{
		mymemset(str,0,50);
		sprintf(str,"库容量:%d     对比等级: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
	}
	else
		ShowErrMessage(ensure);	
	myfree(SRAMIN,str);
	LED0=1;
	while(1)
	{
		//printf("\r\nY0:%d\r\n",Y0);
		key=KEY_Scan(0);	//得到键值
		if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//控制蜂鸣器
					BEEP=!BEEP;
					break; 
				case KEY1_PRES:	//控制LED1翻转	 
					hcsr04 = !hcsr04;
					hcsr04flag = 0;
					break;
				case KEY0_PRES:	//同时控制LED0,LED1翻转 
					max30100 = !max30100;
					max30100flag = 0;
					break;
			}
		}else delay_ms(10); 
		//printf("\r\nhcsr04:%d\r\n",hcsr04);
		//printf("\r\nmax30100:%d\r\n",max30100);
		if(max30100==1)
		{
				max30100flag++;
				POupdate();//??FIFO?? ???? ???? 
		}
		if(max30100flag == 1)
		{
				LD1 = 0;
				delay_ms(100);
				LD1 = 1;
		}
		if(hcsr04==1)
		{
			hcsr04flag++;
			result=Sensor_using();
			distance = (int)(result);
			//printf("\r\nDistance:%d\r\n",distance);
			OLED_ShowNum(48,16,distance/10,6,16);
			OLED_ShowNum(104,16,distance%10,1,16);
			OLED_Refresh_Gram();
		}
		if(hcsr04flag == 1)
		{
				LD0 = 0;
				delay_ms(100);
				LD0 = 1;
		}
		if(PS_Sta)	 //检测PS_Sta状态，如果有手指按下
		{
			press_FR();//刷指纹			
		}				 
	} 	
}










