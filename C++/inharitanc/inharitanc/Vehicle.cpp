//Vehicle.cpp
#include <iostream>
#include "Vehicle.h"

using namespace std;
//##########################################################################
Vehicle::Vehicle :: Vehicle(int seat) // 디폴트 매개변수는 헤더파일에만 작성한다.
{
	cout << "Vehicle : " << this << endl << "value check" << seat << endl;
	m_nGear = 0;
	m_nSpeed = 0;
	m_nSeat = seat;
}
Vehicle::Vehicle :: ~Vehicle() {
	cout << "Vehicle : " << this << endl<<endl;
}

void Vehicle::Vehicle :: Accel(void)
{
	m_nSpeed += 10;
}

void Vehicle::Vehicle::Break(void)
{
	m_nSpeed -= 10;
}
void Vehicle::Vehicle::Set(int gear)
{
	m_nGear = gear;
}
void Vehicle::Vehicle:: display(void)
{
	cout << "Display>>>>>>>>>>" << endl;
	cout << "Gear : " << m_nGear << endl;
	cout << "Speed : " << m_nSpeed << endl;
	cout << "Seat : " << m_nSeat << endl;
	cout << ">>>>>>>>>>>>>>>>" << endl;
}
//##########################################################################
Bick::Bick(int seat) : Vehicle(seat)
//private 이 아니라 부모의 값을 변경 못함
{
	cout << "Bick : " << this << endl;
	//Vehicle::Vehicle(seat); //부모의 생성자를 호출한 것이 아니라 객체가 생성되었다 지워진다.
	//m_nSeat = seat;
}
Bick::~Bick()
{
	cout << "Bick : " << this << endl;
}
//자식객체 생성시 부모객체먼저 생성되고 자식객체 생성
//       할당해제 시 자식객체 먼저 할당해제 부모객체 할당해제
//스택구조이기 때문에 부모객체 메모리를 먼저 생성해두고 자식객체 생성 -> 할당해제는 반대로 하게 됨
//##########################################################################
#ifdef code_one
Engine::Engine(int Engine, int seat):Vehicle(seat)
{
	cout << "Engine : " << this << endl;
	m_nEngine = Engine;
}
Engine::~Engine()
{
	cout << "Engine : " << this << endl;
}
void Engine::Engine_Display(void)
{
	cout << "Engine : " << m_nEngine << endl;
}
//##########################################################################
Truck::Truck(int Engine, int seat, float weight) : Engine(Engine, seat)
{
	cout << "Truck" << this << " " << seat << "  " << weight << endl;
	m_fWeight = weight;
}
Truck::~Truck()
{
	cout << "Truck : " << this << endl;
}

void Truck::Truck_Display()
{
	Vehicle::display();
	Engine_Display();
	cout << "Weight : " << m_fWeight << endl;
}
//##########################################################################

MotaCycle::MotaCycle(int Engine , int seat): Engine(Engine, seat)
{
	cout << "MotaCycle : " << this << " " << seat << endl;
}
MotaCycle::~MotaCycle()
{
	cout << "MotaCycle : " << this << endl;
}
void MotaCycle::Cycle_Display()
{
	Vehicle::display();
	Engine_Display();
}
//##########################################################################
#else
Engine::Engine(int Engine)
{
	cout << "Engine : " << this << endl;
	m_nEngine = Engine;
}
Engine::~Engine()
{
	cout << "Engine : " << this << endl;
}
void Engine::Engine_Display(void)
{
	cout << "Engine : " << m_nEngine << endl;
}
//##########################################################################
Truck::Truck(int Engine, int seat, float weight) : Engine(Engine),Vehicle(seat)
{
	cout << "Truck" << this << " " << seat << "  " << weight << endl;
	m_fWeight = weight;
}
Truck::~Truck()
{
	cout << "Truck : " << this << endl;
}

void Truck::Truck_Display()
{
	Vehicle::display();
	Engine_Display();
	cout << "Weight : " << m_fWeight << endl;
}
//##########################################################################

MotaCycle::MotaCycle(int Engine, int seat) : Engine(Engine),Vehicle(seat)
{
	cout << "MotaCycle : " << this << " " << seat << endl;
}
MotaCycle::~MotaCycle()
{
	cout << "MotaCycle : " << this << endl;
}
void MotaCycle::Cycle_Display()
{
	Vehicle::display();
	Engine_Display();
}
//##########################################################################
#endif