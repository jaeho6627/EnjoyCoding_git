#include <iostream>
#include <vector>   //�迭
#include <list>		//����Ʈ
#include <deque>	//ť
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
/*
���ϸ�: STLTEST.cpp
���ϸ���: STL ����غ���
�ۼ���: ����ȣ
������ ���� : 2019.9.7
//������: �� �ȵǴ��� ���ذ� �ȵ�....
�� �����ؾ���...
*/
using namespace std;


template<typename T>
void PrintContainer(const T& con)
{
	typename T::const_iterator it = con.begin();
	for (; it != con.end(); it++)
	{
		cout << *it << ", ";
	}
	cout << endl;
}
//
//int inputdata(void) //�迭
//{
//	int data = 0;
//	cout << "Input data size: ";
//	cin >> data;
//	return data;
//}
//
//void Printcontainer(vector<int>vec) 
//{
//	vector<int>::iterator it = vec.begin();
//	for (; it != vec.end(); it++) 
//	{
//		cout << *it << ",";
//	}
//	cout << endl;
//}
////vector : ���� �迭(runtime�� ���� �Ҵ簡�� �Ѱ�): �����߿� ũ�⸦ ���� �� �� �ִ� �迭
////void VecInsert(vector<int> &vec, int a, int data)
////{
////	cout << "Insert " << data << endl;
////	vector<int>::iterator it = *vec.begin;
////	vec.insert(it + a, data);
////
////}
//
//void printdata(vector<int> &vec)
//{
//	Printcontainer(vec);
//	cout << "Size: " << vec.size() << endl;
//}
////���ͷ����� : �ݺ��� : STL�� �����̳�(Vector)�� ���ۺ��� ������ �ݺ������� ��.
////�����Ϳ� �����ϰ� �����Ѵ�. ( �׷��ٰ� �����ʹ� �ƴϴ�. )
//
//void vecHightest(vector<int> &vec)
//{
//	int highest = vec[0];
//	for (int i = 0; i < vec.size(); i++)
//	{
//		if (vec[i] > highest)
//			highest = vec[i];
//	}
//	cout << "HighestScore: " << highest << endl;
//}
//
//void stlvector(void)
//{
//	vector<int> scores(inputdata());
//
//	for (int i = 0; i < scores.size(); i++)
//	{
//		scores[i] = i;
//	}
//	cout << endl;
//
//	cout << "Push 7"<<endl;
//	scores.push_back(7);    //�������� 7�߰�
//	vecHightest(scores);
//	printdata(scores);
//	cout << endl;
//
//	
//
//
//	//VecInsert(scores, 2, 9);		//���� �ּ� + sizeof(int) +2 �ڸ��� 9�߰�
//	vecHightest(scores);
//	printdata(scores);
//	cout << endl;
//
//
//
//	cout << "POP end" << endl;
//	scores.pop_back();		//�������� ����
//	vecHightest(scores);
//	printdata(scores);
//	cout << endl;
//
//	//end()�� ������ ���Ұ� ������ �ּҸ� ����Ų��.
//
//	printdata(scores);
//}
////###########################################################################################################################
//
//
//void Printlist(list<int>vec) //����Ʈ
//{
//	list<int>::iterator it = vec.begin();
//	for (; it != vec.end(); it++)
//	{
//		cout << *it << ",";
//	}
//	cout << endl;
//}
//
//void listHightest(list<int> &vec)
//{
//	int highest = vec.front();
//	list<int>::iterator it = vec.begin();
//	for (int i = 0; i < vec.size(); i++)
//	{
//		if (*it > highest)
//			highest = *it;
//	}
//	cout << "HighestScore: " << highest << endl;
//}
//
//
//void printdata_list(list<int> &vec)
//{
//	Printcontainer(vec);
//	cout << "Size: " << vec.size() << endl;
//}
//
//void listInsert(list<int> &vec, int a, int data)
//{
//	cout << "Insert " << data << endl;
//	vec.insert(vec.begin() , data);
//}
//
//
//
////List : ���߿��Ḯ��Ʈ : ���� ���, ���� ��� �̵��� ����.
//void stlList(void)
//{
//	list<int> scores(inputdata());
//	//����Ʈ
//
//	for (int i = 0; i < scores.size(); i++)
//	{
//		scores.push_back(i);
//	}
//	cout << endl;
//
//	cout << "Push 7" << endl;
//	scores.push_back(7);    //�������� 7�߰�
//	listHightest(scores);
//	printdata_list(scores);
//	cout << endl;
//
//
//
//
//	//VecInsert(scores, 2, 9);		//���� �ּ� + sizeof(int) +2 �ڸ��� 9�߰�
//	listHightest(scores);
//	printdata_list(scores);
//	cout << endl;
//
//
//
//	cout << "POP end" << endl;
//	scores.pop_back();		//�������� ����
//	listHightest(scores);
//	printdata_list(scores);
//	cout << endl;
//
//	//end()�� ������ ���Ұ� ������ �ּҸ� ����Ų��.
//
//
//
//
//
//	printdata_list(scores);
//}
//
//
////#####################################################################################################################3
//
//
//void Printdeque(deque<int> vec) //�迭
//{
//	list<int>::iterator it = vec.begin ;
//	for (; it != vec.end; it++)
//	{
//		cout << *it << ",";
//	}
//	cout << endl;
//}
//
//void dequeHightest(deque<int> &vec)
//{
//	int highest = vec.front();
//	list<int>::iterator it = vec.begin;
//	for (int i = 0; i < vec.size(); i++)
//	{
//		if (*it > highest)
//			highest = *it;
//	}
//	cout << "HighestScore: " << highest << endl;
//}
//
//
//void printdata_deque(deque<int> vec)
//{
//	Printcontainer(vec);
//	cout << "Size: " << vec.size() << endl;
//}
//
//void dequeInsert(deque<int> &vec, int a, int data)
//{
//	cout << "Insert " << data << endl;
//	vec.insert(vec.begin(), data);
//}
//
//
//
////deque: ť�� ����� �ݴ�� ����ϴ� �� ( �տ����� �߰� ������ )
//void stldeque(void)
//{
//	deque<int> scores(inputdata());
//	//����Ʈ
//
//	for (int i = 0; i < scores.size(); i++)
//	{
//		scores[i]=i;
//	}
//	cout << endl;
//
//	cout << "Push 7" << endl;
//	scores.push_back(7);    //�������� 7�߰�
//	dequeHightest(scores);
//	printdata_deque(scores);
//	cout << endl;
//
//
//
//
//	//VecInsert(scores, 2, 9);		//���� �ּ� + sizeof(int) +2 �ڸ��� 9�߰�
//	dequeHightest(scores);
//	printdata_deque(scores);
//	cout << endl;
//
//
//
//	cout << "POP end" << endl;
//	scores.pop_back();		//�������� ����
//	dequeHightest(scores);
//	printdata_deque(scores);
//	cout << endl;
//
//	//end()�� ������ ���Ұ� ������ �ּҸ� ����Ų��.
//
//
//
//
//
//	printdata_deque(scores);
//}
//#############################################################################################################
void SetTest(void) //����-�� ����Ʈ��
{ //set �� multiset�� ���̴� �ߺ����� �����ϰ� ���ϰ��� �����̴�.
	set<int> setData;
	setData.insert(1);
	setData.insert(2);
	setData.insert(3);
	//���� ���� �߰� ���� �ʴ´�.

	set<int>::iterator it;
	it = setData.find(2);

	PrintContainer(setData);
	if (it != setData.end())
		cout << "Find: " << *it << endl;
}

//������ ���� ������ ��� insert ���
//������ ������ �ʴ� ����-�� ����Ʈ���� �̿��Ѵ�.
//����-�� ����Ʈ���� �̿��ϱ� ������ ���ĵ��� ���� ���� �����ϸ� ������ ���� ����.

//###################################################################################################################3
void MapTest(void)			//Ű���� Ȱ���� ����-�� ����Ʈ��
{
	map<string, string> dic;
	dic["boy"] = "�ҳ�";
	dic["school"] = "�б�";
	dic["office"] = "����";
	dic["house"] = "��";
	dic["moring"] = "��ħ";
	dic["evening"] = "����";
	dic["end"] = "��";


	cout << "Size" << dic.size() << endl;
	//PrintContainer(dic);

	cout << dic["boy"] << endl;
	cout << dic["none"] << endl;

	map<int, int> mapArray;
	mapArray[0] = 1;
}
//c#������ ��ųʸ� ��� �Ѵ�.
//############################################################################################################################################
void StackTest(void) //����Ʈ ( ��������)
{
	stack<string> st;
	string sayings[3] = { "The grass is preener on the other side of the fence",
	"Even the greatest make mistakes",
	"To see is to believe" };

	for (int i = 0; i < 3; ++i)
		st.push(sayings[i]);
	while (!st.empty())
	{
		cout << st.top() << endl;
		st.pop();
	}
	return;
}
//###########################################################################################################################################
void QueTest(void) //����Ʈ ( ���� ����)
{
	queue<int> que;
	que.push(100);
	que.push(200);
	que.push(300);
	while (!que.empty())
	{
		cout << que.front() << endl;
		que.pop();
	}
}
//############################################################################################################################################3
void PQueTest(void)  //���� ū ������ ���  //�ִ� ��Ʈ�� Ȱ�� 
{
	priority_queue<int> que;
	que.push(100);
	que.push(300);
	que.push(200);
	while (!que.empty())
	{
		cout << que.top() << endl;
		que.pop();
	}
}
int main(void) 
{
	//stlvector();
	//stlList();
	//stldeque();
	//SetTest();
	//MapTest();
	//StackTest();
	//QueTest();
	PQueTest();
	return 0;
}


