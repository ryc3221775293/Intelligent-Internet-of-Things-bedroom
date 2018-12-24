#include "bjdj.h"

#define uint unsigned int
	
//�����������ת����1
uint16_t phasecw[4] ={0x0200,0x0100,0x0080,0x0040};// D-C-B-A   
uint16_t phaseccw[4]={0x0040,0x0080,0x0100,0x0200};// A-B-C-D.

//�����������ת����2
uint16_t phasecw1[4] ={0x0800,0x0400,0x0200,0x0100};// D-C-B-A   
uint16_t phaseccw1[4]={0x0100,0x0200,0x0400,0x0800};// A-B-C-D.	
void Delay_xms(uint x)
{
 uint i,j;
 for(i=0;i<x;i++)
  for(j=0;j<112;j++);
}

void Moto_Init(void)
{
	//���1
 GPIO_InitTypeDef GPIO_InitStructure;
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7 | GPIO_Pin_8 | GPIO_Pin_9 ;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOC,&GPIO_InitStructure);
 GPIO_ResetBits(GPIOC,GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 );
// IN4: PC9   d
// IN3: PC8   c
// IN2: PC7   b
// IN1: PC6   a
	
	//���2
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11 ;
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOD,&GPIO_InitStructure);
 GPIO_ResetBits(GPIOD,GPIO_Pin_8 | GPIO_Pin_9 |GPIO_Pin_10 |GPIO_Pin_11 );
// IN4: PD11  d
// IN3: PD10  c
// IN2: PD9   b
// IN1: PD8   a
}

void Motorcw(int speed)  
{  
    uint8_t i;  
  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(GPIOC,phasecw[i]);  
        Delay_xms(speed);  
    }  
}

void Motorcw1(int speed)  
{  
    uint8_t i;  
  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(GPIOD,phasecw1[i]);  
        Delay_xms(speed);  
    }  
}

void Motorccw(int speed)  
{  
    uint8_t i;  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(GPIOC,phaseccw[i]);  
        Delay_xms(speed);  
    }  
}

void Motorccw1(int speed)  
{  
    uint8_t i;  
  
    for(i=0;i<4;i++)  
    {  
        GPIO_Write(GPIOD,phaseccw1[i]);  
        Delay_xms(speed);  
    }  
}

void MotorStop(void)  
{  
//    GPIO_Write(GPIOC,0x0000);  
	GPIO_ResetBits(GPIOC,GPIO_Pin_6 | GPIO_Pin_7 |GPIO_Pin_8 |GPIO_Pin_9 );
}

void MotorStop1(void)  
{  
    GPIO_Write(GPIOD,0x0000);  
}

//����   *һ������*   *�����*  ת0.08789�ȣ����ʵת0.08789*64=5.625�ȣ�����������Ϊ5.625�ȡ���ת��A-B-C-DΪ  *8������*  ����0.08789*8=0.70312�ȡ�����A-B-C-DΪһ�����ڣ���jΪ��Ҫ��ת��angle�Ƕ��������������
void Motorcw_angle(int angle,int speed)
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorcw(speed);
	}
	MotorStop();
}

void Motorcw_angle1(int angle,int speed)
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorcw1(speed);
	}
}

void Motorccw_angle(int angle,int speed)
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorccw(speed);
	}
}

void Motorccw_angle1(int angle,int speed)
{
	int i,j;
	j=(int)(angle/0.70312);
	for(i=0;i<j;i++)
	{
		Motorccw1(speed);
	}
}
