#ifndef PULSE_CONTROL_H_

#define PULSE_CONTROL_H_

#include "stm32h7xx_hal.h"
#include "stm32h7xx_it.h"

#define STEP_PORT_A GPIOB
#define STEP_PIN_A GPIO_PIN_14
#define DIR_PORT_A GPIOE
#define DIR_PIN_A GPIO_PIN_8
#define STEP_PORT_B GPIOB
#define STEP_PIN_B GPIO_PIN_7
#define DIR_PORT_B GPIOE
#define DIR_PIN_B GPIO_PIN_12
#define STEP_PORT_C GPIOB
#define STEP_PIN_C GPIO_PIN_0
#define DIR_PORT_C GPIOE
#define DIR_PIN_C GPIO_PIN_10
#define SYS_CLOCK 240000000 //выставляется настройкой - частота тактирования таймеров

void timers_ini(void);

void axis_a_timer(void);

void axis_a_motion_ini(
		int pulses,
		float max_speed,
		float min_speed,
		float accel,
		float brake,
		float  time_to_start_brake,
		float	motion_time,
		uint8_t direction
);

void axis_b_timer(void);

void axis_b_motion_ini(
		int pulses,
		float max_speed,
		float min_speed,
		float accel,
		float brake,
		float  time_to_start_brake,
		float	motion_time,
		uint8_t direction
);

void axis_c_timer(void);

void axis_c_motion_ini(
		int pulses,
		float max_speed,
		float min_speed,
		float accel,
		float brake,
		float  time_to_start_brake,
		float	motion_time,
		uint8_t direction
);

#endif /* PULSE_CONTROL_H_ */
