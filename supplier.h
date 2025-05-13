//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __SUPPLIER__
#define __SUPPLIER__

#include "product.h"
#define SIZE 254

typedef struct
{
	char name[SIZE];
	int code;
}Supplier;

void initSupplier(Supplier* s);
int readSuppFromFile(FILE* fl, Supplier* s);
void printSuppGeneric(const void* supplier);
int isSameSupplier(const Supplier* s1, const Supplier* s2);
int isSupplierCode(const Supplier* s,const int code);
int isSupplierName(const Supplier* s, const char name[]);
void addProdcutToSupplier(Product* p, const char suppName[]);
void deleteProdcutFromSupplier(Product* p, const char suppName[]);
int isProductFromSupplier(const char nameOfProduct[], const char code[], const char suppName[]);



#endif
