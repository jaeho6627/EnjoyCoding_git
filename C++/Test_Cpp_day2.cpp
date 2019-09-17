/*
c++ 배열

2차원 배열 배열이름 [y][x]

포인터

뉴와 딜리트 사용하는 이유

참조자

문자열 표현 방식 (string)

객체 지향
- 실제 세계를 모델링하여 프로그래밍

객체 (object)는 상태와 동작을 가지고 있다.
객체의 상태(state)는 객체의 특징값(속성)이다
객체의 동작() 은 함수로 나타낸다.

메시지 : 소프트웨어 객체는 메시지(massage)를 통해 다른 소프트웨어 객체와 통신하고 서로 상호 작용한다.

클래스(class) : 객체를 만드는 설계도
클래스로부터 만들어지는 각각의 객체를 특별히 그 클래스의 인스턴스(instance)라고 한다.

객체 지향 언어 = 자료와 함수를 같이 관리
- 오브젝트를 조합하여 프로그램을 작성

캡슐화(encapsulation)
정보 은닉
상속
다형성 - 객체가 위하는 동작이 상황에 따라 달라지는 것

*/
#include <iostream>
#include <string>
using namespace std;
#define RED 1
#define Blue 2
#define Yello 3
#define Black 4
#define Wight 5

//문자열자료형을 활용하는 코드 ( string )
void String(void)
{
	string strFullName; RED;
	string strLastName = "Jung"; //성
	string strFirstName = "jaeho"; //이름

	strFullName = strLastName + strFirstName;
	int nIdx = strFullName.find(strFirstName);		//해당 문자의 위치를 찾는다(배열에서)
	cout << strLastName << "Find" << nIdx << "["<<strFirstName<<"]"<< endl;
	//string은 배열처럼 사용가능
	for (int i = 0; i < strFullName.size(); i++)
	{
		cout<<strFullName[i];
	}
	cout << endl;
}

enum On_Off { Off=0, On = 1};

//클래스 : 객체를 만드는 설계도
//객체를 생성하는 것 만으로는 메모리를 사용하지 않는다.

//자동차 
class Car
{
public:
	//멤버 변수
	int m_nSpeed;
	string m_strColor;
	int m_nGear;
	On_Off m_On_Off;
	
	//브레이크와 가속은 속도를 확인하기위해 속도를 리턴한다
	//int Accel()
	//{
	//	//클레스 안에 이미 있기 때문에 인자를 전달 받을 필요는 없다.
	//	return ++m_nSpeed;				//복사 연산이 일어나 효율이 떨어진다.
	//}
	//int& Break()					//참조자 사용
	//{
	//	return --m_nSpeed;				//복사 연산 사용 x 대신 외부에서 값을 제어할 수 있다.
	//}
	//멤버 함수

	//호출하지 않아도 객체생성시 호출됨
	//반환값이 없고, 클래스 이름과 동일하다

	Car() //생성자 : 객체가 생성될때 실행하는 함수 ( 객체 생성시 자동으로 호출되는 '함수')
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
	//클래스를 사용할때 객체(인스턴스)를 생성한다 ( ==클래스를 사용할때 메모리를 생성한다)
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
		// 운전 중에는 시동 유지
		cCar.CarState();	//속도판 확인
		cout << "witch do you want - 1 = Accel, 2 = Break, 0 = Packing" << endl;	//탑승자 선택
		cin >> nUserinput;
		cout << endl;

		if (nUserinput == 1) //엑셀을 밟으면 속도가 1씩 증가
			cCar.Accel();
		else if (nUserinput == 2)	//브레이크를 밟으면 속도가 1씩 감소
			cCar.Break();
		else if (cCar.m_nSpeed > 0 && nUserinput == 0)	//스피드가 1이상인 경우 주차할경우 불가능
			cout << "I can't stop now!!" << endl;
		else
		{		// 위 조건을 모두 만족하지 않으면 주차 시동 끔
			cInput = 0;
			cCar.m_On_Off = Off; //시동 종료
		}
		cout << "drive speed : " << cCar.m_nSpeed << endl;
	}
	
	cCar.CarState();
}
//1. 자동차의 색상을 정한다. ( 속도, 기어는 기본으로 설정 되어 있다.)
//1-1 샐행준에 생상을 바꿔야 된다. ( 색상 변수, 입력 )
//2. 공장에서 내가 주문한 색상으로 자동차를 생산한다.
//2-1 설계도를 보고 자동차를 생산한다. ( 객체 생성 )
//2-2 속도, 기어는 기본설정 (0 초기화)
//2-3 주문된 색상으로 자동차의 색상을 정한다.
//3. 생산된 자동차를 내가 운전한다.
//3-1 가속패달을 밟아 속도를 증가 시킨다.
//3-2 브레이크를 밟아 속도를 감소시킨다.


int main(void) {
	//String();
	Car_();
	return 0;
}