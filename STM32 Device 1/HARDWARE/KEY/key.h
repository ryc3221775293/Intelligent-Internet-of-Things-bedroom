#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEK��ӢSTM32������
//������������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   	 


//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define WK_UP PAin(0)	//PA0  WK_UP

#define KEY0  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_4)//��ȡ����0
#define KEY1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_3)//��ȡ����1
#define WK_UP   GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_0)//��ȡ����3(WK_UP) 

#define Y0  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_0) 
#define Y1  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_0) 
#define Y2  GPIO_ReadInputDataBit(GPIOE,GPIO_Pin_1)
#define Y3  GPIO_ReadInputDataBit(GPIOB,GPIO_Pin_1)

#define LD0  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_0)
#define LD1  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_1)
#define LD2  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_2)
#define LD3  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_3)
#define LD4  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_4)
#define LD5  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_5)
#define LD6  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_6)
#define LD7  GPIO_ReadInputDataBit(GPIOD,GPIO_Pin_7)

#define KEY0_PRES 	1	//KEY0����
#define KEY1_PRES	  2	//KEY1����
#define WKUP_PRES   3	//KEY_UP����(��WK_UP/KEY_UP)


void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif