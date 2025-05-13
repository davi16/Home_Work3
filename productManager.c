//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "productManager.h"
#include "supermarketManager.h"
#include "supplierManager.h"
#include "arrays.h"

const char* sortTitle[NumOfSort] = { "Not Sorted", "By Name", "By Code", "By Type" };

void initProductManager()
{
	sparProducts.numOfProducts = 0;
	sparProducts.products = (Product*)calloc(sparProducts.numOfProducts, sizeof(Product));
	sparProducts.sortedBy = notSorted;
}


void sortProductArray(sorting_type sortType)
{
	switch (sortType)
	{
	case byName:
			qsort(sparProducts.products, sparProducts.numOfProducts, sizeof(Product), compareProductByName);
			sparProducts.sortedBy = byName;
			break;
	case byCode:
			qsort(sparProducts.products, sparProducts.numOfProducts, sizeof(Product), compareProductByCode);
			sparProducts.sortedBy = byCode;
			break;
	case byType:
			qsort(sparProducts.products, sparProducts.numOfProducts, sizeof(Product), compareProductByType);
			sparProducts.sortedBy = byType;
			break;
	}
}

Product* binarySearch()
{
	int t;
	Product temp;
	switch (sparProducts.sortedBy)
	{
	case byName:
		initString(temp.pData.name, sizeof(temp.pData.name));
		return bsearch(&temp, sparProducts.products, sparProducts.numOfProducts, sizeof(Product), compareProductByName);
	case byCode:
		initString(temp.pData.code, sizeof(temp.pData.code));
		while (!checkProductCode(temp.pData.code))
		{
			printf("Value entered doesn't match requirments!\nPlease re-enter: ");
			initString(temp.pData.code, sizeof(temp.pData.code));
		}
		return bsearch(&temp, sparProducts.products, sparProducts.numOfProducts, sizeof(Product), compareProductByCode);
	case byType:
		do {
			for (int i = 0; i < NumOfTypes; i++)
				printf("Enter %d for %s\n", i, typeTitle[i]);
			(void)scanf("%d", &t);
			while (getchar() != '\n') {};//clearing buffer
		} while (t < 0 || t >= NumOfTypes);
		temp.pData.type = (product_type)t;
		Product* first = bsearch(&temp, sparProducts.products, sparProducts.numOfProducts, sizeof(Product), compareProductByType);
		for (int i = 0; i < sparProducts.numOfProducts; i++)
		{
			if (sparProducts.products[i].pData.type == first->pData.type)
			{
				printProductGeneric(&sparProducts.products[i]);
			}
		}
		return NULL;
	}
	return NULL;
}

sorting_type whatSort()
{
	return sparProducts.sortedBy;
}

sorting_type getSortingTypeFromUser()
{
	int i, t;
	printf("Enter sorting type\n");
	do {
		for (i = 0; i < NumOfSort; i++)
			printf("Enter %d for %s\n", i, sortTitle[i]);
		(void)scanf("%d", &t);
		while (getchar() != '\n') {};//clearing buffer
	} while (t < 0 || t >= NumOfSort);
	return (sorting_type)t;
}

int compareProductByName(const void* product1, const void* product2)
{
	const Product* p1 = (const Product*)product1;
	const Product* p2 = (const Product*)product2;
	return strcmp(p1->pData.name, p2->pData.name);
}

int compareProductByCode(const void* product1, const void* product2)
{
	const Product* p1 = (const Product*)product1;
	const Product* p2 = (const Product*)product2;
	int code1 = atoi(p1->pData.code);
	int code2 = atoi(p2->pData.code);
	if (code1 < code2) return -1;
	else if (code1 > code2) return 1;
	else return 0;
}

int compareProductByType(const void* product1, const void* product2)
{
	const Product* p1 = (const Product*)product1;
	const Product* p2 = (const Product*)product2;
	return strcmp(typeTitle[p1->pData.type], typeTitle[p2->pData.type]);
}


void printProductManager()
{
	if (sparProducts.numOfProducts == 0)
	{
		printf("No products");
		return;
	}
	printf("The products sold in SPAR supermarket branches:\n");
	printGeneralArrayFunction(sparProducts.products, sparProducts.numOfProducts, sizeof(Product), printProductGeneric);
}



int addProduct(Product* p)
{
	Product* arr =
		(Product*)realloc(sparProducts.products, (sparProducts.numOfProducts + 1) * sizeof(Product));
	if (arr)
	{
		sparProducts.products = arr;
		sparProducts.products[sparProducts.numOfProducts] = *p;
		sparProducts.numOfProducts++;
		return 1;
	}
	return 0;
}




Product* findProductByNameOrCode(const char name[], const char code[])
{
	for (int i = 0; i < sparProducts.numOfProducts; ++i)
	{
		if (isProductName(&sparProducts.products[i], name) || ckeckIsProductCode(&sparProducts.products[i], code))
			return &sparProducts.products[i];
	}
	return NULL;
}



void doPrintSupermarketWithProductCode(const char code[])
{
	printf("Finding supermarkets where the product is being sold by code:\n");
	Product* temp = findProductByNameOrCode("", code);
	if (!temp)
	{
		printf("Product code doesn't exist\n");
		return;
	}
	int count = 0;
	for (int i = 0; i < temp->numOfSupers; ++i)
	{
		printf("Sold in: %s\n", temp->soldInSupers[i]);
		count++;
	}
	if (count == 0)
	{
		printf("This product isn't sold in any supermarket at the moment.\n");
	}
}



void doPrintSupermarketWithProductName(const char nameOfProduct[])
{
	printf("Finding supermarkets where the product is being sold by name:\n");
	Product* temp = findProductByNameOrCode(nameOfProduct, "-1");
	if (!temp)
	{
		printf("Product name doesn't exist\n");
		return;
	}
	int count = 0;
	for (int i = 0; i < temp->numOfSupers; ++i)
	{
		printf("Sold in: %s\n", temp->soldInSupers[i]);
		count++;
	}
	if (count == 0)
	{
		printf("This product isn't sold in any supermarket at the moment.\n");
	}
}




void doPrintSupplierWithProductCode(const char code[])
{
	printf("Finding supplier of the product by code:\n");
	Product* temp = findProductByNameOrCode("", code);
	if (!temp)
	{
		printf("Product name doesn't exist\n");
		return;
	}
	printf("Supplier is: %s\n", temp->supplier);
}



void doPrintSupplierWithProductName(const char nameOfProduct[])
{
	printf("Finding supplier of the product by name:\n");
	Product* temp = findProductByNameOrCode(nameOfProduct, "-1");
	if (!temp)
	{
		printf("Product name doesn't exist\n");
		return;
	}
	printf("Supplier is: %s\n", temp->supplier);
}

void doPrintSuppWithProductType(const product_type type)
{
	printf("Finding suppliers that supply this type of product:\n");
	int size = 0;
	char** suppliers = (char**)calloc(size, sizeof(char*));
	for (int i = 0; i < sparProducts.numOfProducts; ++i)
	{
		if (sparProducts.products[i].pData.type == type)
		{
			if (!doesExist(suppliers, sparProducts.products[i].supplier, size))
			{
				size++;
				char** temp = (char**)realloc(suppliers, size * sizeof(char*));
				if (temp)
				{
					suppliers = temp;
					suppliers[size - 1] = (char*)malloc(SIZE * sizeof(char*));
					if (suppliers[size - 1])
						strcpy(suppliers[size - 1], sparProducts.products[i].supplier);
				}
			}
		}
	}
	if (suppliers && size != 0)
	{
		for (int i = 0; i < size; ++i)
		{
			printf("%s\n", *(suppliers + i));
		}
	}
	else
		printf("Not sold by any supplier\n");
	free(suppliers);
}

int doesExist(char** array, char* name, int size)
{
	for (int i = 0; i < size; ++i)
	{
		if (compareTwoStringsNoCaseSensetive(array[i], name))
			return 1;
	}
	return 0;
}

void doPrintProductsWithProductTypeSupers(const product_type type)
{
	printf("Finding supermarkets where this type of product is being sold:\n");

	int size = 0;
	char** superMarkets = (char**)calloc(size, sizeof(char*));
	for (int i = 0; i < sparProducts.numOfProducts; ++i)
	{
		if (sparProducts.products[i].pData.type == type)
		{
			for (int j = 0; j < sparProducts.products[i].numOfSupers; ++j)
			{
				if (!doesExist(superMarkets, sparProducts.products[i].soldInSupers[j], size))
				{
					size++;
					char** temp = (char**)realloc(superMarkets, size * sizeof(char*));
					if (temp)
					{
						superMarkets = temp;
						superMarkets[size - 1] = (char*)malloc(SIZE * sizeof(char*));
						if (superMarkets[size - 1])
							strcpy(superMarkets[size - 1], sparProducts.products[i].soldInSupers[j]);
					}
				}
			}
		}
	}
	if (superMarkets && size != 0)
	{
		for (int i = 0; i < size; ++i)
		{
			printf("%s\n", *(superMarkets + i));
		}
	}
	else
		printf("Not sold in any branch\n");
	free(superMarkets);
}


int isProductType(const char code[], const char nameOfProduct[])
{
	Product* temp = findProductByNameOrCode(nameOfProduct, "-1");
	if (!temp)
	{
		printf("Product name doesn't exist\n");
		return -1;
	}
	if (ckeckIsProductCode(temp, code))
	{
		printf("Product code doesn't exist\n");
		return -1;
	}
	return temp->pData.type;
}



int isProductCode(const char nameOfProduct[])
{
	//Recieves product name and returns product code
	Product* temp = findProductByNameOrCode(nameOfProduct, "-1");
	if (!temp)
	{
		printf("Product name doesn't exist\n");
		return -1;
	}
	return atoi(temp->pData.code);

}

void doPrintAllProductsSoldInSuper(const char nameOfSuper[])
{
	Supermarket* s = findSupermarketByNameOrCode(nameOfSuper, -1);
	if (!s)
	{
		printf("Supermarket name doesn't exist\n");
		return;
	}
	printf("The products sold in %s branch are:\n", nameOfSuper);
	for (int i = 0; i < sparProducts.numOfProducts; ++i)
	{
		if (isProductInSupermarket(nameOfSuper, sparProducts.products[i].pData.name))
			printf("%s\n", sparProducts.products[i].pData.name);
	}
}


void doPrintAllProductsSuppliedBySupp(const char suppName[])
{
	Supplier* s = findSupplierByNameOrCode(suppName, -1);
	if (!s)
	{
		printf("Supplier name doesn't exist\n");
		return;
	}
	printf("The products supplied by %s are:\n", suppName);
	for (int i = 0; i < sparProducts.numOfProducts; ++i)
	{
		if (isProductFromSupplier(sparProducts.products[i].pData.name, "-1", suppName))
			printf("%s\n", sparProducts.products[i].pData.name);
	}

}