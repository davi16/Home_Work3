//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __SUPERMARKETMANAGER__
#define __SUPERMARKETMANAGER__

#include "supermarket.h"
#define SIZE 254

typedef enum { code, lexi } CHOICE;

typedef enum { False, True } BOOL;


LIST myList;
CHOICE sort;



void firstInitSuper();
void initSuperMarketManager();
void printSuperMarketManager();
int addSupermarket(const Supermarket *s);
int removeSupermarket(const Supermarket* s);
int updateSupermarket(Supermarket* s);
Supermarket* findSupermarketByNameOrCode(const char name[],const int code);
NODE* L_insert(NODE* pNode, const Supermarket* s);
void L_free(LIST* pList);
BOOL L_delete(NODE* pNode);
NODE* L_find(NODE* pNode, Supermarket Value);
void reSort();
#endif
