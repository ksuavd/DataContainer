#include <iostream>
using namespace std;

#define tab "\t"
template <typename T> class ForwardList;
template <typename T> class Iterator;

template <typename T> class Element
{
	T Data; //значение элмента
	Element<T>* pNext; //адрес следующего элемента
	static int count; //Количество элементов
public:
	Element(T Data, Element<T>* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList<T>;
	friend class Iterator<T>;
};

template <typename T>

int Element<T>::count = 0;// Инициализируем статическую переменную, объявленную за классом 
 //Статическую переменную можно проиницилизировать только за классом

template <typename T> class Iterator
{
	Element<T>* Temp;
public:
	Iterator(Element<T>* Temp) :Temp(Temp)
	{
		cout << "ItConstructor:\t" << this << endl;
	}
	~Iterator()
	{
		cout << "ItDetructor:\t" << this << endl;
	}
	Iterator<T>& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}

	bool operator==(const Iterator<T>& other)const
	{
		return this->Temp == other.Temp;
	}
	bool operator!=(const Iterator<T>& other)const
	{
		return this->Temp != other.Temp;
	}
	T& operator*()
	{
		return Temp->Data;
	}
};
template <typename T> class ForwardList //Forward-односвязный, однонаправленный список
{
	Element<T>* Head;//Голова списка, содержит указатель на нулевой элемент списка
	int size;
public:
	Iterator<T> begin() //возвращает итератор на начало контейнера
	{
		return Head;//начало
	}

	Iterator<T> end() // возвращает итератор на конец контейнера
	{
		return nullptr; //конец
	}
	
	// Constructors

	ForwardList()
	{
		Head = nullptr;//Если список пуст, то его голова указывает на ноль
		cout << "LConstructor:\t" << this << endl;
	}
	
	~ForwardList()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//               Operators
	ForwardList(const std::initializer_list<T>& il) :ForwardList()
	{
		cout << typeid(il.begin()).name() << endl;
		for (T const* it = il.begin(); it != il.end(); it++)
		{
			push_back(*it);
		}
	}


	void push_front(T Data)
	{
		/*
		//1.Создаем новый элемент:
		Element* New = new Element(Data);
		//2. Новый элемент должен указывать на начало списка:
		New->pNext = Head;
		//3. Голову списка переводим на новый элемент
		Head = New;   */
		Head = new Element<T>(Data, Head);
		size++;
	}
	void push_back(T Data)
	{
		if (Head == nullptr)return push_front(Data);
		//1. Создаем новый элемент
		//Element* New = new Element(Data);
		//Element* Temp = Head;
		//2. Доходим до конца списка
		Element<T>* Temp = Head;
		while (Temp->pNext)
		Temp = Temp->pNext;
		//3. Добавляем элемент
		Temp->pNext = new Element<T>(Data);
		size++;
	}

	//Erasing Elements
	void pop_front()
	{
		//1) Сохраняем адрес удаляемого элемента
		Element<T>* Erased = Head;
		//2) Исключаем элемент из списка
		Head = Head->pNext;
		//3) Удаляем элемент из памяти
		delete Erased;
		size--;
	}
	void pop_back()
	{
		//1) Доходим до предпоследнего элемента списка Temp->pNext->pNext
		Element<T>* Temp = Head;
		while (Temp->pNext->pNext)	Temp = Temp->pNext;
		//2) удаляем последний элемент из памяти
		delete Temp->pNext;
		//3)Зануляем указатель на следующий элемент
		Temp->pNext = nullptr;
		size--;
	}
	void insert(int Index, T Data)
	{
		if (Index == 0)return push_front(Data);
		if (Index > size)return;

		//1)Создаем новый элемент
		Element<T>* New = new Element(Data);

		//2) Доходим до нужного элемента в список
		Element<T>* Temp = Head;
		for (int i = 0; i < Index - 1; i++)Temp = Temp->pNext;

		//3)Включаем новый элемент в список
		//New->pNext = Temp->pNext;
		//Temp->pNext = New;
		Temp->pNext = new Element<T>(Data, Temp->pNext);

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
		for (Element<T>* Temp = Head; Temp; Temp = Temp->pNext)
		cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << size << endl;
		cout << "ОБЩЕЕ количество элементов: " << Element::count << endl;
	}
};

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