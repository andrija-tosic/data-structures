#pragma once

template <class T>
class Array
{
private:
	T* niz;
	int base;
	unsigned int length;
public:
	Array(int b, int n)
	{
		base = b;
		length = n;
		niz = new T[n];
	}

	Array(int n)
	{
		base = 0;
		length = n;
		niz = new T[n];
	}

	~Array()
	{
		delete[] niz;
	}

	void print();

	Array<T>& operator=(const Array<T>& arr);
	T& operator[](int index);

	T* getData() { return niz; }
	T& getAt(int index)	{ return niz[index - base]; }

	int getBase() { return base; }
	unsigned int getLength() { return length; }

	void setBase(int newBase) { base = newBase; }
	void setLength(unsigned int newLength);
	void setAt(T el, int index);
};

template <class T>
void Array<T>::print()
{
	for (int i = 0; i < length; i++)
		std::cout << "niz[" << i + base << "] = " << niz[i] << std::endl;
}

template <class T>
Array<T>& Array<T>::operator=(const Array<T>& arr)
{
	if (this != &arr)
	{
		if (this->length != arr.length)
		{
			if(niz)
				delete[] niz;

			this->length = arr.length;
			this->niz = new T[this->length];
		}

		for (int i = 0; i < this->length; i++)
			this->niz[i] = arr.niz[i];

		this->base = arr.base;
	}
	return *this;
}

template <class T>
T& Array<T>::operator[](int index)
{
	int trueIndex = index - base;
	if (trueIndex < 0 || trueIndex > length)
		throw "Nevazeci indeks.";
	return niz[trueIndex];
}

template <class T>
void Array<T>::setAt(T el, int index)
{
	int trueIndex = index - base;
	if (trueIndex < 0 || trueIndex > length)
		throw "Nevazeci indeks.";
	niz[trueIndex] = el;
}

template <class T>
void Array<T>::setLength(unsigned int newLength)
{
	if (length != newLength)
	{
		T* tmp = new T[newLength];

		int minLength = length < newLength ? length : newLength;

		for (int i = 0; i < minLength; i++)
			tmp.niz[i] = niz[i];
		delete[] niz;
		niz = tmp;
		length = newLength;
	}
}
