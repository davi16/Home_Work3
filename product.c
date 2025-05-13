//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "productManager.h"
#include "supermarketManager.h"
#include "arrays.h"


const char* typeTitle[NumOfTypes] = { "food", "cleaning", "general" };

void initProduct(Product* p)
{
	printf("Please enter product name: ");
	initString(p->pData.name, sizeof(p->pData.name));
	printf("Please enter product code: ");
	initString(p->pData.code, sizeof(p->pData.code));
	while (!checkProductCode(p->pData.code))
	{
		printf("Value entered doesn't match requirments!\nPlease re-enter: ");
		initString(p->pData.code, sizeof(p->pData.code));
	}
	p->pData.type = getTypeFromUser();
	printf("Set manufacture date\n");
	printf("Enter the date in the format dd^^mm^^yyyy: ");
	char date[SIZE];
	initString(date, sizeof(date));
	initDate(&(p->pData.manufactureDate), date);
	printf("Set expiration date:\n");
	printf("Enter the date in the format dd^^mm^^yyyy: ");
	initString(date, sizeof(date));
	initDate(&(p->pData.experationDate), date);
	p->soldInSupers = initSupersArray(p);
}

int readProductFromFile(FILE* fl, Product* p)
{
	Date manufactured = { 20 , 05 , 2024 };
	Date expiration = { 20 , 07, 2024 };
	int type;
	while (fgetc(fl) != '\n') {};
	if (!fgets(p->pData.name, sizeof(p->pData.name), fl))
		return 0;
	p->pData.name[strcspn(p->pData.name, "\n")] = 0;
	if (fscanf(fl, "%s %d", p->pData.code, &type) != 2)
		return 0;
	if (!p->pData.name || !p->pData.code)
		return 0;
	p->pData.type = ((product_type)type);
	p->pData.manufactureDate = manufactured;
	p->pData.experationDate = expiration;
	p->soldInSupers = initSupersArray(p);
	return 1;
}

product_type getTypeFromUser()
{
	int i, t;
	printf("Enter product type\n");
	do {
		for (i = 0; i < NumOfTypes; i++)
			printf("Enter %d for %s\n", i, typeTitle[i]);
		(void)scanf("%d", &t);
		while (getchar() != '\n') {};//clearing buffer
	} while (t < 0 || t >= NumOfTypes);
	return (product_type)t;
}


void printProductGeneric(const void* product)
{
	const Product* p = (const Product*)product;
	printf("Name: %s, Code: %s, Type: %s ", &p->pData.name, p->pData.code, typeTitle[p->pData.type]);
	printf("\n");
}
char** initSupersArray(Product* p)
{
	p->numOfSupers = 0;

	//inits dynamic array of strings
	p->soldInSupers = (char**)malloc(p->numOfSupers * sizeof(char*));
	if (p->soldInSupers)
		return p->soldInSupers;
	else
	{
		printf("Alocation didn't succeed");
		return NULL;
	}

}


int isProductName(const Product* p, const char name[])
{
	if (compareTwoStringsNoCaseSensetive(p->pData.name, name))
		return 1;
	return 0;
}

int ckeckIsProductCode(const Product* p, const char code[])
{
	if (compareTwoStringsNoCaseSensetive(p->pData.code, code))
		return 1;
	return 0;
}


void addProdcutToSupermarket(const char nameOfProduct[], const char nameOfSupermarket[])
{
	Product* p = findProductByNameOrCode(nameOfProduct, "-1");
	if (!p)
	{
		printf("Product doesn't exist");
		return;
	}
	if (!findSupermarketByNameOrCode(nameOfSupermarket, -1))
	{
		printf("Supermarket doesn't exist");
		return;
	}
	p->numOfSupers++;
	char** temp = (char**)realloc(p->soldInSupers, p->numOfSupers * sizeof(char*));
	if (temp && p->numOfSupers > 0)
	{
		p->soldInSupers = temp;
		p->soldInSupers[p->numOfSupers - 1] = (char*)malloc(SIZE * sizeof(char*));
		if (p->soldInSupers[p->numOfSupers - 1])
			strcpy(p->soldInSupers[p->numOfSupers - 1], nameOfSupermarket);

	}
}

void freeSupersArray()
{
	for (int i = 0; i < sparProducts.numOfProducts; ++i)
	{
		for (int j = 0; j < sparProducts.products[i].numOfSupers; ++j)
			free(sparProducts.products[i].soldInSupers[j]);
		free(*sparProducts.products[i].soldInSupers);
	}
}


void deleteProdcutFromSupermarket(const char nameOfProduct[], const char nameOfSupermarket[])
{
	//Empty string instead of supermarket name
	Product* p = findProductByNameOrCode(nameOfProduct, "-1");
	if (!p)
	{
		printf("Product doesn't exist");
		return;
	}
	if (!isProductInSupermarket(nameOfSupermarket, nameOfProduct))
	{
		printf("Product is not in supermarket");
	}
	for (int i = 0; i < p->numOfSupers; ++i)
	{
		if (compareTwoStringsNoCaseSensetive(p->soldInSupers[i], nameOfSupermarket))
			strcpy(p->soldInSupers[i], "");
	}

}



int isProductInSupermarket(const char nameOfSupermarket[], const char nameOfProduct[])
{
	Product* p = findProductByNameOrCode(nameOfProduct, "-1");
	if (!p)
	{
		printf("Product doesn't exist");
		return 0;
	}
	for (int i = 0; i < p->numOfSupers; ++i)
	{
		if (compareTwoStringsNoCaseSensetive(p->soldInSupers[i], nameOfSupermarket))
			return 1;
	}
	return 0;
}
