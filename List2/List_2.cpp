#include"List_2.h"

///////////////определение класса///////////////////////////

template <typename T>List<T>::Element::Element(T Data, Element* pNext, Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template <typename T>List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}
template <typename T>List<T>::ConstBaseIterator::ConstBaseIterator(Element* Temp) :Temp(Temp) {}
template <typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {}
template <typename T>bool List<T>::ConstBaseIterator::operator==(const ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template <typename T>bool List<T>::ConstBaseIterator:: operator!=(const ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template <typename T>const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}

template <typename T>List<T>::ConstIterator::ConstIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "ItConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>List<T>::ConstIterator::~ConstIterator()
{
#ifdef DEBUG
	cout << "ItDestructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template <typename T>typename List<T>::ConstIterator List<T>::ConstIterator:: operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template <typename T>typename List<T>::ConstIterator& List<T>::ConstIterator:: operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template <typename T>typename List<T>::ConstIterator List<T>::ConstIterator::  operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}

template <typename T>  List<T>::ConstReverseIterator::ConstReverseIterator(Element* Temp) :ConstBaseIterator(Temp)
{
#ifdef DEBUG
	cout << "RItConstructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T> List<T>::ConstReverseIterator::~ConstReverseIterator()
{
#ifdef DEBUG
	cout << "RItDestructor:\t" << this << endl;
#endif // DEBUG
}
template <typename T>typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template <typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator:: operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}

template <typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template <typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template <typename T>typename List<T>::ConstIterator List<T>::cbegin()const
{
	return Head;
}
template <typename T>typename List<T>::ConstIterator List<T>::cend()const
{
	return nullptr;
}

template <typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template <typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template <typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template <typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::crbegin()const
{
	return Tail;
}
template <typename T>typename List<T>::ConstReverseIterator List<T>::crend()const
{
	return nullptr;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template <typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
//Constructors
template <typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template <typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); it++)
	{
		push_back(*it);
	}
}
template <typename T>List<T>::~List()
{
	//while (Head)pop_front();
	while (Tail)pop_back();
	cout << "LDestructor:\t" << this << endl;
}

//					Adding elements:
template <typename T>void List<T>::push_front(T Data)
{
	if (Head == nullptr && Tail == nullptr)
	{
		Head = Tail = new Element(Data);
		size++;
		return;
	}

	Head = Head->pPrev = new Element(Data, Head);
	size++;
}
template <typename T>void List<T>::push_back(T Data)
{
	if (Head == nullptr && Tail == nullptr)return push_front(Data);

	Tail = Tail->pNext = new Element(Data, nullptr, Tail);

	size++;
}
template <typename T>void List<T>::insert(int Index, T Data)
{
	if (Index > size)return;

	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}

	Temp->pPrev = Temp->pPrev->pNext = new Element(Data, Temp, Temp->pPrev);
	size++;
}

//				Removing elements:
template <typename T>void List<T>::pop_front()
{
	if (Head == nullptr && Tail == nullptr)return;
	if (Head == Tail)
	{
		delete Head;
		Head = Tail = nullptr;
		return;
	}
	//1) Исключаем элемент из списка:
	Head = Head->pNext;
	//2) Удаляем элемент из памяти:
	delete Head->pPrev;
	//3) Обнуляем адрес удаленного элемента:
	Head->pPrev = nullptr;

	size--;
}
template <typename T>void List<T>::pop_back()
{
	if (Head == Tail)return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template <typename T>void List<T>::erase(int Index)
{
	if (Index == 0) return pop_front();
	if (Index > size)return;
	Element* Temp;
	Temp = Tail;
	for (int i = 0; i < size - Index - 1; i++)
	{
		Temp = Temp->pPrev;
	}
	Element* Erased = Temp->pPrev->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = Temp->pNext;
	delete Erased;
	size--;
}
//				Methods:
template <typename T>void List<T>::print()const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
template <typename T>void List<T>::reverse_print()const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	cout << "Количество элементов списка: " << size << endl;
}

///////////////конец определение класса///////////////////////////