//Students submitting: Kristina goldin 317958799, David Ben Yaacov 320759921
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "exe.h"
#include "arrays.h"
#include "supermarketManager.h"
#include "supplierManager.h"
#include "productManager.h"



void firstInit()
{

	initSuperMarketManager();
	firstInitSuper();
	initProductManager();
	initSuppManagerFromFile();


	printSuperMarketManager();
	printSupplierManager();
	printProductManager();

}
//adding a supermarket
void option1()
{
	Supermarket newSuper;
	printf("Please enter new branch details:\n");
	initSuperMarket(&newSuper);
	printf("The details you entered:\n");
	printSuperMarket(&newSuper);
	if (addSupermarket(&newSuper))
		printf("The branch added successfully!\n");
	else
		printf("Error try again:\n");
}
//find product in supermarket or supplier
void option2()
{
	char name[SIZE], code[SIZE];
	printProductManager();
	printf("Please enter product details:\n");
	printf("Product name: ");
	initString(name, sizeof(name));
	printf("Product code: ");
	initString(code, sizeof(code));
	printf("Where do you want to search? 1-Supermarket , 2-Supplier\n");
	int choice;
	(void)scanf("%d", &choice);
	while (getchar() != '\n') {};//clearing buffer
	switch (choice) {
	case 1:
		doPrintSupermarketWithProductName(name);
		doPrintSupermarketWithProductCode(code);
		break;
	case 2:
		doPrintSupplierWithProductName(name);
		doPrintSupplierWithProductCode(code);
		break;
	default:
		printf("Wrong input!\n Going back to main menu.\n");
		break;
	}
}
//adding a product to super/supplier, make sure the super/supplier doesn't contain the product allready
void option3()
{
	printf("Add product to a branch and supplier\n");
	printf("Do you want to init new product or add existing? 1-new 2-existing  ");
	char select;
	(void)scanf("%c", &select);
	while (getchar() != '\n') {};//clearing buffer
	switch (select)
	{
	case '1':
		option3_1();
		break;
	case '2':
		option3_2();
		break;
	default:
		printf("You entered wrong input \n\n");
	}
}
void addSupermarketExe(Product p)
{
	printf("Enter a supermarket where this product is being sold: ");
	char supermarket[SIZE];
	initString(supermarket, sizeof(supermarket));
	if (findSupermarketByNameOrCode(supermarket, -1))
		addProdcutToSupermarket(p.pData.name, supermarket);
}
void option3_1()
{
	Product p;
	initProduct(&p);
	printf("Product: ");
	printProductGeneric(&p);
	if (addProduct(&p))
		printf("Added successfuly to the data base!\n Enter the supplier of the product: ");
	else
	{
		printf("Error");
		return;
	}
	char supplier[SIZE];
	initString(supplier, sizeof(supplier));
	if (findSupplierByNameOrCode(supplier, -1))
		addProdcutToSupplier(&p, supplier);
	else
		printf("Supplier is not in the data base\n");
	int select = 1;
	do {
		addSupermarketExe(p);
		printf("Do you want to add another supermarket? 1-yes , 0-no");
		(void)scanf("%d", &select);
		while (getchar() != '\n') {};//clearing buffer
	} while (select);
}
void option3_2()
{
	printProductManager();
	char name[SIZE];
	Product* p;
	printf("Enter product name: ");
	initString(name, sizeof(name));
	p = findProductByNameOrCode(name, "-1");
	if (p)
	{
		printf("Enter supplier name: ");
		initString(name, sizeof(name));
		if (findSupplierByNameOrCode(name, -1) && !compareTwoStringsNoCaseSensetive(p->supplier, name))
		{
			addProdcutToSupplier(p, name);
			printf("Succsess\n");
		}
		else
			printf("Somthing went wrong\n");
		printf("Enter super name: ");
		initString(name, sizeof(name));
		if (findSupermarketByNameOrCode(name, -1) && !doesExist(p->soldInSupers, name, p->numOfSupers))
		{
			addProdcutToSupermarket(p->pData.name, name);
			printf("Succsess\n");
		}
		else
			printf("Somthing went wrong\n");
	}

}
//printing the data of a super, make sure to print all products too
void option4()
{
	Supermarket* s;
	char supermarket[SIZE];
	printf("Enter Supermarket branch name: ");
	initString(supermarket, sizeof(supermarket));
	s = findSupermarketByNameOrCode(supermarket, -1);
	if (s)
	{
		printSuperMarket(s);
		doPrintAllProductsSoldInSuper(supermarket);
	}
	else
		printf("Supermarket doesn't exist\n");
}
//printing all supermarkets, without their products
void option5()
{
	printSuperMarketManager();
}
//print all products supplied by a supplier, asks for the supplier name or number
void option6()
{
	char supplier[SIZE];
	printSupplierManager();
	printf("Enter Supplier name: ");
	initString(supplier, sizeof(supplier));
	doPrintAllProductsSuppliedBySupp(supplier);
}
//print all products of a specific type from all supers
void option7()
{
	product_type t;
	t = getTypeFromUser();
	doPrintProductsWithProductTypeSupers(t);
}
//print all products of a specific type being supplied by suppliers
void option8()
{
	product_type t;
	t = getTypeFromUser();
	doPrintSuppWithProductType(t);
}
//print all products sold in a super, asks for name or code or both
void option9()
{
	printSuperMarketManager();
	printf("Enter the supermarket name or code: ");
	char nameOrCode[SIZE];
	initString(nameOrCode, sizeof(nameOrCode));
	Supermarket* s = findSupermarketByNameOrCode(nameOrCode, atoi(nameOrCode));
	if (s)
		doPrintAllProductsSoldInSuper(s->name);
	else
		printf("Supermarket doesn't exist\n");
}
//Sorting Products array by selected sorting method
void option10()
{
	printf("Right now the products sorting is: %s\n", sortTitle[sparProducts.sortedBy]);
	printProductManager();
	printf("Select sorting method:\n");
	sorting_type sortType;
	sortType = getSortingTypeFromUser();
	sortProductArray(sortType);
	printf("The products after sorting %s: \n", sortTitle[sortType]);
	printProductManager();
}
//Finding a product through binary search
void option11()
{
	Product* p = NULL;
	printProductManager();
	printf(sortTitle[whatSort()]);
	switch (whatSort())
	{
	case notSorted:
		printf("The search can't be completed, the array is yet to be sorted!\n");
		printf("Returning to main menu...\n");
		break;
	case byName:
		printf("Please enter product details:\n");
		printf("Product name: ");
		p = binarySearch();
		if (p)
		{
			printf("The product found:\n");
			printProductGeneric(p);
		}
		else
			printf("Product not found\n");
		break;
	case byCode:
		printf("Please enter product details:\n");
		printf("Product code: ");
		p = binarySearch();
		if (p)
		{
			printf("The product found:\n");
			printProductGeneric(p);
		}
		else
			printf("Product not found\n");
		break;
	case byType:
		printf("Please enter product details:\n");
		printf("Product type:\n");
		(void)binarySearch();
		break;
	}
}
//Rearranging the supermarkets by selected sorting method
void option12()
{
	printf("Enter the way to sort the branches (0 - by code, 1 - lexicographicaly): ");
	int choice;
	(void)scanf("%d", &choice);
	while (getchar() != '\n') {};//clearing buffer
	switch (choice)
	{
	case 0: sort = code;
		break;
	case 1: sort = lexi;
		break;
	default:
		printf("Wrong value entered!\n");
		printf("Return to main menu...\n");
		return;
	}
	reSort();
	printf("SPAR branches sorted successfully!\n");
	printf("Return to main menu...\n");
}

void Exit()
//free array allocation on exit 
{
	free(sparSuppliers.suppliers);
	freeSupersArray();
	free(sparProducts.products);
}