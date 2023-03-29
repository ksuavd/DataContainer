#include<iostream>
using namespace std;

#define tab "\t"

template<typename T> class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List<T>;
	}*Head, * Tail;
	unsigned int size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp) :Temp(Temp) {}
		~ConstBaseIterator() {}
		bool operator==(const ConstBaseIterator& other)const
		{
			return this->Temp == other.Temp;
		}
		bool operator!=(const ConstBaseIterator& other)const
		{
			return this->Temp != other.Temp;
		}

		const T& operator*()const
		{
			return Temp->Data;
		}
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator operator++(int);
		ConstIterator& operator--();
		ConstIterator operator--(int);
	};
	class ConstReverseIterator :public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator :public ConstIterator
	{
	public:
		Iterator(Element* Temp) :ConstIterator(Temp) {}
		~Iterator() {}
		T& operator*();
	};
	class ReverseIterator :public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp) :ConstReverseIterator(Temp) {}
		~ReverseIterator() {}
		T& operator*();
	};
	ConstIterator cbegin()const;
	ConstIterator cend()const;
	ConstIterator begin()const;
	ConstIterator end()const;
	Iterator begin();
	Iterator end();

	ConstReverseIterator crbegin()const;
	ConstReverseIterator crend()const;
	ReverseIterator rbegin();
	ReverseIterator rend();
	
	//Constructors
	List();
	List(const std::initializer_list<T>& il);
	~List();

	//					Adding elements:
	void push_front(T Data);
	void push_back(T Data);
	void insert(int Index, T Data);

	//				Removing elements:
	void pop_front();
	void pop_back();
	void erase(int Index);
	//				Methods:
	void print()const;
	void reverse_print()const;
};

/////////////////////ConstIterator НАЧАЛО/////////////////////////////////
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



/////////////////////ConstIterator НАЧАЛО/////////////////////////////////
// 
/////////////////////IConstReverseIterator НАЧАЛО/////////////////////////////////
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

/////////////////////IConstReverseIteratorend/////////////////////////////////


/////////////////////Iterators НАЧАЛО/////////////////////////////////
template <typename T>T& List<T>::Iterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}

template <typename T>T& List<T>::ReverseIterator::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
/////////////////////Iterators НАЧАЛО/////////////////////////////////

/////////////////////LIST НАЧАЛО/////////////////////////////////
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

///////////////////////////////Конец LIST////////////////////////////////////////////////////////////////
template <typename T> void print(const List<T>& list)
{
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
}
template <typename T> void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator rit = list.crbegin(); rit != list.crend(); ++rit)
	{
		//*rit *= 10;
		cout << *rit << tab;
	}
	cout << endl;
}

//#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");

#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	list.reverse_print();

	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	list.reverse_print();
	list.erase(2);
	list.print();
#endif // BASE_CHECK

	List<int> list = { 3, 5, 8, 13, 21 };

	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	for (int& i : list)i *= 10;

	print(list);
	for (List<int>::ReverseIterator rit = list.rbegin(); rit != list.rend(); rit++)*rit /= 10;
	reverse_print(list);
	List<double> d_list = { 2.5,3.14,8.3,4.7 };
	for (double i : d_list)
	{
		cout << i << tab;
	}
	cout << endl;
}