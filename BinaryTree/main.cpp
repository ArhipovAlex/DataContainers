#include <iostream>
#include <ctime>
#include <chrono>
using namespace std;
using namespace chrono;
using std::cin;
using std::cout;
using std::endl;
using std::string;

#define tab "\t"

class Tree
{
protected:
	class Element
	{
		int Data;
		Element* pLeft;
		Element* pRight;
	public:
		Element(int Data, Element* pLeft = nullptr, Element* pRight = nullptr) :Data(Data), pLeft(pLeft), pRight(pRight)
		{
			//cout << "EConstructor:\t" << this << endl;
		}
		~Element()
		{
			//cout << "EDestructor:\t" << this << endl;
		}
		friend class Tree;
		friend class UniqueTree;
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
	Tree(const std :: initializer_list<int>& il) :Tree()
	{
		for (int const* it = il.begin(); it != il.end(); ++it)
			insert(*it, Root);

	}
	~Tree()
	{
		clear(Root);
		cout << "TDestructor:\t" << this << endl;
	}
	void insert(int Data)
	{
		insert(Data, Root);
	}
	void tree_print()const
	{
		tree_print(0,this->depth());
	}
	void print()const
	{
		print(Root);
		cout << endl;
	}
	void balance()
	{
		balance(this->Root);
	}
	int depth()const
	{
		return depth(Root);
	}
	int minValue()const
	{
		return minValue(Root);
	}
	int maxValue()const
	{
		return maxValue(Root);
	}
	int sum()const
	{
		return sum(Root);
	}
	int count()const
	{
		return count(Root);
	}
	double avg()const
	{
		return (double)sum(Root) / count(Root);
	}
	void clear()
	{
		clear(Root);
		Root = nullptr;
	}
	void erase(int Data)
	{
		erase(Data, Root);
	}
	void measure()const
	{
		return measure();
	}
	void chrono_measure()
	{
		return chrono_measure();
	}
	void depth_print(int Data)const
	{
		depth_print( Root,Data);
	}
private:

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
	void clear(Element* Root)
	{
		if (Root == nullptr)return;
		clear(Root->pLeft);
		clear(Root->pRight);
		delete Root;
	}
	int depth(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		if (depth(Root->pLeft) + 1 > depth(Root->pRight) + 1)return depth(Root->pLeft) + 1;
		else return depth(Root->pRight) + 1;*/
		//if (Root == nullptr)return 0;
		/*return Root == nullptr ? 0 :
			depth(Root->pLeft) + 1 > depth(Root->pRight) + 1 ?
			depth(Root->pLeft) + 1:
			depth(Root->pRight) + 1;*/
		if (Root == nullptr)return 0;
		int l_depth = depth(Root->pLeft) + 1;
		int r_depth = depth(Root->pRight) + 1;
		return l_depth > r_depth ? l_depth : r_depth;
	}
	void depth_print(Element* Root, int depth, int width=4)const
	{
		if (Root == nullptr)
		{
			//*cout.width(width);	
			cout << string(pow(2,width), '  ');
			cout << "  ";
			cout << string(pow(2, width)-2, '  ');
			if (depth > 0)
			{
				cout << string(pow(2, width), '  ');
				cout << "  ";
				cout << string(pow(2, width)-2, '  ');
			}
			return;
		}
		if (depth == 0)
		{
			//*cout.width(width); cout << "";
			cout << string(pow(2, width), '  ');
			cout <<Root->Data;
			//*cout.width(width);	cout << "";
			cout << string(pow(2, width)-2, '  ');
			return;
		}
		
		depth_print(Root->pLeft, depth -1, width);
		//cout.width(width); cout << "";
		depth_print(Root->pRight, depth -1, width);
		//cout << "  ";
		//cout.width(width); cout << "";
	}
	void print(Element* Root)const
	{
		if (Root == nullptr)return;
		print(Root->pLeft);
		cout << Root->Data << tab;
		print(Root->pRight);
	}
	void tree_print(int depth, int width)const
	{

		if (depth == this->depth()) 
		{
			//cout.width(width); cout << "";
			return;
		}
		depth_print(this->Root,depth,width - depth);
		cout << endl;
		cout << endl;
		tree_print(depth + 1, width);
	}
	void balance(Element* Root)
	{
		if (Root == nullptr)return;
		if (abs(count(Root->pLeft) - count(Root->pRight)) < 2)return;
		if (count(Root->pLeft) > count(Root->pRight))
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Root->Data);
			else insert(Root->Data, Root->pRight);
			Root->Data = maxValue(Root->pLeft);
			erase(maxValue(Root->pLeft), Root->pLeft);
		}
		else
		{
			if (Root->pLeft == nullptr)Root->pLeft = new Element(Root->Data);
			else insert(Root->Data, Root->pLeft);
			Root->Data = minValue(Root->pRight);
			erase(minValue(Root->pRight), Root->pRight);
		}
		balance(Root->pLeft);
		balance(Root->pRight);
		balance(Root);
	}
	void erase(int Data, Element*& Root)
	{
		if (Root == nullptr)return;	
		erase(Data, Root->pLeft);
		erase(Data, Root->pRight);
		if (Data == Root->Data)
		{
			if (Root->pLeft == Root->pRight)
			{
				delete Root;
				Root = nullptr;
			}
			else
			{
				if (count(Root->pLeft) > count(Root->pRight))
				{
					Root->Data = maxValue(Root->pLeft);
					erase(maxValue(Root->pLeft), Root->pLeft);
				}
				else
				{
					Root->Data = minValue(Root->pRight);
					erase(minValue(Root->pRight), Root->pRight);
				}
			}
		}
	}
	int minValue(Element* Root)const
	{
		/*if (Root->pLeft == nullptr)return Root->Data;
		minValue(Root->pLeft);*/
		return Root==nullptr? 0: Root->pLeft == nullptr ? Root->Data : minValue(Root->pLeft);
	}
	int maxValue(Element* Root)const
	{
		/*if (Root->pRight == nullptr)return Root->Data;
		maxValue(Root->pRight);*/
		return Root == nullptr ? 0 : Root == nullptr ? 0 : Root->pRight ? maxValue(Root->pRight) : Root->Data;
	}
	int sum(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return Root->Data + Sum(Root->pLeft) + Sum(Root->pRight);*/
		return Root == nullptr ? 0 : Root ? Root->Data + sum(Root->pLeft) + sum(Root->pRight) : 0;
	}
	int count(Element* Root)const
	{
		/*if (Root == nullptr)return 0;
		else return 1 + Count(Root->pLeft) + Count(Root->pRight);*/
		return Root == nullptr ? 0 : Root==nullptr? 0: 1 + count(Root->pLeft) + count(Root->pRight);
	}

};

class UniqueTree :public Tree
{
	void insert(int Data, Element* Root)
	{
		if (this->Root == nullptr)this->Root = new Element(Data);
		if (Root == nullptr)return;
		if (Data < Root->Data)
		{
			if (Root->pLeft == nullptr) Root->pLeft = new Element(Data);
			else insert(Data, Root->pLeft);
		}
		else if (Data>Root->Data)
		{
			if (Root->pRight == nullptr)Root->pRight = new Element(Data);
			else insert(Data, Root->pRight);
		}
	}
public:
	void insert(int Data)
	{
		insert(Data, Root);
	}
};

template <typename T> void measure(const char msg[],T(Tree::*function)()const, const Tree& tree)
{
	cout << msg;
	clock_t start = clock();
	T value = (tree.*function)();
	clock_t end = clock();
	cout << value<<", ��������� �� " << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
}

template <typename T> void chrono_measure(const char msg[], T(Tree::* function)()const, const Tree& tree)
{
	cout << msg;
	high_resolution_clock::time_point start = high_resolution_clock::now();
	T value = (tree.*function)();
	high_resolution_clock::time_point end = high_resolution_clock::now();
	duration<double> sec = end - start;
	cout.setf(ios::fixed);  // ����� � ������������� ������� 
	cout.precision(8);      // ����� �� 6 ����� ����� �����, ������������
	cout << value << ", ��������� �� " << sec.count() << " ������" << endl;
}
//#define BASE_CHECK
//#define PREFORMANCE_CHECK_1
//#define MEASURE_CHECK
//#define CHRONO_CHECK
//#define UNIQUE_CHECK
//#define ERASE_CHECK
//#define DEPTH_CHECK
#define BALANCE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	/*
	int n;
	cout << "������� ������ ������: "; cin >> n;
	Tree tree;
	for (int i = 0; i < n; i++)
	{
		tree.insert(rand() % 100);
	}
	*/
	Tree tree = { 50,25,76,16,32,64,90,15,17,91,98 };
	tree.tree_print();
	cout << endl;
	
	/*
	int value;
	cout << "������� ������� ������: "; cin >> value;
	cout << "�������� �� ������: ";
	tree.depth_print(value);
	cout << endl;*/
#ifdef PREFORMANCE_CHECK_1
	clock_t start = clock();//���������� ���-�� ������ ����������
	cout << "����������� �������� � ������: " << tree.minValue() << ", ��������� �� ";
	clock_t end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;

	start = clock();
	cout << "������������ �������� � ������: " << tree.maxValue() << ", ��������� �� ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
	
	start = clock();
	cout << "����� ��������� ������: " << tree.sum() << ", ��������� �� ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
	
	start = clock();
	cout << "���������� ��������� ������: " << tree.count() << ", ��������� �� ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
	
	start = clock();
	cout << "������� �������������� ��������� ������: " << tree.avg() << ", ��������� �� ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
	
	start = clock();
	cout << "������� ������: " << tree.depth() << ", ��������� �� ";
	end = clock();
	cout << double(end - start) / CLOCKS_PER_SEC << " ������" << endl;
#endif //PREFORMANCE_CHECK_1

#ifdef MEASURE_CHECK
	measure("����������� �������� � ������: ", &Tree::minValue, tree);
	measure("������������ �������� � ������: ", &Tree::maxValue, tree);
	measure("����� ��������� ������: ", &Tree::sum, tree);
	measure("���������� ��������� ������: ", &Tree::count, tree);
	measure("������� �������������� ��������� ������: ", &Tree::avg, tree);
	measure("������� ������: ", &Tree::depth, tree);
	int value;
	//cout << "������� ������� ������: "; cin >> value;
	//cout << "�������� �� ������: ";
	//tree.depth_print(value);
	cout << endl;
#endif //CHRONO_CHECK

#ifdef CHRONO_CHECK
	chrono_measure("����������� �������� � ������: ", &Tree::minValue, tree);
	chrono_measure("������������ �������� � ������: ", &Tree::maxValue, tree);
	chrono_measure("����� ��������� ������: ", &Tree::sum, tree);
	chrono_measure("���������� ��������� ������: ", &Tree::count, tree);
	chrono_measure("������� �������������� ��������� ������: ", &Tree::avg, tree);
	chrono_measure("������� ������: ", &Tree::depth, tree);
#endif //CHRONO_CHECK

#endif //BASE_CHECK

#ifdef UNIQUE_CHECK
	UniqueTree u_tree;
	for (int i = 0; i < n; i++)
	{
		u_tree.insert(rand() % 100);
	}
	u_tree.print();
	cout << "����������� �������� � ������: " << u_tree.minValue() << endl;
	cout << "������������ �������� � ������: " << u_tree.maxValue() << endl;
	cout << "����� ��������� ������: " << u_tree.sum() << endl;
	cout << "���������� ��������� ������: " << u_tree.count() << endl;
	cout << "������� �������������� ��������� ������: " << u_tree.avg() << endl;
#endif //UNIQUE_CHECK

#ifdef ERASE_CHECK
	//Tree tree = { 50,25,76,16,32,64,90 };
	//Tree tree = { 5,8,2,6,7,9,10,1,3,4 };
//	tree.print();
//	cout << endl;

	int value;
	cout << "������� ��������� ��������: "; cin >> value;
	tree.erase(value);
	cout << "���������� ��������� ������: " << tree.count() << endl;
	tree.print();
	cout << endl;
#endif //ERASE_CHECK

#ifdef DEPTH_CHECK
	Tree tree = 
	{ 
					50,
			25,				75,
		16,		32,		64,		90 
	};
	cout << "������� ������: " << tree.depth() << endl;
#endif //DEPTH_CHECK

#ifdef BALANCE_CHECK
	Tree tree = { 55,34,21,13,8,5,3};
	tree.tree_print();
	tree.balance();
    tree.tree_print();
#endif //BALANCE_CHECK
}