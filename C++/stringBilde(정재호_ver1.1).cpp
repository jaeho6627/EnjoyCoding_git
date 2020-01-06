/*
���ϸ�	:	stringBilde(����ȣ_ver1.1).cpp
���ϸ���	:	string �ش������� stringŬ������ ����� �Ϻ� ī���ؼ� �ۼ�
����������:	2019.09.23
���� : 
1. strlen �� ���� �غ�� �Լ��� Ȱ��
2. ���� (������)������ Ȱ�� //�̹� �߾���
�� ���� : 
1. ���ڿ� insert �Լ� �����
2. �Ҹ��� ������ Ȱ���ϱ�

*/

#include <iostream>
#include <string.h>
#include <stdlib.h> //�޸� �����Ҵ� ���
#include <crtdbg.h> //�޸� ���� Ž�� ���
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
		int size(void)
		{
			return len;
		}

		//���� ������ : ��ü�� ����ɶ� �Ҹ��� �Լ�
		//�����ڿ� ���� �Ű������� �ڱ��ڽ��� �����ڸ� �޴´�.
		//�⺻������ �޸� ī�ǰ� �Ͼ�Ƿ�, �����Ҵ���������,
		//���� �ٸ� ��ü�� ��������� �����Ҵ��� �����ؾ��Ѵ�.
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

		~string()
		{
			delete m_strString;
		}


		void insert(int idx, const char ch) //�ϼ��ϱ� 
		{
			char* pTemp = new char[strlen(m_strString)+2]; //�߰��� ���� 1, �ι��ڸ� ������ ���� 1 => +2
			strcpy(pTemp, m_strString);	//�ӽ� ���ڿ��� ������ ���ڿ� ����
			cout << "1.insert: " << pTemp << endl;
			strcpy(pTemp + idx + 1, m_strString + idx);//������ ��ġ���� 1ĭ���� ���� ���ڿ� ����
			cout << "2.insert: " << pTemp << endl;
			pTemp[idx] = ch;	//������ ��ġ�� �Է��� ���ڸ� �ִ´�.
			cout << "3.insert: " << pTemp << std::endl;
			delete[] m_strString;	//������ �Ҵ�� �޸𸮸� �����ϰ�
			cout << "Delete preMemory: " << (int)m_strString << endl;
			m_strString = pTemp;	//���� �Ҵ�� �޸𸮷� ��ü�Ѵ�.
			cout << "SwapMemory: " << (int)m_strString << endl;


			//cout << pTemp << endl;
			//pTemp[idx] = ch;
			//delete[] m_strString;
			//m_strString = pTemp;
		}
		//	���۷����� �����ε�
		bool operator ==(string& str)
		{
			if (this == &str)
				return true;
			else
				return false;
		}

		string operator = (string& str) //���ڿ� ���� ������
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
		//���� ��ȯ�� ���� ��ȯ�� �׽�Ʈ�ϰ�, �׽�Ʈ�� ����� �� ������� �ʴ��� �����ϱ�, ����� ������ �Ϳ� �ش��ϴ� �� ���� �����ϱ�
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
	//_CrtSetBreakAlloc(12688); //�޸� ������ ��ȣ�� ������ �Ҵ��ϴ� ��ġ�� �극��ũ ����Ʈ�� �Ǵ�.
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //�޸� ���� �˻� 
	//�� �Լ��� ���� ����� ������ Ŀ���� ���ڿ� Ŭ���� �����
	StringMain();
	Custom::StringMain();
}