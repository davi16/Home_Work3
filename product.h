//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __PRODUCT__
#define __PRODUCT__

#define SIZE 254

#include "date.h"


typedef enum { food, cleaning, general ,NumOfTypes} product_type;
const char* typeTitle[NumOfTypes];

typedef struct
{
	product_type type;
	char name[SIZE];
	char code[SIZE];
	Date manufactureDate;
	Date experationDate;

}Product_data;

typedef struct
{
	char** soldInSupers;
	int numOfSupers;
	char supplier[SIZE];
	Product_data pData;
}Product;


void initProduct(Product* p);
int readProductFromFile(FILE* fl, Product* p);
product_type getTypeFromUser();
void printProductGeneric(const void* product);
char** initSupersArray(Product* p);
void freeSupersArray();
int isProductName(const Product* s, const char name[]);
int ckeckIsProductCode(const Product* s, const char code[]);
void addProdcutToSupermarket(const char nameOfProduct[], const char nameOfSupermarket[]);
void deleteProdcutFromSupermarket(const char nameOfProduct[], const char nameOfSupermarket[]);
int isProductInSupermarket(const char nameOfSupermarket[], const char nameOfProduct[]);

#endif

