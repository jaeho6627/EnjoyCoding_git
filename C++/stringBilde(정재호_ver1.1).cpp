/*
���ϸ�	:	stringBilde(����ȣ_ver1.1).cpp
���ϸ���	:	string �ش������� stringŬ������ ����� �Ϻ� ī���ؼ� �ۼ�
����������:	2019.09.23
���� : 
1. strlen �� ���� �غ�� �Լ��� Ȱ��
�� ���� : 
2. �Ҹ��� ������ Ȱ���ϱ�
3. ���� ������ Ȱ��
*/

#include <iostream>
#include <string.h>

using namespace std;

//���ڿ� ����, ����(����), 
//�����Ϸ��� ���ڿ� ��ü�� 2�� �̻� ������ ��
//strA�� ������ ���ڿ��� �����ϰ� 
//strA�� strB�� ���� �ɶ� ����

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
		
		//Ŭ���� �̸��� Ȱ���� �����̺��� ������ �� ����
		//getter ���

		string(const char str[])
		{
			/*for (int n_len = 0; str[n_len] != NULL; n_len++)
			{
				len = n_len;
			}*/
			len = strlen(str);		//�����ϸ� �غ�� �Լ� ���

			m_strString = new char[len+1];	//NULL ���� �����ؾ� �� "data"���ڿ� ���̴� 4���� �ڿ� NULL���� �����ϸ� 5
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
		//���� ���� ���ؽ� ���� ��ġ�� �ش��ϴ� ���� ��ȯ
		/*char reChar(int idx)
		{
			return m_strString[idx];
		}*/
		//���ڿ� ���� ��ȯ�ϴ� �Լ�
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
	//�� �Լ��� ���� ����� ������ Ŀ���� ���ڿ� Ŭ���� �����
	StringMain();
	Custom::StringMain();
}