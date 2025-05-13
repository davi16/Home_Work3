//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "arrays.h"

char* initString(char* buf, int size)
{
	//function inits string and replaces \n with \0 (end of string)
	if (buf != NULL && size > 0)
	{
		if (fgets(buf, size, stdin))
		{
			buf[strcspn(buf, "\n")] = '\0';
			return buf;
		}
		*buf = '\0';
	}
	return NULL;
}


int initCode(int max)
{
	//This function inits a code from user and checking if the number of digits in it matches max value
	int code, temp, counter = 0;
	(void)scanf("%d", &code);
	while (getchar() != '\n') {};//clearing buffer
	temp = code;
	while (temp != 0)
	{
		temp /= 10;
		counter++;
	}
	if (counter != max)
	{
		printf("The code must consist of %d digits! Try again ", max);
		return initCode(max);
	}
	return code;
}

int checkProductCode(char* code)
{
	if (strlen(code) != 6)
	{
		return 0;
	}
	for (int i = 0; i < strlen(code); ++i)
	{
		if (!isdigit(code[i]))
		{
			return 0;
		}
	}
	return 1;
}

int compareTwoStringsNoCaseSensetive(const char s1[], const char s2[])
{
	int i = 0;
	if (s1 == NULL || s2 == NULL)
		return 0;
	if (strlen(s1) != strlen(s2))
		return 0;
	while (s1[i])
	{
		if (tolower(s1[i]) != tolower(s2[i]))
			return 0;
		i++;
	}
	return 1;
}


void printGeneralArrayFunction(const void* arr, int size, size_t typeSize, void f(const void* element))
{
	int i;
	for (i = 0; i < size; i++)
	{
		printf("%d: ", (i + 1));
		f((char*)arr + i * typeSize);
	}
}





