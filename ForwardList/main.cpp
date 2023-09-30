#include<iostream>
using namespace std;

#define tab "\t"

class Element
{
	int Data;
	Element* pNext;
	static int count; //объявление статической переменной
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
	friend class ForwardList;//даем доступ к приватным полям
};

int Element::count = 0;//определение стат. переменной только вне класса

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
	ForwardList(initializer_list<int> il) :ForwardList()
	{
		//initializer_list - контейнер
		//для хранения других объектов в памяти
		//у initializer_list есть методы begin() и end()
		//begin() - возвращает итератор на начало контейнера;
		//end() - возвращает итератор на конец контейнер;
	}
	~ForwardList()
	{
		while (Element::count) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	//Adding elements:
	void push_front(int Data)
	{
		/*
		//1) Создаем элемент
		Element* New = new Element(Data);
		//2) Пристековываем элемент к списку:
		New->pNext = Head;
		//3) Теперьновый элемент является начальным элементом списка:
		Head = New;*/
		Head = new Element(Data,Head);
	}
	void push_back(int Data)
	{
		if (Head == nullptr) return push_front(Data);
		//1) Создаем элемент
		//Element* New = new Element(Data);
		//2) Перебираем весь список, в Temp останется адрес последнего
		Element* Temp = Head;
		while (Temp->pNext)
		{
			Temp = Temp->pNext;//Переход на следующий элемент списка
		}
		Temp->pNext = new Element(Data);
	}
	void insert(int Data, int Index)
	{
		if (Index == 0) return push_front(Data);
		//1) Создаем новый элемент
		//Element* New = new Element(Data);
		//2) Доходим до нужной позиции
		Element* Temp = Head;
		for (int i = 0; i < Index - 1; i++) 
		{
			if (Temp->pNext == 0)return push_back(Data);
			Temp = Temp->pNext;
		}
		//3) Вставляем новый элемент по указанному индексу
		//New->pNext = Temp->pNext;
		Temp->pNext = new Element(Data, Temp->pNext);
	}
	//Methods:
	void print()const
	{
		/*
		Element* Temp = Head;//Temp - итератор.
		//Итератор - это указатель при помощи которого можно получить доступ к элементам структуры данных.
		while (Temp)
		{
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
			Temp = Temp->pNext;//Переход на следующий элемент списка
		}*/
		for(Element* Temp=Head;Temp;Temp=Temp->pNext)
			cout << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
		cout << "Количество элементов списка: " << Element::count << endl;//к статическим полям принято обращаться через оператор разрешения видимости
	}
	// Removing Element
	void pop_front()
	{
		Element* erased = Head; //1) запоминаем адрес удаляемого
		Head = Head->pNext; //2) Исключаем удаляемый элемент из списка
		delete erased; //3) удаление элемента из памяти
	}
	void pop_back()
	{
		Element* erased = Head;
		while (erased->pNext->pNext)
		{
			erased = erased->pNext;//1) Доходим до предпоследнего элемента			
		}
		delete erased->pNext;//2) Удаляем последний элемент из памяти
		erased->pNext = 0;//3) Обнуляем указатель на последний элемент
	}
	void erase(int Index)
	{
		if (Index == 0) return pop_front();

		Element* erased = Head;
		for (int i = 0; i < Index - 1; i++)
		{
			if (erased->pNext == 0)return pop_back();
			erased = erased->pNext;
		}
		Element* Temp = erased->pNext->pNext;
		delete erased->pNext;		
		erased->pNext = Temp;
	}
	//	Copy-Methods:

};

#define BASE_CHECK
//#define INSERT_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
void main()
{
	setlocale(LC_ALL, "");
#ifdef BASE_CHECK
	int n;
	cout << "Введите размер списка: "; cin >> n;
	ForwardList list;
	for (int i = 0; i < n; i++)
	{
		list.push_back(rand() % 100);
		//list.push_front(rand() % 100);
	}
	list.print();
	list.push_front(123);
	list.print();
	int index;
	cout << "Введите индекс удаляемого элемента: "; cin >> index;
	list.erase(index);
	list.print();
	/*list.push_back(123);
	list.print();*/
	//list.print();
	//list.pop_back();
	//list.print();
#ifdef INSERT_CHECK
	int index;
	int value;
	cout << "Введите индекс нового элемента: "; cin >> index;
	cout << "Введите новый элемент: "; cin >> value;
	list.insert(value, index);
	list.print();
#endif //INSERT_CHECK
#endif//BASE_CHEKC
#ifdef RANGE_BASED_FOR_ARRAY
	int arr[] = { 3,5,8,13,21 };
	for (int i = 0; i < sizeof(arr) / sizeof(arr[0]); i++)
	{
		cout << arr[i]<< tab;
	}
	cout << endl;
	for (int i : arr)
	{
		cout << i << tab;
	}
	cout << endl;
#endif//RANGE_BASED_FOR_ARRAY
#ifdef RANGE_BASED_FOR_LIST
	ForwardList list = { 3,5,8,13,21 };
	list.print();

	for (int i : list)
	{
		cout << i << tab;
	}
	cout << endl;
#endif //RANGE_BASED_FOR_LIST
}