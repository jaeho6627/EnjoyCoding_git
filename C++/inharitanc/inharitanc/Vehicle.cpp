//Vehicle.cpp
#include <iostream>
#include "Vehicle.h"

using namespace std;
//##########################################################################
Vehicle::Vehicle :: Vehicle(int seat) // ����Ʈ �Ű������� ������Ͽ��� �ۼ��Ѵ�.
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
//private �� �ƴ϶� �θ��� ���� ���� ����
{
	cout << "Bick : " << this << endl;
	//Vehicle::Vehicle(seat); //�θ��� �����ڸ� ȣ���� ���� �ƴ϶� ��ü�� �����Ǿ��� ��������.
	//m_nSeat = seat;
}
Bick::~Bick()
{
	cout << "Bick : " << this << endl;
}
//�ڽİ�ü ������ �θ�ü���� �����ǰ� �ڽİ�ü ����
//       �Ҵ����� �� �ڽİ�ü ���� �Ҵ����� �θ�ü �Ҵ�����
//���ñ����̱� ������ �θ�ü �޸𸮸� ���� �����صΰ� �ڽİ�ü ���� -> �Ҵ������� �ݴ�� �ϰ� ��
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