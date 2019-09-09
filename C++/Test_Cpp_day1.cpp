/*
파일이름: Test Cpp_day1.cpp
작성자 : 정재호(jhjy5369@naver.com)
마지막작성 : 2019.9.9
*/


/*
c++ 수업
c++ 구조화 프로그래밍 => 객체 지향 언어

객체지향이란 -> 현실을 모델로 반영한 소프트웨어 프로그래밍

객체 지향의 과정
운전 -> 운전자 + 차 -> 모델링

개념
갭슐화 : 데이너와 알고리즘을 하나의 단위(클래스로) 묶는 것
정보 은닉 : 불필요한 접근 막는 것
상속	: 비슷한 코드가 있다면 가져옴
다현성

usingnamespace 의 사용 이유
객체 지향 프로그래밍은 객체들을 조합하여 프로그램을 작성하는 기버버

*/



#include<iostream>
#include <string>
//using namespasece std;
//네임스페이스 : 함수나 전역변수를 구별하고 나누는 것
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

//중복함수(overloading function)
/*
매개 변수의 갯수 또는 졸류가 달라야 됨

..단 리턴, 값이 다른 것은 오버로딩 할 수 없다.

*/
//디폴트 매개변수
/*
인자를 전달하지 않아도 디폴트에 으해 실행됨
//다른 타입의 매개변수나 갯수를 다르게 만듬
매개변수에 기본값을 넣어주는 것, 
뒤에서 부터 차례로 숫자를 채워넣어야한다.
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
//float Add(float a = 0, float b = 0, float c = 0) { return a + b + d; } 자료형이 다르면 오버로딩이 안됨

//인라인 함수 : 함수 호출을 하지 않고 코드를 복사하여서 넣는 것





//:: c++에서 소속을 표현하는데 사용
void main()
{
	A::PrintData();
	B::PrintData();
	std::cout << "printdata : " << Add(10) << std:: endl;
}