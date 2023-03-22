#include <iostream>
using namespace std;

#define tab "\t"
class Element
{
	int Data; //значение элмента
	Element* pNext; //адрес следующего элемента
	static int count; //Количество элементов
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
	//	cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
	//	cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
	friend class Iterator;
	friend class ConstIterator;
};
int Element::count = 0;// Инициализируем статическую переменную, объявленную за классом 
 //Статическую переменную можно проиницилизировать только за классом

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp) :Temp(Temp)
	{
		//cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
	//	cout << "ItDetructor:\t" << this << endl;
	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()
	{
		return Temp->Data;
	}
};
class ConstIterator
{
	Element* Temp;
public:
	ConstIterator(Element* Temp) :Temp(Temp)
	{
		//cout << "ItConstructor:\t" << this << endl;
	}
	~ConstIterator()
	{
		//	cout << "ItDetructor:\t" << this << endl;
	}
	ConstIterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const ConstIterator& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const ConstIterator& other)const
	{
		return this->Temp != other.Temp;
	}
	const int& operator*()const
	{
		return Temp->Data;
	}
};

class ForwardList //Forward-односвязный, однонаправленный список
{
	Element* Head;//Голова списка, содержит указатель на нулевой элемент списка
	int size;
public:
	const Iterator begin() const //возвращает итератор на начало контейнера
	{
		return Head;//начало
	}

	const Iterator end() const // возвращает итератор на конец контейнера
	{
		return nullptr; //конец
	}
	 Iterator begin()  //возвращает итератор на начало контейнера
	{
		return Head;//начало
	}

	 Iterator end()  // возвращает итератор на конец контейнера
	{
		return nullptr; //конец
	}
	
	// Constructors

	ForwardList()
	{
		Head = nullptr;//Если список пуст, то его голова указывает на ноль
	//	cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext) push_back(Temp->Data);
	//	cout << "CopyConstructor:\t" << this << endl;
	}


	~ForwardList()
	{
		while (Head)pop_front();
	//	cout << "LDestructor:\t" << this << endl;
	}
	//               Operators
	ForwardList(const std::initializer_list<int>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}

	void push_front(int Data)
	{
		/*
		//1.Создаем новый элемент:
		Element* New = new Element(Data);
		//2. Новый элемент должен указывать на начало списка:
		New->pNext = Head;
		//3. Голову списка переводим на новый элемент
		Head = New;   */
		Head = new Element(Data, Head);
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1. Создаем новый элемент
		//Element* New = new Element(Data);
		//Element* Temp = Head;
		//2. Доходим до конца списка
		Element* Temp = Head;
		while (Temp->pNext)
		Temp = Temp->pNext;
		//3. Добавляем элемент
		Temp->pNext = new Element (Data);
		size++;
	}

	//Erasing Elements
	void pop_front()
	{
		//1) Сохраняем адрес удаляемого элемента
		Element* Erased = Head;
		//2) Исключаем элемент из списка
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete Erased;
		size--;
	}
	void pop_back()
	{
		//1) Доходим до предпоследнего элемента списка Temp->pNext->pNext
		Element* Temp = Head;
		while (Temp->pNext->pNext)	Temp = Temp->pNext;
		//2) удаляем последний элемент из памяти
		delete Temp->pNext;
		//3)Зануляем указатель на следующий элемент
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Index, int Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;

		//1)Создаем новый элемент
		Element* New = new Element(Data);

		//2) Доходим до нужного элемента в список
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3)Включаем новый элемент в список
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element(Data, Temp->pNext);

		size++;
	}
	void erase(int Index)
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
	void print()const
	{
		//Element* Temp = Head;//Temp-это итератор
		//Итератор-это указатель при помощи которого можно получить доступ
		//к элементам структуры данных
		/*while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент
		}*/
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "ОБЩЕЕ количество элементов: " << Element::count << endl;
	}
	void reverse()
	{
	/*	Element* Temp;
		for (int i = 0; i < size - 1; i++)
		{
			Temp = Head;
			while (Temp->pNext)
				Temp = Temp->pNext;
			insert(i, Temp->Data);
			pop_back();
		}*/
		ForwardList buffer;
		/*for (Element* Temp = Head; Temp; )
		{
			buffer.push_front(Temp->Data);
			pop_front();
		}
		Head = buffer.Head;
		buffer.Head = nullptr;*/
		while (Head)
		{
			buffer.push_front(Head->Data);
			pop_front();
		}
		Head = buffer.Head;
		buffer.Head = nullptr;
	}

};
ForwardList operator +(const ForwardList& left, const ForwardList& right)
{
	ForwardList cat=left;
	for (Iterator it = left.begin(); it != left.end(); ++it)cat.push_back((*it)*10);
	for (Iterator it = right.begin(); it != right.end(); ++it)cat.push_back(*it);
	return cat;
}
//#define BASE_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define HOME_WORK_1
//#define PREFORMANCE_CHEK


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
	//for (int i : list2)cout << i << tab; cout << endl;

	ForwardList list3 = list + list2;
	for (int i : list3)cout << i << tab; cout << endl; 
	for (int i : list)cout << i << tab; cout << endl;
#endif // HOME_WORK_1
#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3, 5, 8, 13, 21 };
	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif
#ifdef	PREFORMANCE_CHEK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
//	list.print();
	list.reverse();
//	list.print();
	cout << "Список заполнен: "; 
	ForwardList list2 = list;
	for (int i : list)cout << i << tab; cout << endl;
	for (int i : list)cout << i << tab; cout << endl;
#endif PREFORMANCE_CHEK
}