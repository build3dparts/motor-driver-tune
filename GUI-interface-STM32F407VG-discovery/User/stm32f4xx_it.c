#include "stm32f4xx_it.h"

void NMI_Handler(void)
{
}

void HardFault_Handler(void)
{
  while (1)   {   }
}

void MemManage_Handler(void)
{
  while (1)  {   }
}

void BusFault_Handler(void)
{
  while (1)    {     }
}

void UsageFault_Handler(void)
{
  while (1)    {   }
}

void SVC_Handler(void)
{
}

void DebugMon_Handler(void)
{
}

void PendSV_Handler(void)
{
}

extern void TimingDelay_Decrement(void);
void SysTick_Handler(void)
{
	TimingDelay_Decrement();
}

//extern void Events_TimerIRQ(void);
void TIM3_IRQHandler(void)
{
    //Events_TimerIRQ();
}

//-------------------------------------------DREAPTA------------------------------------------
void EXTI0_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line0) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line0);
  }
}

void EXTI1_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line1) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line1);
  }
}

void EXTI2_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line2) != RESET)
  {	
    EXTI_ClearITPendingBit(EXTI_Line2);
  }
}

//-----------------------------------------STANGA------------------------------------------------------
void EXTI15_10_IRQHandler(void)
{
  if(EXTI_GetITStatus(EXTI_Line13) != RESET)
  {
    EXTI_ClearITPendingBit(EXTI_Line13);
  }
  if(EXTI_GetITStatus(EXTI_Line14) != RESET)
  {	
    EXTI_ClearITPendingBit(EXTI_Line14);
  }	
  if(EXTI_GetITStatus(EXTI_Line15) != RESET)
  {		
    EXTI_ClearITPendingBit(EXTI_Line15);
  }		
}

extern char buf[100];
extern int cidx;
void USART2_IRQHandler(void)
{
    /*if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET)
    {
        if((char)USART_ReceiveData(USART2) == 't')
        {
            USART_SendData(USART2, 'T');
            //while(USART_GetFlagStatus(USART1, USART_FLAG_TXE) == RESET){}
        }
    }*/
		if(USART_GetITStatus(USART2, USART_IT_RXNE) != RESET){
				while (!(USART2->SR & USART_SR_RXNE)) {};
				buf[cidx++]=USART2->DR;		
		}
}   
