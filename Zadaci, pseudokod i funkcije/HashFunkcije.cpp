#include <iostream>
#include <cmath>

const unsigned int m = 1000;

unsigned int djb2(unsigned char *str) {
    unsigned int hash = 5381;
    int c;
    while (c = *str++) {
        hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
    }
    return hash;
}

unsigned int metod_sredine_kvadrata(unsigned int key) {
    unsigned w = 32;
    unsigned p = 6; // m = 64
    return (key*key) >> (w - p);
}

unsigned int metod_mnozenja(unsigned int key) {
    unsigned a = 2654435769; // 2^32 / fi
    unsigned w = 32;
    unsigned p = 6;
    return (a*key) >> (w - p);
}

unsigned int metod_fibonnaci(unsigned int key) {
    unsigned a = 40503;
    unsigned w = 32;
    unsigned p = 6;
    return (a*key) >> (w - p);
}

unsigned int metod_presavijanja(unsigned int key) {
    unsigned sum = 0;
    for(int i=0; i<3; i++) {
        sum += key % 1000; // extract zadnje 3 cifre
        key /= 1000; // shave off zadnje 3 cifre
    }
    return sum;
}

unsigned jun2020f(const char* key) {
    unsigned a=0, b=0, c=0, d=0;
    int i;
    for (i=0;i<3;i++)
        a += (key[i]<<5) + key[i];
    
    for (i=4;i<8;i++) {
        b*=10;
        b+=key[i] - '0';
    }
    c=key[9]*10 + key[10];
    d = key[12]*100 + key[13]*10 + key[14];
    
    return ((b<<a) >> c) + d;
}

unsigned int jun2020g(unsigned int h) {
    return (h*40503) >> (32-19);
}

unsigned g(unsigned h) {
    return h % m;
}

/*
Septembar 2020
U jednom kolu grupne faze Lige sampiona se igra i do osam utakmica.
Za potrebe pracenja statistike svakog igraca, a kako bi se stedelo pristupanje bazi podataka,
softver koji je razvila UEFA koristi hes tablicu sa unutrasnjim ulancavanjem i zajednickim prostorom
za sinonime zarad brzog pristupa statistici svakog igraca. Za svakog igrada se pamti ime, prezime.
Broj na dresu (1-99), troslovna oznaku kluba za koji igra i troslovna oznaka kluba protiv koga igra
na utakmici za koju se vodi statistika kao i sama instanca klase Statistika (nije potrebno implementirati).
Implementirati funkciju koja obezbedjuje dobro rasipanje stavki u tablici i metodu za dodavanje i
azuriranje statistike igraca u hes tablici ako se zna da timovi unapred registruju 25 igraca za polusezonu.
*/

int main()
{
    /*
    std::cout << metod_sredine_kvadrata(257346542) << std::endl;
    std::cout << metod_mnozenja(257346542) << std::endl;
    std::cout << metod_fibonnaci(257346542) << std::endl;
    std::cout << metod_presavijanja(257346542) << std::endl;
    std::cout << std::endl;
    
    std::cout << g(metod_sredine_kvadrata(257346542)) << std::endl;
    std::cout << g(metod_mnozenja(257346542)) << std::endl;
    std::cout << g(metod_fibonnaci(257346542)) << std::endl;
    std::cout << g(metod_presavijanja(257346542)) << std::endl; 
    */
    
    std::cout << jun2020g(jun2020f("MFC-5437/63-105")) << std::endl;
    std::cout << jun2020g(jun2020f("MCF-5347/36-105")) << std::endl;
    return 0;
}

/*
2020 jan
U cilju razvoja softvera za proveru zauzetosti email adresa ACME kompanije 
koja koristi sledece domene na kojima registruje emailove zaposlenih 
(acme.com, acme.org, acme.us.com i acme.io) koristi se hes tablica sa 
otvorenim adresiranjem i sekundarnom funkcijom sa kvadratnim trazenjem. 
Implementirati funkcije bool IsTaken(char* email, char* name, char* lastName) 
koja vraca ime i prezime radnika kome je dodeljena email adresa, ukoliko postoji 
iii vraca podatak o tome da email adresa nije zauzeta i funkciju 
bool Register(char* email, char* name, char* lastName) koja registruje email za 
radnika cije je ime i prezime prosledjeno. Smatrati da je softver projektovan za 
registraciju do 1000 email adresa.
*/

bool IsTaken(char* email, char* name, char* lastName)
{
	unsigned int hash = h(email);

    for (int i = 0; i < m; i++)
    {
        unsigned int probe = hash + c(i);
        if (array[probe].status == 0) return false;
        if (array[probe].status == 2 && strcmp (array[probe].getKey(), email) == 0)
        {
            name = array[probe].name;
            lastName = array[probe].lastName;
            return true;
        }
    }
    
    return false;
}

bool Register(char* email, char* name, char* lastName)
{
    if (count == m)
        throw "Full";

    if (isTaken(email, nullptr, nullptr))
        throw "Posotji";

    unsigned int hash = h(email);
    unsigned int probe = hash;

    int i = 0;

    do
    {
        if (array[probe].status < 2)
        {
            array[probe].status = 2;
            array[probe].name = name;
            array[probe].lastName = lastName;
            count++;
            return true;
        }
        i++;
        probe = (hash + c(i))
    } while (probe != hash && i < m)
    return false;
}

ChainedScatterObject ChainedScatterTable::withdraw(char* key)
{
	unsigned int hash = h(key);
	unsigned int prev = -1;

	if (count == 0)
		throw "mrs";

	while (array[hash].next != -1 && array[hash].next != 0 && array[hash].status != 0 && !array[hash].isEqualKey(key))
	{
		prev = hash;
		hash = array[hash].next;
	}

	if (array[hash].next == 0)
	{
		throw "puno.";
	}
	else if (array[hash].status == 2 && array[hash].isEqualKey(key))
	{
		array[hash].status = 1;
		array[hash].deleteRecord();
		
		if (prev != -1)
		{
			array[prev].next = array[hash].next;
		}

		array[hash].next = lrmp;
		lrmp = hash;
	}
	else
	{
		throw "nema ga.";
	}
}
