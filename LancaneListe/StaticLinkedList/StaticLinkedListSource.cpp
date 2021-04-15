#include "StaticLinkedList.h"
#include <iostream>

int main() {
	StaticLinkedList<int> slist(3);
	StaticLinkedList<std::string> slist2(10);

	slist.addToTail(1);

	slist.print();
	std::cout << std::endl;

	slist.addToTail(2);
	
	slist.print();
	std::cout << std::endl;

	slist.addToTail(3);

	slist.print();
	std::cout << std::endl;

	slist.addToTail(4);

	slist.print();
	std::cout << std::endl;

	slist.deleteElement(0);
	
	slist.print();
	std::cout << std::endl;
	
	slist.deleteElement(2);
	
	slist.print();
	std::cout << std::endl;

	slist.deleteFromTail();

	slist.print();
	std::cout << std::endl;

	slist.addToTail(5);

	slist.print();
	std::cout << std::endl;

	slist.addToHead(2);

	slist.print();
	std::cout << std::endl;

	slist.deleteFromTail();

	slist.print();
	std::cout << std::endl;

	slist2.addToTail("asd");
	slist2.addToTail("www");
	slist2.addToHead("ptowe");

	slist2.print();
	std::cout << std::endl;

	slist2.deleteElement("asd");
	slist2.deleteFromHead();
	slist2.deleteFromTail();

	slist2.print();
	std::cout << std::endl;

	slist2.addToTail("novi");
	slist2.print();
}