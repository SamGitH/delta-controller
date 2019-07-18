#ifndef SERIAL_INTERFACE_H_
#define SERIAL_INTERFACE_H_

#include "main_task.h"
#include "libs/_string.h"
#include "calculates.h"
#include "motion_control.h"
#include "uart.h"
#include "obj_control.h"
#include "settings.h"

#define BP_TEST 1
#define BP_ERROR -1
#define SERIAL_BUFSIZE 128

void exec_comm(void);
void parse_commands (char *buff_str);
void parse_commands_machinevision (char *buff_str);
void msg_agent();

#endif /* SERIAL_INTERFACE_H_ */
