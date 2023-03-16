#pragma once
#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
///////////////////////////////////////////////////
////class declaration-объ€вление класса////////////
//////////////////////////////////////////////////

template <typename T> class ForwardList;
template <typename T> class Iterator;

template <typename T> class Element
{
	T Data;
	Element<T>* pNext;
	static int count;
public:
	Element(T Data, Element<T>* pNext = nullptr);
	~Element();

	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template <typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp);
	~Iterator();
	Iterator<T>& operator++();
	bool operator==(const Iterator<T>& other)const;
	bool operator!=(const Iterator<T>& other)const;
	T& operator*();
};

template <typename T> class ForwardList
{
	Element<T>* Head;
	int size;
public:
	Iterator<T> begin();
	Iterator<T> end();
	// Constructors
	ForwardList();
	~ForwardList();
	// Operators
	ForwardList(const std::initializer_list<T>& il);
	void push_front(T Data);
	void push_back(T Data);
	//Erasing Elements
	void pop_front();
	void pop_back();
	void insert(int Index, T Data);
	void erase(int Index);
	//Metods
	void print()const;
};
///////////////////////////////////////////////////
////END class declaration-конец объ€вление класса//
//////////////////////////////////////////////////