#include "HashObject.h"
using namespace std;
//TODO: Izmeniti metode objekta prema zahtevima zadatka
HashObject::HashObject()
{
	key = NULL;
	ime = NULL;
	registrator = NULL;
}

HashObject::HashObject(const char* k, const char* i, const char* r)
{
	key = new char[strlen(k) + 1];
	strcpy(key, k);
	ime = new char[strlen(i) + 1];
	strcpy(ime, i);
	registrator = new char[strlen(r) + 1];
	strcpy(registrator, r);
}

HashObject::~HashObject()
{
	if (key)
		delete[] key;
	if (ime)
		delete[] ime;
	if (registrator)
		delete[] registrator;
}

HashObject::HashObject(HashObject const& obj)
{
	key = strcpy(new char[strlen(obj.key) + 1], obj.key);
	ime = strcpy(new char[strlen(obj.ime) + 1], obj.ime);
	registrator = strcpy(new char[strlen(obj.registrator) + 1], obj.registrator);
}

HashObject& HashObject::operator = (HashObject const& obj)
{
	if (this != &obj)
	{
		if (key)
			delete key;
		key = new char[strlen(obj.key) + 1];
		strcpy(key, obj.key);
		if (ime)
			delete ime;
		ime = new char[strlen(obj.ime) + 1];
		strcpy(ime, obj.ime);
		if (registrator)
			delete registrator;
		registrator = new char[strlen(obj.registrator) + 1];
		strcpy(registrator, obj.registrator);
	}
	return *this;
}

bool HashObject::operator == (HashObject const& obj)
{
	return (strcmp(this->key, obj.key) == 0) && (strcmp(this->ime, obj.ime) == 0 && strcmp(this->registrator, obj.registrator) == 0);
}

void HashObject::deleteRecord() {
	if (ime) { delete ime; ime = NULL; }
	if (registrator) { delete registrator; registrator = NULL; }
}

void HashObject::print()
{
	if (key != NULL)
	{
		cout << key;
	}
	if (ime != NULL)
	{
		cout << "|" << ime;
	}
	if (registrator != NULL)
	{
		cout << "|" << registrator;
	}
}