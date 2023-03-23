#include <iostream>
using namespace std;
#define tab "\t"
class List
{

	class Element
	{
		int Data;
		Element* pNext;
		Element* pPrev;
	public:
		Element(int Data, Element* pNext = nullptr, Element* pPrev = nullptr)
			:Data(Data), pNext(pNext), pPrev(pPrev)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class List;

	}*Head, * Tail;
	unsigned int size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		//while (Head)pop_front();
		while (Tail)pop_back();
		cout << "LDestructor:\t" << this << endl;
	}
	//      Adding elements:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head=Tail= new Element(Data);
			size++;
			return;
		}
	/*	Element* New = new Element(Data);//1 создаем элемент
		New->pNext = Head;//2 
		Head->pPrev = New;//3 
		Head = New;       //4*/
		Head = Head->pPrev = new Element(Data, Head);
		
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)return push_front(Data);
		Element* New = new Element(Data);//1 
		New->pPrev = Tail;//2 
		Tail->pNext = New;//3 
		Tail = New;       //4

		size++;
	}
	//    Removing elements
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		//1 исключаем элемент из списка
		Head = Head->pNext;
		//2 удаляем элемент из памяти 
		delete Head->pPrev;
		//3 Обнуляем адрес удаленного элемента
		Head->pPrev = nullptr;
		
		size--;
	}
	void pop_back()
	{
		if (Head == Tail) return pop_front();
		//1 
		Tail = Tail->pPrev;
		//2
		delete Tail->pNext;
		//3
		Tail->pNext = nullptr;

		size--;
	}
	void insert (int Index, int Data)
	{
		if (Index == 0) return push_front(Data);
		if (Index > size)return;
		Element* Temp;
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)
		{
			Temp = Temp->pPrev;
		}
		Element* New = new Element(Data);
		New->pNext = Temp;
		New->pPrev = Temp->pPrev;
		Temp->pPrev->pNext = New;
		Temp->pPrev = New;
		size++;
	}
	void erase(int Index)
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

	//      Metods
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab <<Temp<< tab<<Temp->Data << tab << Temp->pNext << endl;
		}
	cout << "Колличество элементов списка: " << size << endl;
	}
	void reverse_print()const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Колличество элементов списка: " << size << endl;
	}
};



int main()
{
    setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		list.push_front(rand() % 100);
	}
	list.print();
    //list.reverse_print();
	//list.push_back(888);
	//list.print();
	int index;
	int value;
	cout << "Введите индекс добавляемого элемента: "; cin >> index;
	cout << "Введите значение добавляемого элемента: "; cin >> value;
	list.insert(index, value);
	list.print();
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	list.erase(2);
	list.print();
}