#pragma once
template <typename T>
class MatrixNode
{
	template <typename T>	
	friend class SparseMatrix;
protected:
	T info;
    int i, j;
	MatrixNode<T>* link;
public:
	MatrixNode() {
        info = T();
        link = nullptr;
        i = j = -1;
    }
	MatrixNode(const T& data, int x, int y) {
        info = data;
		i = x;
		j = y; 
		link = nullptr;
	}
	~MatrixNode() {}
};