//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __ADDRESS__
#define __ADDRESS__
#define SIZE 254 

typedef enum { country, city, street, number, NumTypes } address_type;
const char* typeName[NumTypes];

void initAddress(char* address);
void replaceSpaceWithAnd(char* s);
char* ltrim(char* s);
char* rtrim(char* s);
char* trim(char* s);

#endif

