#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define tab "\t"
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

template <typename T> int Element<T>::count = 0;

template <typename T>Element<T>::Element(T Data, Element<T>* pNext):Data(Data), pNext(pNext)
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
//////////ForwardList

template <typename T>Iterator<T>ForwardList<T>:: begin()
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

template <typename T>void ForwardList<T>:: push_front(T Data)
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

//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
#define RANGE_BASED_FOR_LIST
//#define HOME_WORK_1

int main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK



	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
	}
	list.print();
	//list.pop_front();
	//list.print();
	/*
	list.pop_back();
	list.print();

	list.push_back(123);
	list.print();*/

	int value;
	int index;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	//list.pop_back();
	//list.print();

	ForwardList list2;
	//list2.push_back(3);
	//list2.push_back(5);
	//list2.push_back(8);
	//list2.print();
	list.erase(2);
	list.print();
#endif // BASE_CHECK
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	//for (int i = 0; i < sizeof(arr) / sizeof(int); i++)
	//Range-based for
	for (int i :arr)
	{	
		cout <<i << tab; 
	}
	cout << endl;
	ForwardList list = { 3, 5, 8, 13, 21 };
	list.print(); 
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif RANGE_BASED_FOR_ARRAY

#ifdef HOME_WORK_1
	ForwardList list = { 3, 5, 8, 13, 21 };
	//list.print();
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList list2 = { 34, 55, 89 };
	for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3 = list + list2;
	for (int i : list3)cout << i << tab; cout << endl; 
#endif // HOME_WORK_1

#ifdef RANGE_BASED_FOR_LIST
	ForwardList<int> list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;

	ForwardList<double> d_list = { 3.1, 5.1, 8.1, 13.1, 21.1 };
	for (double i : d_list)
	{
		cout << i << tab;
	}
	cout << endl;
	ForwardList<std::string> s_list = { "Хорошо", "живет", "на", "свете", "Винни", "Пух" };
	for (std::string i : s_list)
	{
		cout << i << tab;
	}
	cout << endl;

#endif
}