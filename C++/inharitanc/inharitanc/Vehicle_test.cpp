#include <iostream>

using namespace std;
#include "Vehicle.h" // 헤더파일 만들기

//Abstract : 추상화
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
	//부모가 가진 함수에 접근하기
	//다음과 같은 접근을 막기위해서는
	//상속시 부모의 접근지정자를 변경해준다.
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