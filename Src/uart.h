#ifndef UART_H
#define UART_H

#include "stm32h7xx_hal.h"
#include "_string.h"

void uart_ini(void);
void readATSerialBuff(void);
void printint(int i);
void printint_(int i);
void printstr(char *str);
void printstr_(char *str);
void printstrdma(char *str);
void printfloat(float f);
void printfloat_(float f);
void add_buffer(void);
void parseBuff(char *a);

#endif
