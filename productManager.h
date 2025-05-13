//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __PRODUCTMANAGER__
#define __PRODUCTMANAGER__
#include "product.h"

typedef enum { notSorted, byName, byCode, byType , NumOfSort} sorting_type;
const char* sortTitle[NumOfSort];

typedef struct
{
	Product* products;
	int numOfProducts;
	sorting_type sortedBy;
}ProductManager;

static ProductManager sparProducts;

void initProductManager();
void printProductManager();
int addProduct(Product* p);
Product* findProductByNameOrCode(const char name[], const char code[]);
void sortProductArray(sorting_type sortType);
sorting_type getSortingTypeFromUser();
int compareProductByName(const void* product1, const void* product2);
int compareProductByCode(const void* product1, const void* product2);
int compareProductByType(const void* product1, const void* product2);
void doPrintSupermarketWithProductCode(const char code[]);
void doPrintSupermarketWithProductName(const char nameOfProduct[]);
void doPrintSupplierWithProductCode(const char code[]);
void doPrintSupplierWithProductName(const char nameOfProduct[]);
void doPrintProductsWithProductTypeSupers(const product_type type);
int isProductType(const char code[], const char nameOfProduct[]);//return -1 if not found
int isProductCode(const char nameOfProdect[]);//return -1 if not found
void doPrintAllProductsSoldInSuper(const char nameOfSuper[]);
void doPrintAllProductsSuppliedBySupp(const char suppName[]);
void doPrintSuppWithProductType(const product_type type);
int doesExist(char** array, char* name, int size);
Product* binarySearch();
sorting_type whatSort();
#endif
