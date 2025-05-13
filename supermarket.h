//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __SUPERMARKET__
#define __SUPERMARKET__

#define SIZE 254



typedef struct
{
	char name[SIZE];
	char address[SIZE];
	int code;
}Supermarket;

typedef struct node {
	Supermarket key;
	struct node* next;
}NODE;

typedef struct {
	NODE head;
}LIST;

void initSuperMarket(Supermarket* s);
void printSuperMarket(const Supermarket* s);
int isSameSupermaket(const Supermarket* s1, const Supermarket* s2);
int isSupermarketName(const Supermarket* s, const char name[]);
int isSupermarketCode(const Supermarket* s, const int code);

#endif
