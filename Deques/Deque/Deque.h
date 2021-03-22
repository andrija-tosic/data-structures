template<typename T>
class Deque {
public:
	virtual void EnQueueHead(const T& data) = 0;
	virtual void EnQueueTail(const T& data) = 0;
	virtual T DeQueueHead() = 0;
	virtual T DeQueueTail() = 0;
	virtual T GetHead() = 0;
	virtual T GetTail() = 0;
	virtual bool IsEmpty() = 0;
	virtual size_t NumberOfElements() = 0;
};




































































































