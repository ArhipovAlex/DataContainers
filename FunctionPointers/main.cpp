#include<iostream>
using namespace std;
#define delimiter "\n----------------------\n"

const char* Hello()
{
	return "Hello";
}

int Sum(int a, int b)
{
	return a + b;
}

void main() 
{
	setlocale(LC_ALL, "");
	cout << Hello << endl;
	const char* (*p_hello)();//�������� �� ������� � ����� const char*
	p_hello = Hello;
	cout << p_hello() << endl;//����� ������� ����� ���������
	cout << delimiter;

	int (*p_sum)(int, int) = Sum;
	cout << p_sum(2, 3) << endl;
}