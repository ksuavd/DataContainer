#include <iostream>
using namespace std;
using std::cin;
using std::cout;
using std::endl;

#define DEBUG

#define delimiter "\n-----------------------------------------------------\n"
class Tree
{
protected:
    class Element
    {
        int Data;		//Значение элемента
        Element* pLeft; //Левый потомок (адрес)
        Element* pRight; //правый потомк (адрес)
    public:
        Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr)
            :Data(Data), pLeft(pLeft), pRight(pRight)
        {
#ifdef DEBUG
            cout << "EConstructor:\t" << this << endl;
#endif // DEBUG
        }
        ~Element()
        {
#ifdef DEBUG
            cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
        }
        bool isLeaf()const
        {
            return pLeft == pRight;
        }
        friend class Tree;
        friend class UniqueTree;
    }*Root;
public:
    Element* getRoot()
    {
        return Root;
    }
    Tree() :Root(nullptr)
    {
        cout << "TConstructor:\t" << this << endl;
    }
    ~Tree()
    {
        Clear(Root);

        cout << "TDestructor:\t" << this << endl;
    }
    Tree(const Tree& other) :Tree()
    {
        Copy(other.Root);
    }
    Tree(const std::initializer_list<int>& il) :Tree()
    {
        for (int i:il) insert(i);
    }
    void insert(int Data)
    {
        insert(Data, Root);
    }
    void erase(int Data)
    {
        erase(Data, Root);
    }
    int minValue()const
    {
        return minValue(Root);
    }
    int maxValue()const
    {
        return maxValue(Root);
    }

    int Count()const
    {
        return Count(Root);
    }
    int Sum()const
    {
        return Sum(Root);
    }
    int Avg()const
    {
        return (double)Sum(Root)/Count(Root);
    }
    void print()const
    {
        print(Root);
        cout << endl;
    }
    int Depth()const
    {
        return Depth(Root);
    }
    void Clear()
    {
        Clear(Root);
        Root = nullptr;
    }
private:
    void insert(int Data, Element* Root)
    {
        if (this->Root == nullptr)this->Root = new Element(Data);
        if (Root == nullptr)return;//условие для выхода из рекурсии
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
            else insert(Data, Root->pLeft);
        }
        else
        {
            if (Root->pRight == nullptr)Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }
    void erase(int Data, Element*& Root)
    {
        if (Root == nullptr)return;
        erase(Data, Root->pLeft); // обход дерева налево
        erase(Data, Root->pRight);// обход дерева направо
        if (Data == Root->Data)
        {
            if (Root->isLeaf())//(Root->pLeft== Root->pRight)
            {
                delete Root;
                Root = nullptr;
            }
            else 
            {
                if (Count(Root->pLeft) > Count(Root->pRight))//ищем ветку с мак. кол-вом элементов
                {
                    Root->Data = maxValue(Root->pLeft); //ищем макисмальный элмент удаляем
                    erase(maxValue(Root->pLeft), Root->pLeft);
                }
                else // в противном случае 
                {
                    Root->Data = minValue(Root->pRight);
                    erase(minValue(Root->pRight), Root->pRight);
                }
            }
        }
    }
    void print(Element* Root)const
    {
        if (Root == nullptr)return;
        print(Root->pLeft);
        cout << Root->Data << "\t";
        print(Root->pRight);
    }
    int minValue(Element* Root)const
    {
      /*if (Root == nullptr)return 0;
        if (Root->pLeft == nullptr)return Root->Data;
        else
        {
            return minValue(Root->pLeft);
        }*/
        if (Root == nullptr)return Root->Data;
        return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
    }
    int maxValue (Element* Root)const
    {
        if (Root == nullptr)return 0;
        /*if (Root->pRight == nullptr)return Root->Data;
        else
        {
            return maxValue(Root->pRight);
        }*/
        return Root->pRight == nullptr ? Root->Data : maxValue(Root->pRight);
    }
    int Count(Element* Root)const
    {
        if (Root == nullptr)return 0;
        else
        {
            return Count(Root->pLeft) + Count(Root->pRight)+1;// сумма элементов левой ветки + сум.эл - тов правой ветки +первый эл-т
        }
    }
    int Sum(Element* Root)const
    {
        if (Root == nullptr)return 0;
        else
        {
            return Sum(Root->pLeft) + Sum(Root->pRight) + Root->Data;//сумма элементов левой ветки+сум. эл-тов правой ветки+значение текущего элемента
        }
    }
    int Depth(Element* Root) const
    {
        if (Root == nullptr)return 0;

        int l_depth = Depth(Root->pLeft) + 1;
        int r_depth = Depth(Root->pRight) + 1;
        return l_depth > r_depth ? l_depth : r_depth;

        /*
        if (Depth(Root->pLeft) + 1 > Depth(Root->pRight) + 1)return Depth(Root->pLeft) + 1;
        else return Depth(Root->pRight) + 1;*/

        /* return
            Root == nullptr? 0:
            Depth(Root->pLeft)+1 >
            Depth(Root->pRight)+1?
            Depth(Root->pLeft) + 1:
            Depth(Root->pRight) + 1;*/
    }
        void Clear(Element * Root)
        {
            if (Root == nullptr)return;
            Clear(Root->pLeft);
            Clear(Root->pRight);
            delete Root;
        }
        void Copy (Element* Root)
        {
            if (Root == nullptr)return;
            insert(Root->Data, this->Root);
            Copy(Root->pLeft);
            Copy(Root->pRight);
        }
    
};
class UniqueTree :public Tree
{
public:
    void insert(int Data, Element* Root)
    {
        if (this->Root == nullptr)this->Root = new Element(Data);
        if (Root == nullptr)return;
        if (Data < Root->Data)
        {
            if (Root->pLeft == nullptr)Root->pLeft = new Element(Data);
            else insert(Data, Root->pLeft);
        }
        else if (Data > Root->Data)
        {
            if (Root->pRight == nullptr)Root->pRight = new Element(Data);
            else insert(Data, Root->pRight);
        }
    }
};
//#define BASE_CHECK
#define DEPTH_CHECK


int main()
{
    setlocale(LC_ALL, "");
#ifdef BASE_CHECK

    int n;
    cout << "Введите размер дерева: "; cin >> n;
    Tree tree;
    for (int i = 0; i < n; i++)
    {
        tree.insert(rand() % 100);
    }
    tree.print();
    cout << endl;
    cout << "Минимальное значение в дереве: " << tree.minValue() << endl;
    cout << "Максимальное значение в дереве: " << tree.maxValue() << endl;
    cout << "Количество элементов в дереве: " << tree.Count() << endl;
    cout << "Сумма элементов в дереве: " << tree.Sum() << endl;
    cout << "Срденее-арфиметическое значение: " << tree.Avg() << endl;
    cout << "Глубина дерева: " << tree.Depth() << endl;

    cout << delimiter;
    UniqueTree tree2;
   for (int i = 0; i < n; i++)
    {
        tree2.insert(rand() % 100, tree2.getRoot());
    }
    tree2.print();
    cout << endl;
    cout << "Минимальное значение в дереве: " << tree2.minValue() << endl;
    cout << "Максимальное значение в дереве: " << tree2.maxValue() << endl;
    cout << "Количество элементов в дереве: " << tree2.Count() << endl;
    cout << "Сумма элементов в дереве: " << tree2.Sum() << endl;
    cout << "Срденее-арфиметическое значение: " << tree2.Avg() << endl;
    cout << "Глубина дерева: " << tree2.Depth() << endl;
#endif // BASE_CHECK
#ifdef DEPTH_CHECK

    Tree tree = { 50,25,75,16,32,64,80,48,49,58,68,67,85,91};
    tree.print();
    cout << "Глубина дерева: " << tree.Depth() << endl;

  //  Tree tree2 = tree;
   // tree2.print();
#endif // DEPTH_CHECK

    int value;
    cout << "Введите удаляемое значение: "; cin >> value;
    tree.erase(value);
    tree.print();
}

