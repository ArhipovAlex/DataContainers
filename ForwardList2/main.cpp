#include<iostream>
using namespace std;
using std::cout;
using std::cin;
#define tab "\t"

class Element
{
	int Data; //значение
	Element* pPrev;//адрес предыдущего
	Element* pNext;//адрес следующего
	static int count;//кол-во элементов в списке
public:
	//Constructors:
	Element(int Data, Element* pPrev = nullptr, Element* pNext = nullptr): Data(Data),pPrev(pPrev),pNext(pNext)
	{
		count++;
		cout << "EConstructor:" << tab << this << endl;
	}
	~Element()
	{
		count--;
		cout << "EDestructor:" << tab << this << endl;
	}
	friend class ForwardList2;
};
int Element::count = 0;

class ForwardList2
{
	Element* Head;
	Element* Tail;
	unsigned int size;
public:
	ForwardList2()
	{
		this->Head = nullptr;
		this->Tail = nullptr;
		this->size = 0;
		cout << "LConstructor:" << tab << this << endl;
	}
	~ForwardList2()
	{
		while (Head) pop_front();
		cout << "LDestructor:" << tab << this << endl;
	}
	//Adding Element:
	void push_front(int Data)
	{
		//1) Создаем элемент
		Element* New = new Element(Data);
		//2) Пристековываем элемент к списку:
		New->pNext = Head;
		//3) Теперьновый элемент является начальным элементом списка:
		Head = New;
		size++;
	}
	void push_back(int Data)
	{
		//1) Создаем элемент
		Element* New = new Element(Data);
		//2) Пристековываем элемент к списку:
		New->pPrev = Tail;
		//3) Теперь новый элемент является конечным элементом списка:
		Tail = New;
		size++;
	}
	//Removing Element:
	void pop_front()
	{
		if (Head == nullptr) return;
		Element* erased = Head;
		Head = Head->pNext;
		delete erased;
		size--;
	}
	void pop_back()
	{
		if (Tail == nullptr)return;
		Element* erased = Tail;
		Tail = Tail->pPrev;
		delete erased;
		size--;
	}
	//Methods
	void print()const
	{
		for (Element* Temp = Head; Temp; Temp = Temp->pNext)
			cout << Temp << tab << Temp->pPrev << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << this->size << endl;
		cout << "Общее количество элементов списка: " << Element::count << endl;
	}
};
#define BASE_CHECK

void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList2 list;
	for (int i = 0; i < n; i++)
	{
		//list.push_back(rand() % 100);
		list.push_front(rand() % 100);
	}
	list.print();

#endif//BASE_CHEKC
}