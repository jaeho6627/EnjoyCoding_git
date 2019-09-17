/*
c++ �迭

2���� �迭 �迭�̸� [y][x]

������

���� ����Ʈ ����ϴ� ����

������

���ڿ� ǥ�� ��� (string)

��ü ����
- ���� ���踦 �𵨸��Ͽ� ���α׷���

��ü (object)�� ���¿� ������ ������ �ִ�.
��ü�� ����(state)�� ��ü�� Ư¡��(�Ӽ�)�̴�
��ü�� ����() �� �Լ��� ��Ÿ����.

�޽��� : ����Ʈ���� ��ü�� �޽���(massage)�� ���� �ٸ� ����Ʈ���� ��ü�� ����ϰ� ���� ��ȣ �ۿ��Ѵ�.

Ŭ����(class) : ��ü�� ����� ���赵
Ŭ�����κ��� ��������� ������ ��ü�� Ư���� �� Ŭ������ �ν��Ͻ�(instance)��� �Ѵ�.

��ü ���� ��� = �ڷ�� �Լ��� ���� ����
- ������Ʈ�� �����Ͽ� ���α׷��� �ۼ�

ĸ��ȭ(encapsulation)
���� ����
���
������ - ��ü�� ���ϴ� ������ ��Ȳ�� ���� �޶����� ��

*/
#include <iostream>
#include <string>
using namespace std;
#define RED 1
#define Blue 2
#define Yello 3
#define Black 4
#define Wight 5

//���ڿ��ڷ����� Ȱ���ϴ� �ڵ� ( string )
void String(void)
{
	string strFullName; RED;
	string strLastName = "Jung"; //��
	string strFirstName = "jaeho"; //�̸�

	strFullName = strLastName + strFirstName;
	int nIdx = strFullName.find(strFirstName);		//�ش� ������ ��ġ�� ã�´�(�迭����)
	cout << strLastName << "Find" << nIdx << "["<<strFirstName<<"]"<< endl;
	//string�� �迭ó�� ��밡��
	for (int i = 0; i < strFullName.size(); i++)
	{
		cout<<strFullName[i];
	}
	cout << endl;
}

enum On_Off { Off=0, On = 1};

//Ŭ���� : ��ü�� ����� ���赵
//��ü�� �����ϴ� �� �����δ� �޸𸮸� ������� �ʴ´�.

//�ڵ��� 
class Car
{
public:
	//��� ����
	int m_nSpeed;
	string m_strColor;
	int m_nGear;
	On_Off m_On_Off;
	
	//�극��ũ�� ������ �ӵ��� Ȯ���ϱ����� �ӵ��� �����Ѵ�
	//int Accel()
	//{
	//	//Ŭ���� �ȿ� �̹� �ֱ� ������ ���ڸ� ���� ���� �ʿ�� ����.
	//	return ++m_nSpeed;				//���� ������ �Ͼ ȿ���� ��������.
	//}
	//int& Break()					//������ ���
	//{
	//	return --m_nSpeed;				//���� ���� ��� x ��� �ܺο��� ���� ������ �� �ִ�.
	//}
	//��� �Լ�

	//ȣ������ �ʾƵ� ��ü������ ȣ���
	//��ȯ���� ����, Ŭ���� �̸��� �����ϴ�

	Car() //������ : ��ü�� �����ɶ� �����ϴ� �Լ� ( ��ü ������ �ڵ����� ȣ��Ǵ� '�Լ�')
	{
		cout << "Gear & Speed : RESET" << endl;
		m_nGear = 0;
		m_nSpeed = 0;
		m_On_Off = Off;
	}
	int Accel()
	{
		if (!(m_nSpeed % 2))
			m_nGear++;
		return ++m_nSpeed;				
	}
	int Break()					
	{
		if (m_nSpeed%2&&!(m_nSpeed==0))
			m_nGear--;
		return --m_nSpeed;				
	}
	void choiceColor(void)
	{
		int colorcode = 0;
		cout << "Choice Color [ 1 = RED, 2 = Blue, 3 = Yello, 4 = Black, 5 = Wight ]" << endl;
		cin >> colorcode;

		switch (colorcode)
		{
		case RED:
			m_strColor = "RED";
			break;
		case Blue:
			m_strColor = "BLUE";
			break;
		case Yello:
			m_strColor = "YELLO";
			break;
		case Black:
			m_strColor = "BLACK";
			break;
		case Wight:
			m_strColor = "WIGHT";
			break;
		};
	}
	void CarState(void)
	{
		cout << "###################################" << endl;
		cout << "Car Color : " << m_strColor << endl;
		cout << "Car Gear : " << m_nGear << endl;
		cout << "Car on-off" << m_On_Off << endl;
		cout << "###################################" << endl << endl;
	}
};

void Car_()
{
	//Ŭ������ ����Ҷ� ��ü(�ν��Ͻ�)�� �����Ѵ� ( ==Ŭ������ ����Ҷ� �޸𸮸� �����Ѵ�)
	Car cCar;
	char cInput = 0;
	int nUserinput = 0;
	cCar.choiceColor();

	cout << "Do you ride a car? " << "1 = YES, 0 = NO" << endl;
	cin >> cInput;
	cout << endl;
	if (cInput)
		cCar.m_On_Off = On;
	while (cCar.m_On_Off)
	{
		// ���� �߿��� �õ� ����
		cCar.CarState();	//�ӵ��� Ȯ��
		cout << "witch do you want - 1 = Accel, 2 = Break, 0 = Packing" << endl;	//ž���� ����
		cin >> nUserinput;
		cout << endl;

		if (nUserinput == 1) //������ ������ �ӵ��� 1�� ����
			cCar.Accel();
		else if (nUserinput == 2)	//�극��ũ�� ������ �ӵ��� 1�� ����
			cCar.Break();
		else if (cCar.m_nSpeed > 0 && nUserinput == 0)	//���ǵ尡 1�̻��� ��� �����Ұ�� �Ұ���
			cout << "I can't stop now!!" << endl;
		else
		{		// �� ������ ��� �������� ������ ���� �õ� ��
			cInput = 0;
			cCar.m_On_Off = Off; //�õ� ����
		}
		cout << "drive speed : " << cCar.m_nSpeed << endl;
	}
	
	cCar.CarState();
}
//1. �ڵ����� ������ ���Ѵ�. ( �ӵ�, ���� �⺻���� ���� �Ǿ� �ִ�.)
//1-1 �����ؿ� ������ �ٲ�� �ȴ�. ( ���� ����, �Է� )
//2. ���忡�� ���� �ֹ��� �������� �ڵ����� �����Ѵ�.
//2-1 ���赵�� ���� �ڵ����� �����Ѵ�. ( ��ü ���� )
//2-2 �ӵ�, ���� �⺻���� (0 �ʱ�ȭ)
//2-3 �ֹ��� �������� �ڵ����� ������ ���Ѵ�.
//3. ����� �ڵ����� ���� �����Ѵ�.
//3-1 �����д��� ��� �ӵ��� ���� ��Ų��.
//3-2 �극��ũ�� ��� �ӵ��� ���ҽ�Ų��.


int main(void) {
	//String();
	Car_();
	return 0;
}