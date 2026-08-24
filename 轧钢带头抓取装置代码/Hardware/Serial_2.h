#ifndef __SERIAL_2_H
#define __SERIAL_2_H

#include <stdio.h>

void Serial_2_Init(void);
void Serial_2_SendByte(uint8_t Byte);
void Serial_2_SendArray(uint8_t *Array, uint16_t Length);
void Serial_2_SendString(char *String);
void Serial_2_SendNumber(uint32_t Number, uint8_t Length);
void Serial_2_Printf(char *format, ...);

uint8_t Serial_2_GetRxFlag(void);
uint8_t Serial_2_GetRxData(void);

#endif
