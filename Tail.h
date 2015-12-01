#pragma once
#include "LinkedList.h"

template <typename T>
class Tail : protected LinkedList<T>
{
public:
	Tail()
	{

	}

	Tail(const Tail& other)
	{

	}

	Tail& operator=(const Tail& other)
	{

	}

	virtual ~Tail()
	{

	}

	bool empty() const
	{
		if (GetSize() == 0)
			return true;
		return false;
	}

	T& top()
	{
		return GetValue(0);
	}

	void pop()
	{
		remove(0);
	}

	void push(const T& Node)
	{
		add(Node);
	}
};
