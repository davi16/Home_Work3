//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "supplierManager.h"
#include "productManager.h"
#include "arrays.h"


void initSupplier(Supplier* s)
{
	printf("Enter supplier name:\n ");
	initString(s->name, sizeof(s->name));
	while (findSupplierByNameOrCode(s->name, -1))
	{
		printf("The name already exists, Try again ");
		initString(s->name, sizeof(s->name));
	}
	printf("Enter supplier code (6 numbers):\n ");
	s->code = initCode(6);
}

int readSuppFromFile(FILE* fl, Supplier* s)
{
	while (fgetc(fl) != '\n') {};//clearing buffer
	char temp[SIZE] = { 0 };
	if (!fgets(temp, sizeof(temp), fl))
		return 0;
	temp[strcspn(temp, "\n")] = 0;
	if (fscanf(fl, "%d", &s->code) != 1)
		return 0;
	strcpy(s->name, temp);
	if (!s->name)
		return 0;
	return 1;
}


void printSuppGeneric(const void* supplier)
{
	const Supplier* s = (const Supplier*)supplier;
	printf("Name: %s, Code: %d\n", &s->name, s->code);
}

int isSameSupplier(const Supplier* s1, const Supplier* s2)
{
	if (s1->code != s2->code)
		return 0;
	if (!compareTwoStringsNoCaseSensetive(s1->name, s2->name))
		return 0;
	return 1;
}

int isSupplierCode(const Supplier* s, const int code)
{
	if (s->code != code)
		return 0;
	return 1;
}
int isSupplierName(const Supplier* s, const char name[])
{
	if (compareTwoStringsNoCaseSensetive(s->name, name))
		return 1;
	return 0;
}
void addProdcutToSupplier(Product* p, const char suppName[])
{
	strcpy(p->supplier, suppName);
}


void deleteProdcutFromSupplier(Product* p, const char suppName[])
{
	strcpy(p->supplier, "");
}


int isProductFromSupplier(const char nameOfProduct[], const char code[], const char suppName[])
//Function return 1 if the product is supplied by the given supplier, else returns 0
{
	Product* p = findProductByNameOrCode(nameOfProduct, code);
	if (compareTwoStringsNoCaseSensetive(p->supplier, suppName))
		return 1;
	return 0;
}