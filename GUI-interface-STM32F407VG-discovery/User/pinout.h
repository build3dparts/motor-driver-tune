#ifndef __INPUT_PINOUT__
#define __INPUT_PINOUT__

#include "stm32f4xx.h"

//output PortC Pins----------------------------------------------
#define OUTPUT_Port									GPIOC
#define OUTPUT_RCC_AHBPeriph				RCC_AHB1Periph_GPIOC
#define RELEU1                      GPIO_Pin_1              //Releu 1
#define BECPRESA  									GPIO_Pin_2              //Releu 2
#define EM_Pin                      GPIO_Pin_3              //Releu 3
#define SPAN_Pin                    GPIO_Pin_4              //Releu 6
#define EM_P_PULL_Pin               GPIO_Pin_13             //Releu 4
#define EM_P_PUSH_Pin               GPIO_Pin_14             //Releu 5
#define RELEU7                      GPIO_Pin_15             //alt releu

#define OUTPUT_Port2								GPIOB
#define OUTPUT_RCC_AHBPeriph2				RCC_AHB1Periph_GPIOB
#define PLATBAND_Pin                GPIO_Pin_8             //alt releu
#define PRESA_Pin                   GPIO_Pin_9             //alt releu
//--------------------------------------------------------------

//input PORTF Pins------------------------------------------------
#define INPUT_Port									GPIOF
#define INPUT_RCC_AHBPeriph					RCC_AHB1Periph_GPIOF
#define SENSOUT_Pin                 GPIO_Pin_3              //Releu 10
#define ROTATII_Pin									GPIO_Pin_5              //Releu 12
#define ENCODER_Pin                 GPIO_Pin_6              //Releu 13
#define RELEU11     			    			GPIO_Pin_8              //Releu 11
//#define ENCODER_Pin               GPIO_Pin_9              //Releu 14
//-----------------------------------------------------------------

#ifdef __cplusplus
extern "C" {
#endif

void PeripheralInit(void);
void UNIVERSAL_STOP(void);

void StartPlatBand(void);
void StartPresa(void);
void StartSPAN(void);
void StartEM(void);
void Start_PULL_EM(void);
void Start_PUSH_EM(void);

void StopPlatBand(void);
void StopPresa(void);
void StopSPAN(void);
void StopEM(void);
void Stop_PULL_EM(void);
void Stop_PUSH_EM(void);

int ReadSenzor(void); 
int ReadPresa(void);

void EXTILine0_Config(void);
void EXTILine1_Config(void);
void EXTILine2_Config(void);

void EXTILine13_Config(void);
void EXTILine14_Config(void);
void EXTILine15_Config(void);   

void Handle_ENCODER(void);
int ReadPresa(void);

extern int enc_ok;

#ifdef __cplusplus
}
#endif

#endif