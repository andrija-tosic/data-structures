#pragma once
#include <iostream>
#include "ChainedScatterTable.h"

int main() {
	ChainedScatterTable<int, std::string> table(10);
	ChainedScatterTable<int, double> table2(10);

	table2.insert(2, 2.4);

	/*
	char* a = new char[10];
	char* b = new char[10];
	char* c = new char[10];

	strcpy_s(a, 10, "Milinko");
	strcpy_s(b, 10, "Janko");
	strcpy_s(c, 10, "Nemanija");
	*/

	table.insert(24, "Milinko");
	table.insert(36, "Janko");

	table2.insert(3, 5.0);
	table2.insert(3, 14.431);
	table2.insert(2, 0.212);

	std::cout << "table1: " << std::endl;
	table.print();
	std::cout << "table2: " << std::endl;
	table2.print();

	table.withdraw(50);
	table.withdraw(24);
	table.withdraw(34);

	table.insert(24, "Nemanija");

	std::cout << "table1: " << std::endl;
	table.print();
	std::cout << "table2: " << std::endl;
	table2.print();

	return 0;
}