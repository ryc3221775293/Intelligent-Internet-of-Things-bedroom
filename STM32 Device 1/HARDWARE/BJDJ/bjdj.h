#ifndef __bjdj_H
#define __bjdj_H	 
#include "sys.h"

//ULN2003����

#define uint unsigned int

void Delay_xms(uint x);//��ʱ����
void Moto_Init(void);  //���������ʼ��
void Motorcw(int speed);    //���������ת����
void Motorcw1(int speed);   //�������1��ת����
void Motorccw(int speed);   //���������ת����
void Motorccw1(int speed);  //�������1��ת����
void Motorcw_angle(int angle,int speed);  //���������ת�ǶȺ���
void Motorcw_angle1(int angle,int speed); //�������1��ת�ǶȺ���
void Motorccw_angle(int angle,int speed); //���������ת�ǶȺ���
void Motorccw_angle1(int angle,int speed);//�������1��ת�ǶȺ���
void MotorStop(void);  //�������ֹͣ����
void MotorStop1(void); //�������1ֹͣ����

#endif
