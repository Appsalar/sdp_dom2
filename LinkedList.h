#pragma once
#include <iostream>

template <typename T>
struct Item
{
	T value;
	Item<T>* next;
};

template <typename T>
class LinkedList
{
private:
	Item <T>* start;
	Item <T>* end;
	int length;

public:
	LinkedList()
	{
		start = NULL;
		end = NULL;
		length = 0;
	}

	LinkedList(const T& other)
	{
		start = NULL;
		end = NULL;
		length = 0;
		copy(other);
	}

	LinkedList& operator=(const T& other)
	{
		if (this != &other)
		{
			del();
			copy(other);
		}
		return *this;
	}
	

	virtual ~LinkedList()
	{
		del();
	}

	int GetSize() const
	{
		return length;
	}

	T& GetLast()
	{
		return end->value;
	}

	T& GetValue(int index)
	{
		Item<T>* foo = start;
		for (int i = 0; i < index; ++i)
		{
			foo = foo->next;
		}
		return foo->value;
	}

	void add(const T& elem)
	{
		Item<T>* newElem = new Item < T > ;
		newElem->value = elem;
		newElem->next = NULL;
		if (length == 0)
		{
			start = newElem;
			end = newElem;
		}
		else
		{
			end->next = newElem;
			end = newElem;
		}
		++length;
	}

	void print() const
	{
		Item<T>* foo = start;
		std::cout << "[";
		for (int i = 0; i < length - 1; ++i)
		{
			std::cout << foo->value << ", ";
			foo = foo->next;
		}
		if (end)
			std::cout << end->value;

		std::cout<< "]";
	}

	void remove(int index)
	{
		if (index < 0 || index >= length)
		{
			return;
		}

		if (index == 0)
		{
			Item<T>* p = start;
			start = start->next;
			delete p;
			--length;
			return;
		}

		Item<T>* p = start;

		for (int i = 0; i < index - 1; ++i)
		{
			p = p->next;
		}

		Item<T>* q = p->next;
		p->next = p->next->next;
		delete q;

		if (index == length - 1)
		{
			end = p;
		}

		--length;
	}

	void insertAt(const T& elem, int index)
	{
		if (index<0 || index>length)
		{
			return;
		}
		++length;

		Item<T>* item = new Item <T>;
		item->value = elem;
		item->next = NULL;
		if (start == 0)
		{
			start = item;
			end = item;
			return;
		}

		if (index == 0)
		{
			item->next = start;
			start = item;
			return;
		}

		Item<T>* p = start;
		for (int i = 0; i < index - 1; ++i)
			p = p->next;

		item->next = p->next;
		p->next = item;
		if (p == end)
			end = item;
	}

	void insertAfter(const T& elem, Item<T>*& item)
	{
		if (item == NULL)
			return;
		++length;

		Item<T>* newElem = new Item < T > ;
		newElem->value = elem;
		newElem->next = item->next;
		if (item == end)
			end = newElem;

	}

private:
	void copy(const LinkedList<T>& other)
	{
		Item<T>* p = other.start;


		if (p)
		{
			start = new Item<T>;
			start->value = p->value;
			start->next = NULL;
			end = start;
			p = p->next;
		}

		while (p)
		{
			Item<T>* elem = new Item<T>;
			elem->value = p->data;
			elem->next = NULL;
			end->next = elem;
			end = elem;
			p = p->next;
		}

		length = other.length;
	}

	void del()
	{
		Item<T>* p = start;
		Item<T>* q;

		while (p)
		{
			q = p;
			p = p->next;
			delete q;
		}

		start = end = NULL;
		length = 0;
	}
};

