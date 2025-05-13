//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "arrays.h"
#include "supplierManager.h"
#include "productManager.h"


void initSuppManagerFromFile()
{
	char* pString = NULL;
	sparSuppliers.numOfSupp = 0;
	int sCount = 0, pCount = 0;
	Product p;
	Supplier s;
	FILE* f = fopen("suppliers.txt", "r");

	if (!f) {
		printf("File not found\n");
		initSupplierManager();
	}
	else {
		sparSuppliers.suppliers = (Supplier*)calloc(sparSuppliers.numOfSupp, sizeof(Supplier));
		if (!sparSuppliers.suppliers)
		{
			fclose(f);
			initSupplierManager();
		}
		while (!feof(f))
		{
			if (!readSuppFromFile(f, &s))
			{
				fclose(f);
				initSupplierManager();
			}
			else
				addSupplier(&s);
			(void)fscanf(f, "%d", &pCount);
			for (int j = 0; j < pCount; j++)
			{
				if (readProductFromFile(f, &p))
				{
					addProduct(&p);
					addProdcutToSupplier(&p, s.name);
				}
			}
		}
		fclose(f);
		printf("Suppliers initialized successfully from file!\n\n");
	}
}


void initSupplierManager()
{
	int physSize = 1, logicSize = 0, i = 0;
	int more;
	printf("Please initialize suppliers that work with Spar company\n");
	sparSuppliers.suppliers = (Supplier*)calloc(physSize, sizeof(Supplier));
	if (sparSuppliers.suppliers)
	{
		while (1)
		{
			sparSuppliers.numOfSupp = physSize;
			Supplier sTemp;
			initSupplier(&sTemp);
			sparSuppliers.suppliers[i] = sTemp;
			logicSize++;
			i++;
			printf("Do you want to initialize more? 1-yes, 0-no: ");
			(void)scanf("%d", &more);
			while (getchar() != '\n') {};//clearing buffer
			if (more == 0)
			{
				break;
			}
			if (physSize == logicSize)
			{
				physSize++;
				Supplier* arr = (Supplier*)realloc(sparSuppliers.suppliers, physSize * sizeof(Supplier));
				
				if (!arr)

				{
					printf("Error");
					break;
				}
				sparSuppliers.suppliers = arr;
			}
		}
	}
}

void printSupplierManager()
{
	if (sparSuppliers.numOfSupp == 0)
	{
		printf("No suppliers");
		return;
	}
	printf("The SPAR suppliers list:\n");
	printGeneralArrayFunction(sparSuppliers.suppliers, sparSuppliers.numOfSupp, sizeof(Supplier), printSuppGeneric);
}

int addSupplier(const Supplier* s)
{
	Supplier* arr = (Supplier*)realloc(sparSuppliers.suppliers, (sparSuppliers.numOfSupp+1) * sizeof(Supplier));
	if (arr)
	{
		sparSuppliers.suppliers = arr;
		sparSuppliers.suppliers[sparSuppliers.numOfSupp] = *s;
		sparSuppliers.numOfSupp++;
		return 1;
	}
	return 0;
	
}
int removeSupplier(const Supplier* s)
{
	for (int i = 0; i < sparSuppliers.numOfSupp; ++i)
	{
		if (isSameSupplier(&sparSuppliers.suppliers[i], s))
		{
			sparSuppliers.suppliers[i] = sparSuppliers.suppliers[sparSuppliers.numOfSupp - 1];
			Supplier* arr = (Supplier*)realloc(sparSuppliers.suppliers, (sizeof(sparSuppliers.numOfSupp) - 1) * sizeof(Supplier));
			if (arr)
			{
				sparSuppliers.suppliers = arr;
				sparSuppliers.numOfSupp--;
				return 1;
			}
		}
	}
	return 0;

}
int updateSupplier(Supplier* s)
{
	for (int i = 0; i < sparSuppliers.numOfSupp; ++i)
	{
		if (isSameSupplier(s, &sparSuppliers.suppliers[i]))
		{
			initSupplier(&sparSuppliers.suppliers[i]);
			return 1;
		}
	}
	return 0;

}
Supplier* findSupplierByNameOrCode(const char nameOfSupp[], const int code)
{
	for (int i = 0; i < sparSuppliers.numOfSupp; ++i)
	{
		if (isSupplierName(&sparSuppliers.suppliers[i], nameOfSupp) || isSupplierCode(&sparSuppliers.suppliers[i], code))
			return &sparSuppliers.suppliers[i];
	}
	return NULL;
}