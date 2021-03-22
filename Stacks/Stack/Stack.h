#pragma once
template <typename T>
class Stack
{
public:
	virtual void Push(const T& data) = 0;
	virtual T Pop() = 0;
	virtual T GetTop() = 0;
	virtual size_t NumberOfElements() = 0;
	virtual bool IsEmpty() = 0;
};










































