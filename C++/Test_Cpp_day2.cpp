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
	//멤버 변수
	int m_nSpeed;
	string m_strColor;
	int m_nGear;
	//객체 지향에서 은닉한 data에 잘못된 접근을 막는 용도
public: //접근 제한자(제어자) . public, private , protected
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

	//Car() //생성자 : 객체가 생성될때 실행하는 함수 ( 객체 생성시 자동으로 호출되는 '함수')
	//{//기본 생성자
	//	cout << "Gear & Speed : RESET" << endl;
	//	m_nGear = 0;
	//	m_nSpeed = 0;
	//	m_On_Off = Off;
	//	m_strColor = choiceColor();
	//}
	//Car(string color) //오버로딩 가능
	//{
	//	cout << "Gear & Speed : RESET" << endl;
	//	m_nGear = 0;
	//	m_nSpeed = 0;
	//	m_On_Off = Off;
	//	m_strColor = color;
	//}
	Car(string color = "gray", int speed = 0, int gear = 0, On_Off staus = Off) //디폴트 생성자로 모두 대처가 가능하다
	{
		cout << "Gear & Speed : RESET" << endl;
		m_nGear = speed;
		m_nSpeed = gear;
		m_On_Off = staus;
		m_strColor = color;
	}
	/*
<c++ setter getter>
setter : 은닉된 멤버변수의 값을 설정하는 것
getter : 은닉된 멤버변수의 값을 가져오는 것
public이어야 함
*/

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
	//setter 함수
	
	void CarState(void)
	{
		cout << "###################################" << endl;
		cout << "Car Color : " << m_strColor << endl;
		cout << "Car Gear : " << m_nGear << endl;
		cout << "Car on-off" << m_On_Off << endl;
		cout << "###################################" << endl << endl;
	}
	//getter 함수
	int Returnspeed()
	{
		return m_nSpeed;
	}
};
/*  검색 방법
1. c++은닉 -> 은닉의 개념에 대한 설명
2. 내가 은닉하려고 하는 것은 => 속도, c++클래스 멤버 변수
							=> c++멤버변수 은닉 => private을 사용
#내가 해야할 것을 전문용어로 구체적으로 표현가능해야한다.
*/
string choiceColor(void)
{
	int colorcode = 0;
	cout << "Choice Color [ 1 = RED, 2 = Blue, 3 = Yello, 4 = Black, 5 = Wight ]" << endl;
	cin >> colorcode;

	switch (colorcode)
	{
	case RED:
		return "RED";
	case Blue:
		return "BLUE";
	case Yello:
		return "YELLO";
	case Black:
		return "BLACK";
	case Wight:
		return "WIGHT";
	};
}
void Car_()
{
	//클래스를 사용할때 객체(인스턴스)를 생성한다 ( ==클래스를 사용할때 메모리를 생성한다)
	Car cCar(choiceColor());
	//Car cCar();
	char cInput = 0;
	int nUserinput = 0;
	

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
		else if (cCar.Returnspeed() > 0 && nUserinput == 0)	//스피드가 1이상인 경우 주차할경우 불가능
			cout << "I can't stop now!!" << endl;
		else
		{		// 위 조건을 모두 만족하지 않으면 주차 시동 끔
			cInput = 0;
			cCar.m_On_Off = Off; //시동 종료
		}
		cout << "drive speed : " << cCar.Returnspeed() << endl;
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

/*
캡슐화 : 나타낼 대상의 속성과 동작을 변수와 함수로 묶어서 클래스로 표현
은닉 : 나타낼 대상의 접근을 제한되어야 할 경우 사용
*/