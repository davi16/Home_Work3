//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "supermarketManager.h"


void firstInitSuper()
{
	//for testing
	sort = code;
	Supermarket superDuper = { "Super Duper" , "Israel#Tel-Aviv#Alenbi#105" , 12345 };
	Supermarket davidSuper = { "David super" , "Israel#Lod#Dakar#3" , 23456 };
	Supermarket kS = { "KS" , "Israel#Ashdod#hertzl#53" , 34567 };
	addSupermarket(&superDuper);
	addSupermarket(&davidSuper);
	addSupermarket(&kS);
}


void initSuperMarketManager()
{
	printf("Please initialize supermarket branches into the Spar company\n");
	sort = code;
	myList.head.next = NULL;
	int more = 1;
		while (more)
		{
			Supermarket sTemp;
			initSuperMarket(&sTemp);
			addSupermarket(&sTemp);
			printf("Do you want to init more? 1-yes, 0-no: ");
			(void)scanf("%d", &more);
			while (getchar() != '\n') {};//clearing buffer
		}
}

void printSuperMarketManager()
{
	if (!&myList)
	{
		printf("No supers");
		return;
	}
	printf("The SPAR supermarket branches:\n");
	NODE* tmp = &myList.head;
	while (tmp->next != NULL)
	{
		printSuperMarket(&tmp->next->key);
		tmp = tmp->next;
	}
}

void reSort()
{
	if (!&myList)
	{
		return;
	}
	LIST tempList;
	tempList.head = myList.head;
	NODE* tmp = &tempList.head;
	myList.head.next = NULL;
	while (tmp->next != NULL)
	{
		addSupermarket(&tmp->next->key);
		tmp = tmp->next;
	}
	L_free(&tempList);
}

void L_free(LIST* pList)
{
	NODE* tmp;
	BOOL cont = True;
	if (!pList) return;
	tmp = &(pList->head);
	while (cont)
		cont = L_delete(tmp);
}


int addSupermarket(const Supermarket* s)
{
	if (!&myList)
	{
		return 0;
	}
	NODE* tmp = &myList.head;
	while (tmp->next != NULL)
	{
		switch (sort)
		{
		case code:	if (tmp->next->key.code > s->code)
					{
						tmp->next = L_insert(tmp, s);
						return 1;
					}
					break;
		case lexi:	if (strcmp(tmp->next->key.name , s->name) > 0)
					{
						tmp->next = L_insert(tmp, s);
						return 1;
					}
					break;
		}
		tmp = tmp->next;
	}
	tmp->next = L_insert(tmp, s);
	return 1;

}


NODE* L_insert(NODE* pNode,const Supermarket * s)
{
	NODE* tmp;
	if (!pNode) return NULL;
	tmp = (NODE*)malloc(sizeof(NODE));
	if (tmp != NULL) {
		tmp->key = *s;
		tmp->next = pNode->next;
		pNode->next = tmp;
	}
	return tmp;
}


int removeSupermarket(const Supermarket* s)
{
	NODE * found = L_find(myList.head.next, *s);
	if (!found)
	{
		return 0;
	}
	NODE* tmp = found;
	while (tmp != NULL)
	{
		if (isSameSupermaket(&tmp->next->key, s))
			found = tmp->next;
		tmp = tmp->next;
	}
	BOOL deleted = L_delete(found);
	if (deleted == False) {
		return 0;
	}
	return 1;
}


BOOL L_delete(NODE* pNode)
{
	NODE* tmp;
	if (!pNode || !(tmp = pNode->next)) return False;
	pNode->next = tmp->next;
	free(tmp);
	return True;
}


NODE* L_find(NODE* pNode, Supermarket Value)
{
	NODE* tmp = pNode;
	while (tmp != NULL)
	{
		if (isSameSupermaket(&tmp->key, &Value))
			return tmp;
		tmp = tmp->next;
	}
	return NULL;
}


int updateSupermarket(Supermarket* s)
{
	NODE* found = L_find(myList.head.next, *s);
	if (!found)
	{
		return 0;
	}
	initSuperMarket(&found->key);
	return 1;
}


Supermarket* findSupermarketByNameOrCode(const char name[],const int code)
{
	NODE* tmp = myList.head.next;
	while (tmp != NULL)
	{
		if (isSupermarketName(&tmp->key, name) || isSupermarketCode(&tmp->key, code))
			return &tmp->key;
		tmp = tmp->next;
	}
	return NULL;
}