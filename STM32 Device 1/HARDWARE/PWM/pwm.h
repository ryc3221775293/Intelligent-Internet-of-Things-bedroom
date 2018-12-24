#ifndef __PWM_H
#define __PWM_H
#include "sys.h"

//¶æ»ú¿ØÖÆIO PA0
#define Servo_PIN         GPIO_Pin_0
#define Servo_GPIO        GPIOA
#define Servo_SET         GPIO_SetBits(Servo_GPIO , Servo_PIN)
#define Servo_RESET       GPIO_ResetBits(Servo_GPIO , Servo_PIN)
void DuojiMid(void);
void DuojiRight(void);
void DuojiLeft(void);
void ServoInit(void);
void TIM2_Init(void);
void Open(void);
void Close(void);
#endif
