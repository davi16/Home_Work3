//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __SUPPLIERMANAGER__
#define __SUPPLIERMANAGER__

#include "supplier.h"
#define SIZE 254

typedef struct
{
	Supplier* suppliers;
	int numOfSupp;
}SupplierManager;

static SupplierManager sparSuppliers;


void initSuppManagerFromFile();
void initSupplierManager();
void printSupplierManager();
int addSupplier(const Supplier* s);
int removeSupplier(const Supplier* s);
int updateSupplier(Supplier* s);
Supplier* findSupplierByNameOrCode(const char nameOfSupp[], const int code);


#endif
