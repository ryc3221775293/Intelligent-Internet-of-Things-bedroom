#ifndef __Hcsr04_H
#define __Hcsr04_H 
#include "sys.h"
#define HCSR04_PORT     GPIOA
#define HCSR04_CLK      RCC_APB2Periph_GPIOB
#define HCSR04_TRIG     GPIO_Pin_1
#define HCSR04_ECHO     GPIO_Pin_0

#define TRIG_Send  PAout(1) 
#define ECHO_Reci  PAin(0)


void NVIC_Configuration(void); 
void TIM_Configuration(void); 
void GPIO_Configuration(void); 
void RCC_Configuration(void); 
float Sensor_using(void); 
#endif
