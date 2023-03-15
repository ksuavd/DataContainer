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
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;
};
int Element::count = 0;// Инициализируем статическую переменную, объявленную за классом 
 //Статическую переменную можно проиницилизировать только за классом

class ForwardList //Forward-односвязный, однонаправленный
{
	Element* Head;//Голова списка, содержит указатель на нулевой элемент списка
	int size;
public:
	ForwardList()
	{
		Head = nullptr;//Если список пуст, то его голова указывает на ноль
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
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
		New->pNext = Temp->pNext;
		Temp->pNext = New;
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
		Element* Temp = Head;//Temp-это итератор
		//Итератор-это указатель при помощи которого можно получить доступ
		//к элементам структуры данных
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент
		}
		cout << "Количество элементов списка: " << size << endl;
		cout << "ОБЩЕЕ количество элементов: " << Element::count << endl;
	}
};


int main()
{
	setlocale(LC_ALL, "");
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
//	cout << "Введите индекс добавляемого элемента: "; cin >> index;
//	cout << "Введите значение добавляемого элемента: "; cin >> value;
	//list.insert(index, value);
	//list.print();
	//list.pop_back();
	//list.print();

	ForwardList list2;
	//list2.push_back(3);
	//list2.push_back(5);
	//list2.push_back(8);
	//list2.print();
	list.erase(2);
	list.print();

}