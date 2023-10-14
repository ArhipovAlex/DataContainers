//List.cpp
#include"List.h"

///////////////////////////////////////////////
////////////Element member-function////////////
template<typename T>List<T>::Element::Element(T Data, List<T>::Element* pNext, List<T>::Element* pPrev)
	:Data(Data), pNext(pNext), pPrev(pPrev)
{
	cout << "EConstructor:\t" << this << endl;
}
template<typename T>List<T>::Element::~Element()
{
	cout << "EDestructor:\t" << this << endl;
}
////////////Element member-function////////////
///////////////////////////////////////////////

///////////////////////////////////////////////
//////ConstBaseIterator member-functions///////
template<typename T>List<T>::ConstBaseIterator::ConstBaseIterator(List<T>::Element* Temp) : Temp(Temp) {}
template<typename T>List<T>::ConstBaseIterator::~ConstBaseIterator() {}
template<typename T> bool List<T>::ConstBaseIterator::operator==(const List<T>::ConstBaseIterator& other)const
{
	return this->Temp == other.Temp;
}
template<typename T> bool List<T>::ConstBaseIterator::operator!=(const List<T>::ConstBaseIterator& other)const
{
	return this->Temp != other.Temp;
}
template<typename T> const T& List<T>::ConstBaseIterator::operator*()const
{
	return Temp->Data;
}
//////ConstBaseIterator member-functions///////
///////////////////////////////////////////////

///////////////////////////////////////////////
////////ConstIterator member-functions/////////
template<typename T>List<T>::ConstIterator::ConstIterator(List<T>::Element* Temp) :ConstBaseIterator(Temp) {}
template<typename T>List<T>::ConstIterator::~ConstIterator() {}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator++(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstIterator& List<T>::ConstIterator::operator--(int)
{
	ConstIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
////////ConstIterator member-functions/////////
///////////////////////////////////////////////

///////////////////////////////////////////////
/////ConstReverseIterator member-functions/////
template<typename T>List<T>::ConstReverseIterator::ConstReverseIterator(List<T>::Element* Temp) :ConstBaseIterator(Temp) {}
template<typename T>List<T>::ConstReverseIterator::~ConstReverseIterator() {}

template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator++()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator++(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pPrev;
	return old;
}
template<typename T> typename List<T>::ConstReverseIterator& List<T>::ConstReverseIterator::operator--()
{
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return *this;
}
template<typename T> typename List<T>::ConstReverseIterator List<T>::ConstReverseIterator::operator--(int)
{
	ConstReverseIterator old = *this;
	ConstBaseIterator::Temp = ConstBaseIterator::Temp->pNext;
	return old;
}
/////ConstReverseIterator member-functions/////
///////////////////////////////////////////////

///////////////////////////////////////////////
//////////Iterator member-functions////////////
template<typename T>List<T>::Iterator::Iterator(List<T>::Element* Temp) :ConstIterator(Temp) {}
template<typename T>List<T>::Iterator::~Iterator() {}
template<typename T> T& List<T>::Iterator ::operator*()
{
	return ConstBaseIterator::Temp->Data;
}
//////////Iterator member-functions////////////
///////////////////////////////////////////////

///////////////////////////////////////////////
///////ReverseIterator member-functions////////
template<typename T>List<T>::ReverseIterator::ReverseIterator(List<T>::Element* Temp) : ConstReverseIterator(Temp) {}
template<typename T>List<T>::ReverseIterator::~ReverseIterator() {}
template<typename T> T& List<T>::ReverseIterator ::operator*()
{
	return List<T>::ConstBaseIterator::Temp->Data;
}
///////ReverseIterator member-functions////////
///////////////////////////////////////////////

///////////////////////////////////////////////
////////////List member-functions//////////////

template<typename T>typename List<T>::ConstIterator List<T>::begin()const
{
	return Head;
}
template<typename T>typename List<T>::ConstIterator List<T>::end()const
{
	return nullptr;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rbegin()const
{
	return Tail;
}
template<typename T>typename List<T>::ConstReverseIterator List<T>::rend()const
{
	return nullptr;
}
template<typename T>typename List<T>::Iterator List<T>::begin()
{
	return Head;
}
template<typename T>typename List<T>::Iterator List<T>::end()
{
	return nullptr;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rbegin()
{
	return Tail;
}
template<typename T>typename List<T>::ReverseIterator List<T>::rend()
{
	return nullptr;
}
//Constructors:
template<typename T>List<T>::List()
{
	Head = Tail = nullptr;
	size = 0;
	cout << "LConstructor:\t" << this << endl;
}
template<typename T>List<T>::List(const std::initializer_list<T>& il) :List()
{
	for (T const* it = il.begin(); it != il.end(); ++it)
		push_back(*it);
}
template<typename T>List<T>::List(const List<T>& other) : List()
{
	//for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	*this = other;
	cout << "LCopyConstructor:\t" << this << endl;
}
template<typename T>List<T>::~List()
{
	while (Head)pop_front();
	cout << "LDestructor:\t" << this << endl;
}

//Operators:

template<typename T>List<T>& List<T>::operator=(const List<T>& other)
{
	if (this == &other)return *this;
	while (Head)pop_front();
	for (Element* Temp = other.Head; Temp; Temp = Temp->pNext)push_back(Temp->Data);
	cout << "LCopyConstructor:/t" << this << endl;
	return *this;
}
//Adding Element:
template<typename T>void List<T>::push_front(T Data)
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
		Head = Head->pPrev = new Element(Data, Head);
	}
	size++;
}
template<typename T>void List<T>::push_back(T Data)
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
template<typename T>void List<T>::insert(T Data, int Index)
{
	if (Index == 0) return push_front(Data);
	if (Index >= size) return push_back(Data);
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++)Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < size - Index - 1; i++)Temp = Temp->pPrev;
	}
	Element* New = new Element(Data);
	New->pNext = Temp;
	New->pPrev = Temp->pPrev;
	Temp->pPrev->pNext = New;
	Temp->pPrev = New;
	size++;
}
//Removing Element:
template <typename T>void List<T>::pop_front()
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
	size--;
}
template<typename T>void List<T>::pop_back()
{
	if (Head == Tail) return pop_front();
	Tail = Tail->pPrev;
	delete Tail->pNext;
	Tail->pNext = nullptr;
	size--;
}
template <typename T>void List<T>::erase(int Index)
{
	if (Index == 0) return pop_front();
	if (Index == size - 1) return pop_back();
	if (Index >= size)return;
	Element* Temp;
	if (Index < size / 2)
	{
		Temp = Head;
		for (int i = 0; i < Index; i++) Temp = Temp->pNext;
	}
	else
	{
		Temp = Tail;
		for (int i = 0; i < Index; i++) Temp = Temp->pPrev;
	}
	//Temp указывает на нужный элемент
	//1) нужно исключить элемент из списка
	Temp->pPrev->pNext = Temp->pNext;
	Temp->pNext->pPrev = Temp->pPrev;
	//2) удаляем элемент из списка
	delete Temp;
	size--;
}
//Methods:
template <typename T>void List<T>::print() const
{
	for (Element* Temp = Head; Temp; Temp = Temp->pNext)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
template<typename T>void List<T>::reverse_print() const
{
	for (Element* Temp = Tail; Temp; Temp = Temp->pPrev)
	{
		cout << Temp->pPrev << tab << Temp << tab << Temp->Data << tab << Temp->pNext << endl;
	}
	cout << "Количество элементов списка: " << size << endl;
}
////////////List member-functions//////////////
///////////////////////////////////////////////

template<typename T>List<T> operator+(const List<T>& left, const List<T>& right)
{
	List<T> cat = left;
	for (typename List<T>::ConstIterator it = right.begin(); it != right.end(); ++it)
	{
		//*it *= 10;
		cat.push_back(*it);
	}
	return cat;
}

template<typename T>void reverse_print(const List<T>& list)
{
	for (typename List<T>::ConstReverseIterator it = list.rbegin(); it != list.rend(); ++it)
	{
		cout << *it << tab;
	}
	cout << endl;
}