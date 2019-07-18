#ifndef OBJ_CONTROL_H_
#define OBJ_CONTROL_H_

#include "uart.h"
#include "stm32h7xx_hal.h"
#include "calculates.h"
#include "motion_control.h"
#include <stdio.h>

#define N_OBJ 25
#define ARRAY_ACTIONS_SIZE 300 //800 - максимум

void reset_seq_steps();
void translate_step(int n);
void do_demo(int state);
void add_object(float x, float y);
void obj_action(int i);
void encoder_pulce();
void put_obj();

#endif /* OBJ_CONTROL_H_ */
