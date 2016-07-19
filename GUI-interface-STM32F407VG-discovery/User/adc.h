#ifndef __ADC__
#define __ADC__

#include "stm32f4xx.h"

void ADC_Configuration(void);
int media(int *vect,int vals);
uint16_t Get_ADC_Value(uint8_t Channel);
void ADC1_CH6_DMA_Config(void);


#endif