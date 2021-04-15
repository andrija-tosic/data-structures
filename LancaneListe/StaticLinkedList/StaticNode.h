template<typename T>
class StaticNode {
private:
	T info;
	int next;

	template<typename T>
	friend class StaticLinkedList;
	
	StaticNode();
	StaticNode(const T& data);
	StaticNode(const T& data, const int& n);
};

template<typename T>
inline StaticNode<T>::StaticNode() {
	info = T();
	next = 0;
}

template<typename T>
inline StaticNode<T>::StaticNode(const T& data) {
	info = data;
}

template<typename T>
inline StaticNode<T>::StaticNode(const T& data, const int& n) {
	info = data;
	next = n;
}