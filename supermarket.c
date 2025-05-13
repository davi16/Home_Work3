//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "supermarketManager.h"
#include "arrays.h"
#include "address.h"



void initSuperMarket(Supermarket* s)
{
	printf("Enter supermarket branch name:\n ");
	initString(s->name,sizeof(s->name));
	while (findSupermarketByNameOrCode(s->name, -1))
	{
		printf("The name already exists, Try again: ");
		initString(s->name, sizeof(s->name));
	}
	printf("Enter supermarket branch address:\n ");
	initAddress(s->address);
	printf("Enter supermarket code (5 numbers):\n ");
	s->code = initCode(5);

}
void printSuperMarket(const Supermarket* s)
{
	printf("Name: %s, Address:%s, Code: %d\n", &s->name, &s->address, s->code);
}

int isSameSupermaket(const Supermarket* s1, const Supermarket* s2)
{
	if (strcmp(s1->name, s2->name) != 0)
		return 0;
	if (strcmp(s1->address, s2->address) != 0)
		return 0;
	if (s1->code != s2->code)
		return 0;
	return 1;
}
int isSupermarketName(const Supermarket* s, const char name[])
{
	if(compareTwoStringsNoCaseSensetive(s->name,name))
		return 1;
	return 0;
}
int isSupermarketCode(const Supermarket* s, const int code)
{
	if (s->code != code)
		return 0;
	return 1;
}
