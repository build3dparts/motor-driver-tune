#ifndef __UARTLIB_H
#define __UARTLIB_H

#include <stdio.h>
#include "stdint.h"

#ifdef __cplusplus
 extern "C" {
#endif


void UART_LowLevel_Init(void);
void UART_Send(uint8_t *buf);
void UART_Receive(uint8_t *buf, uint32_t cnt);

#ifdef __cplusplus
}
#endif
#endif //__UARTLIB_H
