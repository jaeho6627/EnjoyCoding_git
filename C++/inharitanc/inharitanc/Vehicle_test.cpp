#include <iostream>

using namespace std;
#include "Vehicle.h" // ������� �����

//Abstract : �߻�ȭ
void Abstract(void)
{
	Vehicle object;
	object.display();
	Bick cBick(2);
	cBick.display();
}
void Abstract2(void)
{
	Vehicle object;
	object.display();
	Truck cTruck;
	cTruck.Truck_Display();
	//cTruck.display();
	//�θ� ���� �Լ��� �����ϱ�
	//������ ���� ������ �������ؼ���
	//��ӽ� �θ��� ���������ڸ� �������ش�.
}
void Abstract3(void)
{
	Vehicle object;
	object.display();
	cout << endl;
	Truck truck;
	truck.Truck_Display();
	cout << endl;
	/*MotaCycle Cycle;
	Cycle.Cycle_Display();*/
}
int main(void)
{
	Abstract3();
	return 0;
}