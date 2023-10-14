#include <iostream>
using namespace std;

#define tab "\t"

class Tree
{
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
	}*Root;
public:
	Element* getRoot()
	{
		return Root;
	}
	Tree()
	{
		Root = nullptr;
		cout << "TConstructor:\t" << this << endl;
	}
	~Tree()
	{
		cout << "TDestructor:\t" << this << endl;
	}

	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
	void print(Element* Root)
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	int minValue(Element* Root)
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		minValue(Root->pLeft);*/
		return Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		maxValue(Root->pRight);*/
		return Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int Sum(Element* Root)
	{
		/*if (Root == nullptr)return 0;
		else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);*/
		return Root ? Root->Data + Sum(Root->pLeft) + Sum(Root->pRight) : 0;
	}
	int Count(Element* Root)
	{
		/*if (Root == nullptr)return 0;
		else return 1 + Count(Root->pLeft) + Count(Root->pRight);*/
		return Root==nullptr? 0: 1 + Count(Root->pLeft) + Count(Root->pRight);
	}
	double AVG()
	{
		return (double)Sum(Root)/Count(Root);
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер дерева: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100, tree.getRoot());
	}
	tree.print(tree.getRoot());
	cout << endl;
	cout << "Минимальное значение в дереве: " << tree.minValue(tree.getRoot()) << endl;
	cout << "Максимальное значение в дереве: " << tree.maxValue(tree.getRoot()) << endl;
	cout << "Сумма элементов дерева: " << tree.Sum(tree.getRoot()) << endl;
	cout << "Количество элементов дерева: " << tree.Count(tree.getRoot()) << endl;
	cout << "Среднее арифметическое элементов дерева: " << tree.AVG() << endl;

}