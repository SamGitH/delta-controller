#ifndef MOTION_CONTROL_H_
#define MOTION_CONTROL_H_

#include "stm32h7xx_hal.h"
#include "calculates.h"
#include "uart.h"
#include "_string.h"

#define PORT_SWITCH_LIMIT_A GPIOB
#define PIN_SWITCH_LIMIT_A GPIO_PIN_12

#define PORT_SWITCH_LIMIT_B GPIOB
#define PIN_SWITCH_LIMIT_B GPIO_PIN_13

#define PORT_SWITCH_LIMIT_C GPIOB
#define PIN_SWITCH_LIMIT_C GPIO_PIN_14

void domotion(float x, float y, float z);
void vacuum_on(void);
void vacuum_off (void);
uint8_t soft_limit_ini(void);
void axis_int_stop(uint8_t axis);
uint8_t prepair_move_carr(float pos_mm, float time,  uint8_t axis, float *need_time);
void action_move_carr(uint8_t axis);
uint8_t short_move (float a, float b, float c);
void action_loop();
void set_acceleration(int value);


#endif /* MOTION_CONTROL_H_ */
