#pragma once
#include"ChainedHashTable.h"

void main()
{
	ChainedHashTable tablica(64);

	tablica.insert(HashObject("www.youtube.com", "google", "a"));
	tablica.insert(HashObject("www.youtub.com", "facebook", "c"));

	tablica.insert(HashObject("www.google.com", "google", "b"));
	tablica.insert(HashObject("www.googl.com", "facebook", "c"));
	
	tablica.insert(HashObject("www.instagrm.com", "facebook", "c"));
	tablica.insert(HashObject("www.instagram.com", "facebook", "c"));
	
	tablica.insert(HashObject("www.wasd.com", "facebook", "c"));
	
	tablica.insert(HashObject("www.asd.com", "facebook", "c"));
	tablica.insert(HashObject("www.das.com", "facebook", "c"));
	tablica.insert(HashObject("www.dsa.com", "facebook", "c"));
	tablica.insert(HashObject("www.sad.com", "facebook", "c"));

	tablica.insert(HashObject("www.aaaaaaa.com", "facebook", "c"));
	tablica.insert(HashObject("www.aaaaaab.com", "facebook", "c"));

	tablica.insert(HashObject("www.facebook.com", "facebook", "c"));
	tablica.insert(HashObject("www.facebok.com", "facebook", "c"));

	tablica.print();

	char* y = new char[30];

	strcpy(y, "www.youtube.com");

	std::cout << tablica.find(y).getRecord() << std::endl;

}