#pragma once
//Vehicle �������
#define code_one
class Vehicle
{
	//private:
protected:		// ���� ������ : �ڽ��� ������ �����ϰ� ��
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
private : �ܺο��� ���� ��ü�� ���´�
public : �ܺο��� �����ϴ� ���� ����Ѵ�.
protected : �ܺο��� �����ϴ� ���� ������, �ڽ� Ŭ������ ���� '��' ����Ѵ�.
*/

//������ ��ü ����
class Bick : public Vehicle	//�̹� ������� ��ü�� ����� ��� �޴� ��� (��� �޴� ��ü�� �ڽ� ��ü , ����ϴ� ��ü�� �θ� ��ü��� ��)
{
	//���ǰ� �ٸ��� ��ӹ��� �θ��� ����� �ڽ��� ����� ���� �ٸ� ���� ������ �� �ִ�.
public:
	Bick(int seat = 1); //private �� �ƴ϶� �θ��� ���� ���� ����
	~Bick();
};
#ifdef code_one
//Vehicle Ŭ������ �޸𸮿� �Ҵ�� �� Engine ������ Vehicle�� �Ҵ�� �޸𸮸� �����ϸ鼭 class�� �Ҵ�ȴ�.
//���� ���
class Engine : public Vehicle
{
	int m_nEngine;
public:
	Engine(int Engine = 500, int seat = 1);
	~Engine();
	int getEngine(void) { return m_nEngine; }
	void Engine_Display(void);
};

//Ʈ�� ��ü ����
class Truck : public Engine
{
	float m_fWeight;
public:
	Truck(int Engine = 500, int seat = 2, float weight = 1000.0f);
	~Truck();
	//�� ���� �Լ� :#define���� �ø� ���� �⼧ ȿ���� �������� ����ϴ� ���
	//������ ��� �ζ��� �Լ��� ����� ȿ���� ���δ�.
	//�ζ��� �Լ��� �����Ϸ��� �Լ��� ȣ���� �� �ڵ�� �����Ѵ�.
	float GetWeight() { return m_fWeight; }
	void Truck_Display();
};

//�������
class MotaCycle : public Engine
{
public:
	MotaCycle(int Engine = 500, int seat = 1);
	~MotaCycle();
	void Cycle_Display();
};
 // code_one

#else
//���� ���
//����ϴ� ������ ���� �޸𸮸� �Ҵ��ϴ� ������ �ٸ���
//���� ��ӽ� ����ϴ� ��ü�� ���� �޸𸮸� �Ҵ��ϰ� �ȴ�.
class Engine
{
	int m_nEngine;
public:
	Engine(int Engine = 500);
	~Engine();
	int getEngine(void) { return m_nEngine; }
	void Engine_Display(void);
};

//Ʈ�� ��ü ����
class Truck : public Engine, public Vehicle
{
	float m_fWeight;
public:
	Truck(int Engine = 500, int seat = 2, float weight = 1000.0f);
	~Truck();

	float GetWeight() { return m_fWeight; }
	void Truck_Display();
};

//�������
class MotaCycle :  public Vehicle, public Engine  
{
public:
	MotaCycle(int Engine = 500, int seat = 1);
	~MotaCycle();
	void Cycle_Display();
};
// else_code
#endif

//2019.9.30 ���� 
//���߻�ӽ� �޸� �Ҵ� ����?
//����Ҷ� ����ϴ� ������ ���� �޶�����. class Ŭ�����̸� : 1�����, 2�����
//1�� > 2�� > Ŭ���� �̸� ������ �Ҵ�
//Ŭ���� �̸� > 2�� > 1�� ������ �Ҵ� ����

//���� ��ӽ� �Ҵ� ����
//����� ������� Vehicle > Engine > MotaCycle �Ҵ� 
//�Ҵ� ������ MotaCycle > Engine > Vehicle ������ �Ҵ� ����

//���߻���� �������� ??
//��������/����������/�� �θ��� �޸� �Ҵ��� ���� �ٸ� ������ ����ȴ�.