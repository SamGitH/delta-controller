#ifndef STRING_H_
#define STRING_H_

#include <stdlib.h>
#include "stdbool.h"

#define MAX_PRECISION	(10)

static const double rounders[MAX_PRECISION + 1] =
{
		0.5,				// 0
		0.05,				// 1
		0.005,				// 2
		0.0005,				// 3
		0.00005,			// 4
		0.000005,			// 5
		0.0000005,			// 6
		0.00000005,			// 7
		0.000000005,		// 8
		0.0000000005,		// 9
		0.00000000005		// 10
};

int indexOf(char *a,char findingchar);
void clearArray(char*a,int n);
void copy(char*a,char*b);
int length(char *a);
char * concat(char*a,char*b,char*c); //a первая строка, b - вторая, c - результат
char * substring(char *a,char *c,int start, int ends);
char * intToStr(int myint, char *a);
int lastIndexOf(char *a,char findchar);
int countOf(char *a,char chr);
char * trimChar(char*a,char*c,char chr);
bool startsWith (char *a,char *b );
void addChar(char *a, char*b, char c);
char * crypto_substring(char *a,char *c,int start, int ends);
char * crypto_concat(char*a,char*b,char*c, int n_start, int n_chars); //n - количество символов присоединения
int indexOfCount(char *a,char findchar, int k);
long int toInt(char *a);
int indexOfStr(char *a, char *b);
char * ftoa(double f, char * buf, int precision);

#endif /* STRING_H_ */
