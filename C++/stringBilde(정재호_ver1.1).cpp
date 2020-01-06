/*
파일명	:	stringBilde(정재호_ver1.1).cpp
파일목적	:	string 해더파일의 string클래스의 기능을 일부 카피해서 작성
마지막수정:	2019.09.23
보완 : 
1. strlen 과 같은 준비된 함수를 활용
2. 복사 (연산자)생성자 활용 //이미 했었음
미 보완 : 
1. 문자열 insert 함수 만들기
2. 소멸자 생성해 활용하기

*/

#include <iostream>
#include <string.h>
#include <stdlib.h> //메모리 동적할당 헤더
#include <crtdbg.h> //메모리 누수 탐지 헤더
using namespace std;

//문자열 생성, 복사(대입), 
//복사하려면 문자열 객체를 2개 이상 만들어야 함
//strA를 생성시 문자열을 지정하고 
//strA를 strB가 생성 될때 복사

void StringMain()
{
	string strA = "Data";
	string strB = strA;
	cout << strA.c_str() << endl;
	cout << strB.c_str() << endl;
	if (&strB.operator=(strA.c_str()))
	{
		cout << "==" << endl;
	}
	else
	{
		cout << "!=" << endl;
	}
}

namespace Custom
{
	class string
	{
		char* m_strString;
		int len;
	public:
		
		//클래스 이름을 활용해 프라이빗에 접근할 수 없음
		//getter 사용

		string(const char str[])
		{
			/*for (int n_len = 0; str[n_len] != NULL; n_len++)
			{
				len = n_len;
			}*/
			len = strlen(str);		//가능하면 준비된 함수 사용

			m_strString = new char[len+1];	//NULL 문자 저장해야 함 "data"문자열 길이는 4지만 뒤에 NULL까지 포함하면 5
			/*for (int i = 0; i <= len; i++)
			{
				m_strString[i] = str[i];
			}*/
			memcpy(m_strString, str, len+1);
		}
		int size(void)
		{
			return len;
		}

		//복사 생성자 : 객체가 복사될때 불리는 함수
		//생성자와 같고 매개변수가 자기자신의 참조자를 받는다.
		//기본적으로 메모리 카피가 일어나므로, 동적할당했을때는,
		//서로 다른 객체로 만들기위해 동적할당을 실행해야한다.
		string(string& str)
		{
			/*len = str.reLen();*/
			len = strlen(str.c_str());

			m_strString = new char[len+1];
			/*for (int i = 0; i <= len; i++)
			{
				m_strString[i] = str.reChar(i);
			}*/
			memcpy(m_strString, str.c_str(), len + 1);
		}
		const char* c_str()
		{
			return m_strString;
		}
		//전달 받은 인텍스 값의 위치에 해당하는 문자 반환
		/*char reChar(int idx)
		{
			return m_strString[idx];
		}*/
		//문자열 길이 반환하는 함수
		/*int reLen()
		{
			return len;
		}*/

		~string()
		{
			delete m_strString;
		}


		void insert(int idx, const char ch) //완성하기 
		{
			char* pTemp = new char[strlen(m_strString)+2]; //추가할 문자 1, 널문자를 저장할 공간 1 => +2
			strcpy(pTemp, m_strString);	//임시 문자열에 복사할 문자열 복사
			cout << "1.insert: " << pTemp << endl;
			strcpy(pTemp + idx + 1, m_strString + idx);//선택한 위치에서 1칸띄우고 원래 문자열 저장
			cout << "2.insert: " << pTemp << endl;
			pTemp[idx] = ch;	//선택한 위치에 입력할 문자를 넣는다.
			cout << "3.insert: " << pTemp << std::endl;
			delete[] m_strString;	//기존에 할당된 메모리를 삭제하고
			cout << "Delete preMemory: " << (int)m_strString << endl;
			m_strString = pTemp;	//현재 할당된 메모리로 교체한다.
			cout << "SwapMemory: " << (int)m_strString << endl;


			//cout << pTemp << endl;
			//pTemp[idx] = ch;
			//delete[] m_strString;
			//m_strString = pTemp;
		}
		//	오퍼레이터 오버로딩
		bool operator ==(string& str)
		{
			if (this == &str)
				return true;
			else
				return false;
		}

		string operator = (string& str) //문자열 복사 연산자
		{
			delete[] m_strString;
			int size = strlen(str.c_str());
			m_strString = new char[size + 1];
			strcpy(m_strString, str.c_str());
			return *this;
		}
		char* operator[] (int i)
		{
			return *(this)->m_strString[i];
		}

		char* operator+(string& str)
		{
			char* ReturnC = NULL;
			ReturnC = new char[this->len + str.len - 1];
			strcpy(ReturnC, this->m_strString);
			strcpy(ReturnC[this->len - 1], str.m_strString);

		}
		//참조 교환과 값의 교환을 테스트하고, 테스트한 결과가 왜 적용되지 않는지 설명하기, 설명시 설명한 것에 해당하는 용어에 대해 정리하기
	};

	void StringMain()
	{
		string strA = "Data";
		string strB = strA;
		cout << strA.c_str() << endl;
		cout << strB.c_str() << endl;

		strB.insert(0, 'A');
		cout << strA.c_str() << endl;
		cout << strB.c_str() << endl;
		if (strB.operator==(strA))
		{
			cout << "==" << endl;
		}
		else
		{
			cout << "!=" << endl;
		}
		cout << "end" << endl;
		strA = strB;
		cout << strA.c_str() << endl;
		cout << strB.c_str() << endl;
		for (int i = 0; i < strB.size(); i++)
			cout << strA[i];
		cout << strB + strA << endl;
	}
}

int main()
{
	//_CrtSetBreakAlloc(12688); //메모리 누수시 번호를 넣으면 할당하는 위치에 브레이크 포인트를 건다.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //메모리 누수 검사 
	//두 함수가 같은 결과를 내도록 커스텀 문자열 클래스 만들기
	StringMain();
	Custom::StringMain();
}