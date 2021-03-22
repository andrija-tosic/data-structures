#pragma once
#include "MatrixNode.h"
#include <iostream>
using namespace std;

template<typename T>
class SparseMatrix {
    MatrixNode<T>* start;
    MatrixNode<T>* tail;
    size_t dim;

    void AddNode(MatrixNode<T>* node);
    MatrixNode<T>* GetNodeAt(int i, int j);
public:
    SparseMatrix();
    SparseMatrix(size_t n) { dim = n; }
    ~SparseMatrix();
    void SetAt(const T& el, int i, int j);
    T GetAt(int i, int j);
    void Print(); // stampa i nulte elemente

};

template<typename T>
SparseMatrix<T>::SparseMatrix() {
    start = tail = nullptr;
    dim = 0;
}

template<typename T>
SparseMatrix<T>::~SparseMatrix() {
    MatrixNode<T>* element = start;
    MatrixNode<T>* traveler;
    while (element) {
        traveler = element->link;
        delete element;
        element = traveler;
    }
}

template<typename T>
void SparseMatrix<T>::SetAt(const T& el, int i, int j) {
    if (i >= 0 && i < dim && j >= 0 && j < dim) {
        MatrixNode<T>* found = GetNodeAt(i, j);
        if (found) {
            found->info = el;
        }
        else {
            MatrixNode<T>* node = new MatrixNode<T>(el, i, j);
            AddNode(node);
        }
    }
    else {
        cout << "index out of bounds" << endl;
    }
}

template<typename T>
MatrixNode<T>* SparseMatrix<T>::GetNodeAt(int i, int j) {
    MatrixNode<T>* pok = start;
    while (pok && pok->i != i && pok->j != j)
        pok = pok->link;
    return pok;
}

template<typename T>
T SparseMatrix<T>::GetAt(int i, int j) {
    MatrixNode<T>* pok = start;
    while (pok && (pok->i != i || pok->j != j))
        pok = pok->link;
    if (pok)
        return pok->info;
    else return T();
}


template<typename T>
void SparseMatrix<T>::AddNode(MatrixNode<T>* node) {
    if (!start) {
        start = tail = node;
    } else {
        tail->link = node;
        tail = node;
    }
}

template<typename T>
void SparseMatrix<T>::Print() {
    for (int i=0;i<dim;i++) {
        for (int j=0;j<dim;j++) {
            cout << GetAt(i, j) << " ";
        }
        cout << endl;
    }
}