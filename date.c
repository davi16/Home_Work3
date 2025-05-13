//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "date.h"
#include "arrays.h"


void initDate(Date* newDate, char * date)
{
	if (verifyFormat(newDate , date))
	{
		int count = 0;
		char temp[SIZE], * delimiters = "^", * individuals;
		strcpy(temp, date);
		individuals = strtok(temp, delimiters);
		while (individuals)
		{
			switch (count)
			{
			case 0:
				newDate->day = atoi(individuals);
				break;
			case 1:
				newDate->month = atoi(individuals);
				break;
			case 2:
				newDate->year = atoi(individuals);
				break;
			}
			individuals = strtok(NULL, delimiters);
			count++;
		}
		verify(newDate);
	}
}
int verifyFormat(Date* newDate, const char* date)
{
	char new[SIZE];
	for (int i = 0; i < strlen(date);++i)
	{
		switch (i)
		{
		case 0: case 1: case 4: case 5: case 8: case 9: case 10: case 11:
			if (!isdigit(date[i]))
			{
				printf("(1)The date you entered isn't of a good format!\nEnter the date again: ");
				initString(new, sizeof(new));
				initDate(newDate, new);
				return 0;
			}
			break;
		case 2: case 3: case 6: case 7:
			if(date[i] != '^')
			{
				printf("(2)The date you entered isn't of a good format!\nEnter the date again: ");
				initString(new, sizeof(new));
				initDate(newDate, new);
				return 0;
			}
			break;
		default:
			printf("(3)The date you entered isn't of a good format!\nEnter the date again: ");
			initString(new, sizeof(new));
			initDate(newDate, new);
			return 0;
			break;
		}
	}
	return 1;
}
Date* verify(Date * newDate)
{
	char date[SIZE];
	if (newDate->year >= 2024)
	{
		switch (newDate->month)
		{
		case apr: case jun: case sep: case nov:
			if (newDate->day > 30 || newDate->day < 1)
			{
				printf("The value entered for day isn't right for this month!\nEnter the date again: ");
				initString(date, sizeof(date));
				initDate(newDate, date);
				return newDate;
			}
			break;
		case jan: case mar: case may: case jul: case aug: case oct: case dec:
			if (newDate->day > 31 || newDate->day < 1)
			{
				printf("The value entered for day isn't right for this month!\nEnter the date again: ");
				initString(date, sizeof(date));
				initDate(newDate, date);
				return newDate;
			}
			break;
		case feb:
			if (newDate->day > 29 || newDate->day < 1)
			{
				printf("The value entered for day isn't right for this month!\nEnter the date again: ");
				initString(date, sizeof(date));
				initDate(newDate, date);
				return newDate;
			}
			break;
		default:
			printf("The value entered for month isn't right!\nEnter the date again: ");
			initString(date, sizeof(date));
			initDate(newDate, date);
			return newDate;
			break;
		}
		return newDate;
	}
	else {
		printf("The value entered for year isn't right!\nEnter the date again: ");
		initString(date, sizeof(date));
		initDate(newDate, date);
		return newDate;
	}
}
void printDate(const Date* d)
{
	printf("%d/%d/%d", d->day, d->month , d->year);
}