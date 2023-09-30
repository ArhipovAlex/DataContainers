#include<iostream>
using namespace std;

#define tab "\t"
//#define DEBUG

class Element
{
	int Data;
	Element* pNext;
	static int count; //объявление статической переменной
public:
	Element(int Data, Element* pNext = nullptr) : Data(Data), pNext(pNext)
	{
		count++;
#ifdef DEBUG
		cout << "EConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Element()
	{
		count--; 
#ifdef DEBUG
		cout << "EDestructor:\t" << this << endl;
#endif // DEBUG
	}
	friend class ForwardList;//даем доступ к приватным полям
	friend class Iterator;//даем доступ к приватным полям
};

int Element::count = 0;//определение стат. переменной только вне класса

class Iterator
{
	Element* Temp;
public:
	Iterator(Element* Temp = nullptr) :Temp(Temp)
	{
#ifdef DEBUG
		cout << "ITConstructor:\t" << this << endl;
#endif // DEBUG

	}
	~Iterator()
	{
#ifdef DEBUG
		cout << "ITDestructor:\t" << this << endl; 
#endif // DEBUG
	}
	Iterator(const Iterator& other)
	{
		this->Temp = other.Temp;
#ifdef DEBUG
		cout << "ItCopyConstructor:\t" << this << endl;
#endif // DEBUG

	}
	Iterator& operator++()
	{
		Temp = Temp->pNext;
		return *this;
	}
	Iterator& operator++(int)
	{
		Iterator old = *this;
		Temp = Temp->pNext;
		return old;
	}
	bool operator==(const Iterator& other)const
	{
		return this->Temp == other.Temp;
	}	
	bool operator!=(const Iterator& other)const
	{
		return this->Temp != other.Temp;
	}
	int operator*()
	{
		return Temp->Data;
	}
};

class ForwardList
{
	//Forward - односвязный, однонаправленный
	Element* Head;
	unsigned int size;
public:
	//type name (parameters)
	Iterator begin()
	{
		return Head;
	}
	Iterator end()
	{
		return nullptr;
	}
	ForwardList()
	{
		//конструктор по умолчанию создает пустой список
		this->Head = nullptr;//Если список пуст, его Голова указывает на 0.
		this->size = 0;
		cout << "LConstructor:\t" << this << endl;
	}
	ForwardList(const initializer_list<int>& il) :ForwardList()
	{
		//initializer_list - контейнер
		//для хранения других объектов в памяти
		//у initializer_list есть методы begin() и end()
		//begin() - возвращает итератор на начало контейнера;
		//end() - возвращает итератор на конец контейнер;
		cout << typeid(il.begin()).name() << endl;
		for (int const* it = il.begin(); it!= il.end(); ++it)
		{
			push_back(*it);
		}
	}
	ForwardList(const ForwardList& other) :ForwardList()
	{
		//this - этот список
		//other - тот список
		for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)
			push_back(Temp->Data);
		cout << "LConstructor:\t" << this << endl;
	}
	~ForwardList()
	{
		while (Head) pop_front();
		cout << "LDestructor:\t" << this << endl;
	}
	/*ForwardList(const ForwardList& a):ForwardList()
	{
		cout << "CopyConstructor:\t" << this << endl;
		Element* Temp = Head;
		while (Temp->pNext) new Element(Temp->Data, Temp->pNext);
	}*/
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
		size++;
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
		size++;
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
		size++;
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
		cout << "Количество элементов списка: " << this->size << endl;//к статическим полям принято обращаться через оператор разрешения видимости
		cout << "Общее количество элементов списка: " << Element::count << endl;//к статическим полям принято обращаться через оператор разрешения видимости
	}
	// Removing Element
	void pop_front()
	{
		if (Head == nullptr)return;
		Element* erased = Head; //1) запоминаем адрес удаляемого
		Head = Head->pNext; //2) Исключаем удаляемый элемент из списка
		delete erased; //3) удаление элемента из памяти
		size--;
	}
	void pop_back()
	{
		size--;
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
			if (erased== 0)return;
			erased = erased->pNext;
		}
		Element* Temp = erased->pNext->pNext;
		delete erased->pNext;		
		erased->pNext = Temp;
		size--;
	}
	ForwardList& operator=(const ForwardList& a)
	{
#ifdef DEBUG
		cout << "CopyAssigment:\t" << this << endl;
#endif // DEBUG

		Element* Temp = Head;
		while (Temp->pNext)
		{
			
		}
		return *this;
	}
};

//#define BASE_CHECK
//#define INSERT_CHECK
//#define RANGE_BASED_FOR_ARRAY
//#define RANGE_BASED_FOR_LIST
#define COPY_METHODS_CHECK
#define FORWARD_LIST_PREFORMANCE_TEST

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

	for (Iterator it = list.begin(); it != list.end(); ++it)
	{
		cout << *it << endl;
	}
	cout << endl;
#endif //RANGE_BASED_FOR_LIST

#ifdef COPY_METHODS_CHECK
	ForwardList list1 = { 3,5,8,13,21 };
	for (int i : list1)cout << i << tab; cout << endl;
	
	ForwardList list2 = list1;//Copy constructor
	for (int i : list2)cout << i << tab; cout << endl;

#endif //COPY_METHODS_CHECK

}