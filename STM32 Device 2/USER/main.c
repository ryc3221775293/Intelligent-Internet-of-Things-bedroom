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
#define usart2_baund  57600//����2�����ʣ�����ָ��ģ�鲨���ʸ���

SysPara AS608Para;//ָ��ģ��AS608����
u16 ValidN;//ģ������Чָ�Ƹ���
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
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);//����ϵͳ�ж����ȼ�����2
	delay_init();  	//��ʼ����ʱ����
	uart_init(115200);	//��ʼ������1������Ϊ115200������֧��USMART
	usart2_init(usart2_baund);//��ʼ������2,������ָ��ģ��ͨѶ
	PS_StaGPIO_Init();	//��ʼ��FR��״̬����
	BEEP_Init();  			//��ʼ��������
	KEY_Init();					//������ʼ�� 	
	LED_Init();
	TIM3_Int_Init(100-1,720-1);//??1ms??
	IIC_Init();	
	SPO2_Init();
	NVIC_Configuration(); 
  GPIO_Configuration(); 
  TIM_Configuration(); 
	OLED_Init();			//��ʼ��OLED
	OLED_ShowString(64,40,"Spo2:",16);
	OLED_ShowString(0,40,"Rate:",16);
	OLED_ShowChar(120,40,'%',16,1);
	OLED_ShowString(0,16,"Heiht:",16);
	OLED_ShowChar(96,16,'.',16,1);
	OLED_ShowString(112,16,"cm",16);
	OLED_Refresh_Gram();
	my_mem_init(SRAMIN);		//��ʼ���ڲ��ڴ�� 
	exfuns_init();			//Ϊfatfs��ر��������ڴ�  
 	f_mount(fs[1],"1:",1);  //����FLASH.
	
	/*����ָ��ʶ��ʵ�����*/
	printf("\r\nAS608ָ��ʶ��ģ����Գ���\r\n");
	printf("\r\n��AS608ģ������....\r\n");
	while(PS_HandShake(&AS608Addr))//��AS608ģ������
	{
		delay_ms(400);
		printf("\r\nδ��⵽ģ��!!!\r\n");
		delay_ms(800);
		printf("\r\n��������ģ��...\r\n");
	}
	printf("\r\nͨѶ�ɹ�!!!\r\n");
	str=mymalloc(SRAMIN,30);
	sprintf(str,"������:%d   ��ַ:%x",usart2_baund,AS608Addr);
	ensure=PS_ValidTempleteNum(&ValidN);//����ָ�Ƹ���
	if(ensure!=0x00)
		ShowErrMessage(ensure);//��ʾȷ���������Ϣ	
	ensure=PS_ReadSysPara(&AS608Para);  //������ 
	if(ensure==0x00)
	{
		mymemset(str,0,50);
		sprintf(str,"������:%d     �Աȵȼ�: %d",AS608Para.PS_max-ValidN,AS608Para.PS_level);
	}
	else
		ShowErrMessage(ensure);	
	myfree(SRAMIN,str);
	LED0=1;
	while(1)
	{
		//printf("\r\nY0:%d\r\n",Y0);
		key=KEY_Scan(0);	//�õ���ֵ
		if(key)
		{						   
			switch(key)
			{				 
				case WKUP_PRES:	//���Ʒ�����
					BEEP=!BEEP;
					break; 
				case KEY1_PRES:	//����LED1��ת	 
					hcsr04 = !hcsr04;
					hcsr04flag = 0;
					break;
				case KEY0_PRES:	//ͬʱ����LED0,LED1��ת 
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
		if(PS_Sta)	 //���PS_Sta״̬���������ָ����
		{
			press_FR();//ˢָ��			
		}				 
	} 	
}










