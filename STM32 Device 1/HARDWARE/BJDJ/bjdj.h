#ifndef __bjdj_H
#define __bjdj_H	 
#include "sys.h"

//ULN2003驱动

#define uint unsigned int

void Delay_xms(uint x);//延时函数
void Moto_Init(void);  //步进电机初始化
void Motorcw(int speed);    //步进电机正转函数
void Motorcw1(int speed);   //步进电机1正转函数
void Motorccw(int speed);   //步进电机反转函数
void Motorccw1(int speed);  //步进电机1反转函数
void Motorcw_angle(int angle,int speed);  //步进电机正转角度函数
void Motorcw_angle1(int angle,int speed); //步进电机1正转角度函数
void Motorccw_angle(int angle,int speed); //步进电机反转角度函数
void Motorccw_angle1(int angle,int speed);//步进电机1反转角度函数
void MotorStop(void);  //步进电机停止函数
void MotorStop1(void); //步进电机1停止函数

#endif
