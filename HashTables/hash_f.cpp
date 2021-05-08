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
    return (key*key) >> (w - 6);
}

unsigned int metod_mnozenja(unsigned int key) {
    unsigned a = 2654435769; // 2^32 / fi
    unsigned w = 32;
    return (a*key) >> (w - 6);
}

unsigned int metod_fibonnaci(unsigned int key) {
    unsigned a = 40503;
    unsigned w = 32;
    return (a*key) >> (w - 6);
}

unsigned int metod_presavijanja(unsigned int key) {
    unsigned sum = 0;
    for(int i=1000; i<1000000000; i*=1000) {
        sum += key % i;
        key %= i;
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
