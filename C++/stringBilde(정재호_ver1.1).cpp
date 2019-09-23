/*
파일명	:	stringBilde(정재호_ver1.1).cpp
파일목적	:	string 해더파일의 string클래스의 기능을 일부 카피해서 작성
마지막수정:	2019.09.23
보완 : 
1. strlen 과 같은 준비된 함수를 활용
미 보완 : 
2. 소멸자 생성해 활용하기
3. 복사 연산자 활용
*/

#include <iostream>
#include <string.h>

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
	};

	void StringMain()
	{
		string strA = "Data";
		string strB = strA;
		cout << strA.c_str() << endl;
		cout << strB.c_str() << endl;
	}
}

int main()
{
	//두 함수가 같은 결과를 내도록 커스텀 문자열 클래스 만들기
	StringMain();
	Custom::StringMain();
}