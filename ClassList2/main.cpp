#include<iostream>
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
	size_t size;
public:
	List()
	{
		Head = Tail = nullptr;
		size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	~List()
	{
		while (Head)pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//Adding Element:
	void push_front(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pNext = Head;
			Head->pPrev = New;
			Head = New;*/
			Head = Head->pPrev = new Element(Data,Head);
		}
		size++;
	}
	void push_back(int Data)
	{
		if (Head == nullptr && Tail == nullptr)
		{
			Head = Tail = new Element(Data);
		}
		else
		{
			/*Element* New = new Element(Data);
			New->pPrev = Tail;
			Tail->pNext = New;
			Tail = New;*/
			Tail = Tail->pNext = new Element(Data, nullptr, Tail);
		}
		size++;
	}
	//Removing Element:
	void pop_front()
	{
		if (Head == nullptr && Tail == nullptr)return;
		if (Head == Tail)
		{
			delete Head;
			Head = Tail = nullptr;
			return;
		}
		Head = Head->pNext;
		delete Head->pPrev;
		Head->pPrev = nullptr;
	}
	//Methods:
	void print() const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
		{
			cout << Temp->pPrev << tab << Temp << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}
	void reverse_print() const
	{
		for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
		{
			cout << Temp->pPrev << tab << Temp << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		}
		cout << "Количество элементов списка: " << size << endl;
	}

};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	List list;
	for (int i = 0; i < n; i++)
	{
		//list.push_front(rand() % 100);
		list.push_back(rand() % 100);
	}
	list.print();
	cout << endl;
	list.reverse_print();
}