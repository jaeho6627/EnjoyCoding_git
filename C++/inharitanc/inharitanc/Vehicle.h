#pragma once
//Vehicle 헤더파일
#define code_one
class Vehicle
{
	//private:
protected:		// 접근 제한자 : 자식의 접근은 가능하게 함
	int m_nGear;
	int m_nSpeed;
	int m_nSeat;
public:
	Vehicle(int seat = 1);
	~Vehicle();
	void Accel(void);
	void Break(void);
	void Set(int gear);
	void display(void);
};
/*
private : 외부에서 접근 자체를 막는다
public : 외부에서 접근하는 것을 허용한다.
protected : 외부에서 접근하는 것을 막지만, 자식 클래스의 접근 '만' 허용한다.
*/

//자전거 객체 생성
class Bick : public Vehicle	//이미 만들어진 객체의 멤버를 상속 받는 방법 (상속 받는 객체를 자식 객체 , 상속하는 객체를 부모 객체라고 함)
{
	//현실과 다르게 상속받은 부모의 멤버와 자식의 멤버는 선혀 다른 값을 저장할 수 있다.
public:
	Bick(int seat = 1); //private 이 아니라 부모의 값을 변경 못함
	~Bick();
};
#ifdef code_one
//Vehicle 클래스가 메모리에 할당된 후 Engine 순으로 Vehicle가 할당된 메모리를 공유하면서 class가 할당된다.
//계층 상속
class Engine : public Vehicle
{
	int m_nEngine;
public:
	Engine(int Engine = 500, int seat = 1);
	~Engine();
	int getEngine(void) { return m_nEngine; }
	void Engine_Display(void);
};

//트럭 객체 생성
class Truck : public Engine
{
	float m_fWeight;
public:
	Truck(int Engine = 500, int seat = 2, float weight = 1000.0f);
	~Truck();
	//인 라인 함수 :#define으로 올린 성능 향샹 효과를 보기위해 사용하는 기능
	//겟터의 경우 인라인 함수로 만들어 효율을 높인다.
	//인라인 함수는 컴파일러가 함수를 호출할 때 코드로 변경한다.
	float GetWeight() { return m_fWeight; }
	void Truck_Display();
};

//오토바이
class MotaCycle : public Engine
{
public:
	MotaCycle(int Engine = 500, int seat = 1);
	~MotaCycle();
	void Cycle_Display();
};
 // code_one

#else
//다중 상속
//상속하는 순서에 따라 메모리를 할당하는 순서가 다르다
//다중 상속시 상속하는 객체가 따로 메모리를 할당하게 된다.
class Engine
{
	int m_nEngine;
public:
	Engine(int Engine = 500);
	~Engine();
	int getEngine(void) { return m_nEngine; }
	void Engine_Display(void);
};

//트럭 객체 생성
class Truck : public Engine, public Vehicle
{
	float m_fWeight;
public:
	Truck(int Engine = 500, int seat = 2, float weight = 1000.0f);
	~Truck();

	float GetWeight() { return m_fWeight; }
	void Truck_Display();
};

//오토바이
class MotaCycle :  public Vehicle, public Engine  
{
public:
	MotaCycle(int Engine = 500, int seat = 1);
	~MotaCycle();
	void Cycle_Display();
};
// else_code
#endif

//2019.9.30 숙제 
//다중상속시 메모리 할당 순서?
//상속할때 상속하는 순서에 따라 달라진다. class 클래스이름 : 1번상속, 2번상속
//1번 > 2번 > 클래스 이름 순으로 할당
//클래스 이름 > 2번 > 1번 순으로 할당 해제

//계층 상속시 할당 순서
//상속의 순서대로 Vehicle > Engine > MotaCycle 할당 
//할당 해제는 MotaCycle > Engine > Vehicle 순으로 할당 해제

//다중상속의 문제점은 ??
//느려진다/복잡해진다/두 부모의 메모리 할당이 서로 다른 공간에 진행된다.