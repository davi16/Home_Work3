//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include "exe.h"
#include "arrays.h"


int main()
{
	
	firstInit();

	char select;

	printf("     SPAR SuperMarket branch manager system\n");
	printf("------------------------------------------\n\n");

	do
	{
		printf("		Main Menu\n");
		printf("1 - Add new SPAR branch to system.\n");
		printf("2 - Find product in supermarket or supplier.\n");
		printf("3 - Add product to branch or supplier.\n");
		printf("4 - Show details of a SPAR branch and all products. \n");
		printf("5 - Show details of all SPAR branches\n");
		printf("6 - Show all products of a supplier.\n");
		printf("7 - Show all products sold in SPAR by product type.\n");
		printf("8 - Show all products supplied by product type.\n");
		printf("9 - Show all products sold in a SPAR branch.\n");
		printf("a - Sort SPAR products.\n");
		printf("b - Search SPAR products.\n");
		printf("c - Change sorting of SPAR branches.\n");
		printf("e - Exit program.\n");

		printf(" Please enter an option from the main menu: ");
		(void)scanf("%c", &select);
		while (getchar() != '\n') {};//clearing buffer

		switch (select)
		{
		case '1':
			option1();
			break;
		case '2':
			option2();
			break;
		case '3':
			option3();
			break;
		case '4':
			option4();
			break;
		case '5':
			option5();
			break;
		case '6':
			option6();
			break;
		case '7':
			option7();
			break;
		case '8':
			option8();
			break;
		case '9':
			option9();
			break;
		case 'a':
			option10();
			break;
		case 'b':
			option11();
			break;
		case 'c':
			option12();
			break;
		case 'e':
			Exit();
			printf("Exitting... Have a nice day!");
			break;
		default:
			printf("You entered wrong input, Try again. \n\n");
			break;
		}
	} while (select != 'e');
	return 0;
}