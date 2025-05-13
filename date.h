//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __DATEE__
#define __DATEE__
#define DAY 2
#define MONTH 2
#define YEAR 4
#define SYMBOL 2
typedef enum { null , jan, feb, mar, apr, may, jun, jul, aug , sep, oct, nov, dec } month_type;
typedef struct
{
	int day;
	int month;
	int year;
}Date;


void initDate(Date* newDate, char* date);
int verifyFormat(Date* newDate,const char* date);
void printDate(const Date* d);
Date* verify(Date* newDate);
#endif
