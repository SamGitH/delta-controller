/*==========================
 * Для MV
Для подключения этого надо:
- после обработчика прерывания в stm32f3xx_it.c вставть функцию add_buffer();
- проиницировать uart_ini();
- прописать функцию парсинга
В противном случае ничего не заведется - проверено
===============================*/

#include "_string.h"
#include "uart2.h"
#include "stm32h7xx_hal.h"

#define PARSE_VOID_SCRIPT UART_TX(buff);// здесь хранится функция, в которую передаестя сообщения для парсинга

/* Для обнуления буфера при заполеннии файл stm32f1xx_hal_uart.c после 1612 строчки(huart->State = HAL_UART_STATE_READY;)
в функции static void UART_DMAReceiveCplt(DMA_HandleTypeDef *hdma)  вставить строчки:
HAL_UART_DMAStop(huart);
uart_ini();
и подключить заголовочный файл uart.h
 */

#define UART_TXD(strstr) HAL_UART_Transmit_DMA(&huart2,(uint8_t*)strstr  ,length(strstr))
#define UART_TX(strstr) HAL_UART_Transmit(&huart2,(uint8_t*)strstr  ,length(strstr),0xFFFF)

extern UART_HandleTypeDef huart2;

uint8_t readATSerialBuff_flag_u2 = 1;

static char serial_char[2];
static char serial_buff[UART1_BUFSIZE];
static char * a_serial_write_buff;
static char * a_serial_read_buff;
static int write_char_counter=0;
static int read_char_counter=0;
static int buff_chars=0;
static char parsing_buff[UART1_BUFSIZE];
static char *a_parsing_buff;

void uart_ini_u2(void)
{
	a_serial_write_buff = serial_buff;
	write_char_counter=0;
	a_serial_read_buff = serial_buff;
	read_char_counter=0;
	clearArray(serial_buff,UART1_BUFSIZE);
	a_parsing_buff = parsing_buff;
	HAL_UART_Receive_IT(&huart2,(uint8_t*) serial_char,1);
}

void add_buffer_u2()
{
	if(write_char_counter==UART1_BUFSIZE)
	{
		write_char_counter=0;
		a_serial_write_buff = serial_buff;
	}

	if(buff_chars < UART1_BUFSIZE)
	{
		*a_serial_write_buff = serial_char[0];a_serial_write_buff++;
		buff_chars++;
		write_char_counter++;
		HAL_UART_Receive_IT(&huart2,(uint8_t*) serial_char,1);
	}
}

char read_buff_char_u2()
{
	char char_out;
	if (read_char_counter==UART1_BUFSIZE)
	{
		read_char_counter=0;
		a_serial_read_buff = serial_buff;
	}

	if (buff_chars>=0)
	{
		buff_chars--;
		char_out = *a_serial_read_buff;
		a_serial_read_buff++;
		read_char_counter++;
	}

	return char_out;
}

void readATSerialBuff_u2(void)
{
	if (readATSerialBuff_flag_u2 == false) return;
	static int counter_chars;

	if (buff_chars>0)
	{
		counter_chars++;
		*a_parsing_buff = read_buff_char_u2();

		if (*a_parsing_buff == '\r')
		{
			parseBuff_u2(parsing_buff);
			clearArray(parsing_buff, UART1_BUFSIZE);
			a_parsing_buff = parsing_buff;
			counter_chars=0;
			return;
		}
		a_parsing_buff++;
	}
}

void parseBuff_u2(char *a)
{
	int cycle_parses = countOf(parsing_buff,'\r');

	for (int i=0; i<cycle_parses; i++)
	{
		int index_end_msg = indexOf(parsing_buff,'\r');
		if (index_end_msg != 0)
		{
			char buff[index_end_msg];clearArray(buff,index_end_msg);
			substring(parsing_buff,buff,0,index_end_msg);
			if (length(buff)>0)
			{
				//===========Здесь обрабатываем сообщения , лежащие в buff
				PARSE_VOID_SCRIPT
				//===================================
			}
		}
		substring(parsing_buff,parsing_buff,index_end_msg+1,length(parsing_buff));
	}
}

void printint_u2(int i)
{
	char buff[10];
	intToStr(i,buff);
	UART_TX(buff);
	UART_TX("\r\n");
}

void printstr_u2(char *str)
{
	UART_TX(str);
	UART_TX("\r\n");
}

void printfloat_u2(float f)
{
	char buff[12];
	ftoa(f,buff,3);
	UART_TX(buff);
	UART_TX("\r\n");
}
