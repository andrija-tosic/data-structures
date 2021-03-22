template<typename T>
class Queue {
public:
	virtual void EnQueue(const T& data) = 0;
	virtual T DeQueue() = 0;
	virtual T GetHead() = 0;
	virtual bool IsEmpty() = 0;
	virtual size_t NumberOfElements() = 0;
};