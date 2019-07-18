#ifndef SETTINGS_H_

#define SETTINGS_H_
#define UART_TXD(strstr) HAL_UART_Transmit_DMA(&huart1,(uint8_t*)strstr  ,length(strstr))
#define UART_TX(strstr) HAL_UART_Transmit(&huart1,(uint8_t*)strstr  ,length(strstr),0xFFFF)
#define SETTING_SIZE 7

#include "stm32h7xx_hal.h"
#include "flash.h"
#include "uart.h"
#include <stdio.h>
#include "obj_control.h"

#define A_L_ROD A_FL1 //adress lrod = address float #1 etc
#define A_ZEROC A_FL2
#define A_ZBEFORE_CAPTURE A_FL3
#define A_ZCAPTURE A_FL4
#define A_ZPAST_CAPTURE A_FL5
#define A_ZBEFORE_DROP A_FL6
#define A_CAPTURE_LINE A_FL7
#define A_DETECTION_LINE A_FL8
#define A_ZERO_X_LINE A_FL9
#define A_COUNT_DROP_POS A_FL11
#define A_ACCEL_CAPTURED A_FL10

float setting[SETTING_SIZE];

void temp_filarray();
void arrtoset();
void save_data();
void read_table(int n);
uint8_t save_obj_drop_coord();
void load_obj_drop_coord();
void load_settings();
void save_settings();

#endif /* SETTINGS_H_ */
