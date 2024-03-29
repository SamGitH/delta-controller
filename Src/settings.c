/*
 * Модуль ответственный за работу с настройками,
 * сохранение и разгрузку настроек и параметров контроллера во flash память
 */
#include "settings.h"

extern UART_HandleTypeDef huart1;
extern float 	l_rod,
zero_C,
z_before_capture,
z_capture,
z_past_capture,
z_before_drop,
capture_line,
detection_line;

extern float 		obj_drop_x[ARRAY_ACTIONS_SIZE],
obj_drop_y[ARRAY_ACTIONS_SIZE],
obj_drop_z[ARRAY_ACTIONS_SIZE];

extern int mode_motion[ARRAY_ACTIONS_SIZE];
extern 	int accel_captur;
extern float zero_x_line;

void temp_filarray()
{
	for (int i=0; i<ARRAY_ACTIONS_SIZE; i++)
	{
		obj_drop_x[i] = i;
		obj_drop_y[i] = i;
		obj_drop_z[i] = i;
		mode_motion[i] = i;
	}
}

void arrtoset()
{
	l_rod = setting[0];
	zero_C = setting[1];
	z_before_capture = setting[2];
	z_capture = setting[3];
	z_past_capture = setting[4];
	detection_line = setting[5];
	accel_captur = (int)setting[6];
	zero_x_line = setting[7];
}

void settoarr()
{
	setting[0] = l_rod;
	setting[1] = zero_C;
	setting[2] = z_before_capture;
	setting[3] = z_capture;
	setting[4] = z_past_capture;
	setting[5] = detection_line;
	setting[6] = (float)accel_captur;
	setting[7] = zero_x_line;
}

void save_data()
{
	flash_erase(FLASH_SECTOR);	 //очищаем весь сектор т.к. он один на все сохраняемые данные
	settoarr();
	save_obj_drop_coord();
	save_settings();
	printstr("data eeprom saved");
}

uint8_t save_obj_drop_coord()
{
	if(save_array(obj_drop_x, ARRAY_ACTIONS_SIZE, A_X_DROPCOORD) == 0) return 0;
	if(save_array(obj_drop_y, ARRAY_ACTIONS_SIZE, A_Y_DROPCOORD) == 0) return 0;
	if(save_array(obj_drop_z, ARRAY_ACTIONS_SIZE, A_Z_DROPCOORD) == 0) return 0;
	if(save_array(mode_motion, ARRAY_ACTIONS_SIZE, A_MODE_MOTION) == 0) return 0;
	return true;
}

void load_obj_drop_coord()
{
	read_array_float(obj_drop_x, ARRAY_ACTIONS_SIZE, A_X_DROPCOORD);
	read_array_float(obj_drop_y, ARRAY_ACTIONS_SIZE, A_Y_DROPCOORD);
	read_array_float(obj_drop_z, ARRAY_ACTIONS_SIZE, A_Z_DROPCOORD);
	read_array_int(mode_motion, ARRAY_ACTIONS_SIZE, A_MODE_MOTION);
}

void save_settings()
{
	if(save_array(setting, SETTING_SIZE, A_SETTINGS) == 0) return 0;
	return 1;
}

void load_settings()
{
	read_array_float(setting, SETTING_SIZE, A_SETTINGS);
	arrtoset();

	for (int i = 0; i<SETTING_SIZE; i++)
	{
		char str[50];
		sprintf(str,"setting: %d,%.3f\r",i,setting[i]);
		printstr_(str);
		if (mode_motion[i] == 2) break;
	}

	printstr("load settings:");
	UART_TX("l_rod: ");
	printfloat(l_rod);
	UART_TX("zero_C: ");
	printfloat(zero_C);
	UART_TX("z_before_capture: ");
	printfloat(z_before_capture);
	UART_TX("z_capture: ");
	printfloat(z_capture);
	UART_TX("z_past_capture: ");
	printfloat(z_past_capture);
	UART_TX("z_before_drop: ");
	printfloat(z_before_drop);
	UART_TX("capture_line: ");
	printfloat(capture_line);
	UART_TX("detection_line: ");
	printfloat(detection_line);
	UART_TX("accel_captur: ");
	printint(accel_captur);
	UART_TX("zero_x_line: ");
	printfloat(zero_x_line);

	load_obj_drop_coord();
	printstr("data loaded");

	for (int i = 0; i<ARRAY_ACTIONS_SIZE; i++)
	{
		char str[50];
		sprintf(str,"step: %d,%.3f,%.3f,%.3f,%d\r",i,obj_drop_x[i],obj_drop_y[i],obj_drop_z[i],mode_motion[i]);
		printstr_(str);
		if (mode_motion[i] == 2) break;
	}
}

void read_table(int n)
{
	char buf[50];
	sprintf(buf,"stp_req %d\r", n+1);
	printstr_(buf);
}
