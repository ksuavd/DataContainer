#include "ForwardList.h"

///////////////////////////////////////////////////
////class definition-определение класса////////////
//////////////////////////////////////////////////

template <typename T> int Element<T>::count = 0;

template <typename T>Element<T>::Element(T Data, Element<T>* pNext) :Data(Data), pNext(pNext)
{
	count++;
	cout << "EConstructor:\t" << this << endl;
}
template <typename T>Element<T>::~Element()
{
	count--;
	cout << "EDestructor:\t" << this << endl;
}

/////////////////////Iterator/////////////////////

template <typename T>Iterator<T>::Iterator(Element<T>* Temp) :Temp(Temp)
{
	cout << "ItConstructor:\t" << this << endl;
}
template <typename T>Iterator<T>::~Iterator()
{
	cout << "ItDetructor:\t" << this << endl;
}
template <typename T>Iterator<T>& Iterator<T>:: operator++()
{
	Temp = Temp->pNext;
	return *this;
}

template <typename T>bool Iterator<T>::operator==(const Iterator<T>& other)const
{
	return this->Temp == other.Temp;
}
template <typename T>bool Iterator<T>::operator!=(const Iterator<T>& other)const
{
	return this->Temp != other.Temp;
}
template <typename T>T& Iterator<T>::operator*()
{
	return Temp->Data;
}
//////////ForwardList/////////////

template <typename T>Iterator<T>ForwardList<T>::begin()
{
	return Head;
}

template <typename T>Iterator<T> ForwardList<T>::end()
{
	return nullptr;
}

// Constructors

template <typename T>ForwardList<T>::ForwardList()
{
	Head = nullptr;
	cout << "LConstructor:\t" << this << endl;
}

template <typename T>ForwardList<T>::~ForwardList()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}
// Operators
template <typename T>ForwardList<T>::ForwardList(const std::initializer_list<T>& il) :ForwardList()
{
	cout << typeid(il.begin()).name() << endl;
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}

template <typename T>void ForwardList<T>::push_front(T Data)
{

	Head = new Element<T>(Data, Head);
	size++;
}
template <typename T>void ForwardList<T>::push_back(T Data)
{
	if (Head == nullptr)return push_front(Data);
	Element<T>* Temp = Head;
	while (Temp->pNext)
		Temp = Temp->pNext;
	Temp->pNext = new Element<T>(Data);
	size++;
}
//Erasing Elements
template <typename T>void ForwardList<T>::pop_front()
{
	Element<T>* Erased = Head;
	Head = Head->pNext;
	delete Erased;
	size--;
}
template <typename T>void ForwardList<T>::pop_back()
{
	Element<T>* Temp = Head;
	while (Temp->pNext->pNext)	Temp = Temp->pNext;
	delete Temp->pNext;
	Temp->pNext = nullptr;
	size--;
}
template <typename T>void ForwardList<T>::insert(int Index, T Data)
{
	if (Index == 0)return push_front(Data);
	if (Index > size)return;
	Element<T>* New = new Element(Data);
	Element<T>* Temp = Head;
	for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;
	Temp->pNext = new Element<T>(Data, Temp->pNext);

	size++;
}
template <typename T>void ForwardList<T>::erase(int Index)
{
	if (Index == 0)return pop_front();
	if (Index > size)return;

	Element* Temp = Head;
	for (int i = 0; i < Index - 1; i++)
		Temp = Temp->pNext;
	Element* Erased = Temp->pNext;
	Temp->pNext = Temp->pNext->pNext;
	delete Erased;
	size--;
}
//Metods
template <typename T>void ForwardList<T>::print()const
{
	for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
	cout << "ОБЩЕЕ количество элементов: " << Element::count << endl;
}

///////////////////////////////////////////////////
////end class definition-конец определение класса//
//////////////////////////////////////////////////