#pragma once

template <class T>
class MDArray
{
private:
	T* data;
	int* dim;
	int* fact;
	int dimNo;
public:
	MDArray(int* d, int n);
	~MDArray();
	T& getAt(int* indeksi, int n) { return data[getOffset(indeksi, n)]; }
	void setAt(T el, int* indeksi, int n) { data[getOffset(indeksi, n)] = el; }
private:
	int getOffset(int* indeksi, int n);
};

template <class T>
MDArray<T>::~MDArray()
{
	delete[] data;
	delete[] dim;
	delete[] fact;
}

template <class T>
MDArray<T>::MDArray(int* d, int n)
{
	dimNo = n;
	dim = new int[n];
	fact = new int[n];

	int p = 1;
	for (int i = n - 1; i >= 0; i--)
	{
		dim[i] = d[i];
		fact[i] = p;
		p *= dim[i];
	}

	data = new T[p];
}

template <class T>
int MDArray<T>::getOffset(int* indeksi, int n)
{
	if (n != dimNo)
		throw "Netacan broj dimenzija";

	int offset = 0;
	for (int i = 0; i < dimNo; i++)
	{
		if (indeksi[i] < 0 || indeksi[i] >= dim[i])
			throw "Ilegalna dimenzija.";
		offset += indeksi[i] * fact[i];
	}
	return offset;
}