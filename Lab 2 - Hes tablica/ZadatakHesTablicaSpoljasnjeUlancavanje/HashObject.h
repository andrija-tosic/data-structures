#pragma once
#include <iostream>
using namespace std;
class HashObject
{
private:
	char* key;
	char* ime;
	char* registrator;
public:
	HashObject();
	HashObject(const char* k, const char* i, const char* r);
	HashObject(HashObject const& obj);
	~HashObject();
	HashObject& operator = (HashObject const& obj);
	bool operator == (HashObject const& obj);
	void deleteRecord();
	char* getKey() { return key; }
	char* getRecord() {
		char* str = new char[80];
		char separator[] = "|";
		strcpy(str, ime);
		strcat(str, separator);
		strcat(str, registrator);
		return str;
	}
	bool isEqualKey(char* k) { return strcmp(key, k) == 0; }
	void print();
};