//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#ifndef __ARRAYS__
#define __ARRAYS__
#define SIZE 254 

char* initString(char* buf, int size);
int initCode(int max);
int checkProductCode(char* code);
int compareTwoStringsNoCaseSensetive(const char s1[],const char s2[]);
void printGeneralArrayFunction(const void* arr, int size, size_t typeSize, void f(const void* element));

#endif
