//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "arrays.h"
#include "address.h"

const char* typeName[NumTypes] = { "Country", "City", "Street", "Number" };

void initAddress(char* address)
{
	char addressValues[NumTypes][SIZE];
	printf("To initialize an adress, enter following parameters:\n");
	for (int i = 0; i < NumTypes; ++i)
	{
		printf("%s: ", typeName[i]);
		initString(addressValues[i], sizeof(addressValues[i]));
		strcpy(addressValues[i], trim(addressValues[i]));
		replaceSpaceWithAnd(addressValues[i]);
	}
	strcpy(address, addressValues[0]);
	for (int i = 1; i < NumTypes; ++i)
	{
		strcat(address, "#");
		strcat(address, addressValues[i]);
	}
}


void replaceSpaceWithAnd(char* s)
{
	int i = 0;
	s[0] = toupper(s[0]);
	while (s[i] != '\0')
	{
		if (isspace(s[i]))
		{
			s[i] = '&';
			s[i + 1] = toupper(s[i + 1]);
		}
		i++;
	}
}


char* ltrim(char* s)
{
	while (isspace(*s)) s++;
	return s;
}

char* rtrim(char* s)
{
	char* back = s + strlen(s);
	while (isspace(*--back));
	*(back + 1) = '\0';
	return s;
}

char* trim(char* s)
{
	return rtrim(ltrim(s));
}