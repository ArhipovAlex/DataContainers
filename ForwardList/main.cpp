#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		cout << "EConstructor:\t" << this << endl;
	}
	~Element()
	{
		cout << "EDestructor:\t" << this << endl;
	}
	friend class ForwardList;//даем доступ к приватным полям
};
class ForwardList
{
	//Forward - односвязный, однонаправленный
	Element* Head;
public:
	ForwardList()
	{
		//конструктор по умолчанию создает пустой список
		this->Head = nullptr;//Если список пуст, его Голова указывает на 0.
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		cout << "LDestructor:\t" << this << endl;
	}
	//Adding elements:
	void push_front(int Data)
	{
		//1) Создаем элемент
		Element* New = new Element(Data);
		//2) Пристековываем элемент к списку:
		New->pNext = Head;
		//3) Теперьновый элемент является начальным элементом списка:
		Head = New;
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//1) Создаем элемент
		Element* New = new Element(Data);
		//2) Перебираем весь список, в Temp останется адрес последнего
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;//Переход на следующий элемент списка
		}
		Temp->pNext = New;
	}
	//Methods:
	void print()const
	{
		Element* Temp = Head;//Temp - итератор.
		//Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент списка
		}
	}
};

void main()
{
	setlocale(LC_ALL, "");
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	//list.push_back(999);
	//list.print();
}