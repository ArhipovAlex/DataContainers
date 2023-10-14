#pragma once
//List.h
#include<iostream>
using namespace std;
using std::cin;
using std::cout;

#define tab "\t"
#define delimiter "\n----------------------\n"

template<typename T>class List
{
	class Element
	{
		T Data;
		Element* pNext;
		Element* pPrev;

	public:
		Element(T Data, Element* pNext = nullptr, Element* pPrev = nullptr);
		~Element();
		friend class List<T>;
	}*Head, * Tail;
	size_t size;
	class ConstBaseIterator
	{
	protected:
		Element* Temp;
	public:
		ConstBaseIterator(Element* Temp = nullptr);
		~ConstBaseIterator();
		bool operator==(const ConstBaseIterator& other)const;
		bool operator!=(const ConstBaseIterator& other)const;
		const T& operator*()const;
	};
public:
	class ConstIterator :public ConstBaseIterator
	{
	public:
		ConstIterator(Element* Temp = nullptr);
		~ConstIterator();
		ConstIterator& operator++();
		ConstIterator& operator++(int);
		ConstIterator& operator--();
		ConstIterator& operator--(int);
	};
	class ConstReverseIterator : public ConstBaseIterator
	{
	public:
		ConstReverseIterator(Element* Temp = nullptr);
		~ConstReverseIterator();
		ConstReverseIterator& operator++();
		ConstReverseIterator operator++(int);
		ConstReverseIterator& operator--();
		ConstReverseIterator operator--(int);
	};
	class Iterator : public ConstIterator
	{
	public:
		Iterator(Element* Temp = nullptr);
		~Iterator();
		T& operator*();
	};
	class ReverseIterator : public ConstReverseIterator
	{
	public:
		ReverseIterator(Element* Temp = nullptr);
		~ReverseIterator();
		T& operator*();
	};
	ConstIterator begin()const;
	ConstIterator end()const;
	ConstReverseIterator rbegin()const;
	ConstReverseIterator rend()const;
	Iterator begin();
	Iterator end();
	ReverseIterator rbegin();
	ReverseIterator rend();

	// Constructors
	List();
	List(const std::initializer_list<T>& il);
	List(const List<T>& other);
	~List();

	//Operators:

	List<T>& operator=(const List<T>& other);
	//Adding Element:
	void push_front(T Data);
	void push_back(T Data);
	void insert(T Data, int Index);
	//Removing Element:
	void pop_front();
	void pop_back();
	void erase(int Index);
	//Methods:
	void print() const;
	void reverse_print() const;
};
template<typename T>List<T> operator+(const List<T>& left, const List<T>& right);
template<typename T>void reverse_print(const List<T>& list);