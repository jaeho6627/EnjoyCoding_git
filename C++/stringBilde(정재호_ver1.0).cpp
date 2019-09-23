/*
���ϸ�	:	stringBilde(����ȣ_ver1.0).cpp
���ϸ���	:	string �ش������� stringŬ������ ����� �Ϻ� ī���ؼ� �ۼ�
����������:	2019.09.23
*/

#include <iostream>

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
			for (int n_len = 0; str[n_len] != NULL; n_len++)
			{
				len = n_len;
			}
			len++;

			m_strString = new char[len+1];	//NULL ���� �����ؾ� �� "data"���ڿ� ���̴� 4���� �ڿ� NULL���� �����ϸ� 5
			for (int i = 0; i <= len; i++)
			{
				m_strString[i] = str[i];
			}
		}
		string(string& str)
		{
			len = str.reLen();

			m_strString = new char[len+1];
			for (int i = 0; i <= len; i++)
			{
				m_strString[i] = str.reChar(i);
			}
		}
		const char* c_str()
		{
			return m_strString;
		}
		//���� ���� ���ؽ� ���� ��ġ�� �ش��ϴ� ���� ��ȯ
		char reChar(int idx)
		{
			return m_strString[idx];
		}
		//���ڿ� ���� ��ȯ�ϴ� �Լ�
		int reLen()
		{
			return len;
		}
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