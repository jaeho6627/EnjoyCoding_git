/*
�����̸�: Test Cpp_day1.cpp
�ۼ��� : ����ȣ(jhjy5369@naver.com)
�������ۼ� : 2019.9.9
*/


/*
c++ ����
c++ ����ȭ ���α׷��� => ��ü ���� ���

��ü�����̶� -> ������ �𵨷� �ݿ��� ����Ʈ���� ���α׷���

��ü ������ ����
���� -> ������ + �� -> �𵨸�

����
����ȭ : ���̳ʿ� �˰����� �ϳ��� ����(Ŭ������) ���� ��
���� ���� : ���ʿ��� ���� ���� ��
���	: ����� �ڵ尡 �ִٸ� ������
������

usingnamespace �� ��� ����
��ü ���� ���α׷����� ��ü���� �����Ͽ� ���α׷��� �ۼ��ϴ� �����

*/



#include<iostream>
#include <string>
//using namespasece std;
//���ӽ����̽� : �Լ��� ���������� �����ϰ� ������ ��
namespace A
{
	int g_nData = 10;
	void PrintData()
	{
		std::cout << "Data" << g_nData << std::endl;

	}
}
namespace B
{
	int g_nData = 20;
	void PrintData()
	{
		std::cout << "Data" << g_nData << std::endl;
		//cout<<"DATA"<<g_nData<<endl;
	}
}

//�ߺ��Լ�(overloading function)
/*
�Ű� ������ ���� �Ǵ� ������ �޶�� ��

..�� ����, ���� �ٸ� ���� �����ε� �� �� ����.

*/
//����Ʈ �Ű�����
/*
���ڸ� �������� �ʾƵ� ����Ʈ�� ���� �����
//�ٸ� Ÿ���� �Ű������� ������ �ٸ��� ����
�Ű������� �⺻���� �־��ִ� ��, 
�ڿ��� ���� ���ʷ� ���ڸ� ä���־���Ѵ�.
*/
/*int Add(int a, int b, int c)*/
//{
//	return a + b + c;
//}
//int Add(int a, int b)
//{
//	int c = 0;
//	return a + b + c;
//}
//int  Add(int a)void Add(int a, int b)
//{
//	int b=0, c = 0;
//	return a + b + c;
//}
//int  Add(int a, int b)
//{
//	int a=0, b=0, c = 0;
//	return a + b + c;
//}
int Add(int a = 0, int b = 0, int c = 0) 
{ 
	return a + b + c; 
}
//float Add(float a = 0, float b = 0, float c = 0) { return a + b + d; } �ڷ����� �ٸ��� �����ε��� �ȵ�

//�ζ��� �Լ� : �Լ� ȣ���� ���� �ʰ� �ڵ带 �����Ͽ��� �ִ� ��





//:: c++���� �Ҽ��� ǥ���ϴµ� ���
void main()
{
	A::PrintData();
	B::PrintData();
	std::cout << "printdata : " << Add(10) << std:: endl;
}