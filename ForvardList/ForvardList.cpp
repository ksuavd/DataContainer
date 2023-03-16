#include "ForwardList.cpp"

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