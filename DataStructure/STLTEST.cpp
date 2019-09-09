#include <iostream>
#include <vector>   //배열
#include <list>		//리스트
#include <deque>	//큐
#include <set>
#include <map>
#include <string>
#include <stack>
#include <queue>
/*
파일명: STLTEST.cpp
파일목적: STL 사용해보기
작성자: 정재호
마지막 수정 : 2019.9.7
//한줄평: 왜 안되는지 이해가 안됨....
더 공부해야지...
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
//int inputdata(void) //배열
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
////vector : 동적 배열(runtime에 공간 할당가능 한것): 실행중에 크기를 변결 할 수 있는 배열
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
////이터레이터 : 반복자 : STL의 컨테이너(Vector)의 시작부터 끝까지 반복가능한 것.
////포인터와 유사하게 동작한다. ( 그렇다고 포인터는 아니다. )
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
//	scores.push_back(7);    //마지막에 7추가
//	vecHightest(scores);
//	printdata(scores);
//	cout << endl;
//
//	
//
//
//	//VecInsert(scores, 2, 9);		//시작 주소 + sizeof(int) +2 자리에 9추가
//	vecHightest(scores);
//	printdata(scores);
//	cout << endl;
//
//
//
//	cout << "POP end" << endl;
//	scores.pop_back();		//마지막을 제거
//	vecHightest(scores);
//	printdata(scores);
//	cout << endl;
//
//	//end()는 마지막 원소가 끝나는 주소를 가르킨다.
//
//	printdata(scores);
//}
////###########################################################################################################################
//
//
//void Printlist(list<int>vec) //리스트
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
////List : 이중연결리스트 : 이전 노드, 다음 노드 이동이 쉽다.
//void stlList(void)
//{
//	list<int> scores(inputdata());
//	//리스트
//
//	for (int i = 0; i < scores.size(); i++)
//	{
//		scores.push_back(i);
//	}
//	cout << endl;
//
//	cout << "Push 7" << endl;
//	scores.push_back(7);    //마지막에 7추가
//	listHightest(scores);
//	printdata_list(scores);
//	cout << endl;
//
//
//
//
//	//VecInsert(scores, 2, 9);		//시작 주소 + sizeof(int) +2 자리에 9추가
//	listHightest(scores);
//	printdata_list(scores);
//	cout << endl;
//
//
//
//	cout << "POP end" << endl;
//	scores.pop_back();		//마지막을 제거
//	listHightest(scores);
//	printdata_list(scores);
//	cout << endl;
//
//	//end()는 마지막 원소가 끝나는 주소를 가르킨다.
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
//void Printdeque(deque<int> vec) //배열
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
////deque: 큐의 기능을 반대로 사용하는 것 ( 앞에서도 추가 가능함 )
//void stldeque(void)
//{
//	deque<int> scores(inputdata());
//	//리스트
//
//	for (int i = 0; i < scores.size(); i++)
//	{
//		scores[i]=i;
//	}
//	cout << endl;
//
//	cout << "Push 7" << endl;
//	scores.push_back(7);    //마지막에 7추가
//	dequeHightest(scores);
//	printdata_deque(scores);
//	cout << endl;
//
//
//
//
//	//VecInsert(scores, 2, 9);		//시작 주소 + sizeof(int) +2 자리에 9추가
//	dequeHightest(scores);
//	printdata_deque(scores);
//	cout << endl;
//
//
//
//	cout << "POP end" << endl;
//	scores.pop_back();		//마지막을 제거
//	dequeHightest(scores);
//	printdata_deque(scores);
//	cout << endl;
//
//	//end()는 마지막 원소가 끝나는 주소를 가르킨다.
//
//
//
//
//
//	printdata_deque(scores);
//}
//#############################################################################################################
void SetTest(void) //래드-블랙 이진트리
{ //set 과 multiset의 차이는 중복값을 저장하고 안하고의 차이이다.
	set<int> setData;
	setData.insert(1);
	setData.insert(2);
	setData.insert(3);
	//같은 값이 추가 되지 않는다.

	set<int>::iterator it;
	it = setData.find(2);

	PrintContainer(setData);
	if (it != setData.end())
		cout << "Find: " << *it << endl;
}

//집합은 원래 순서가 없어서 insert 사용
//순서가 없지는 않다 래드-블랙 이진트리를 이용한다.
//래드-블랙 이진트리를 이용하기 때문에 정렬되지 않은 값을 저장하면 성능이 떨어 진다.

//###################################################################################################################3
void MapTest(void)			//키값을 활용한 래드-블랙 이진트리
{
	map<string, string> dic;
	dic["boy"] = "소년";
	dic["school"] = "학교";
	dic["office"] = "직장";
	dic["house"] = "집";
	dic["moring"] = "아침";
	dic["evening"] = "저녁";
	dic["end"] = "끝";


	cout << "Size" << dic.size() << endl;
	//PrintContainer(dic);

	cout << dic["boy"] << endl;
	cout << dic["none"] << endl;

	map<int, int> mapArray;
	mapArray[0] = 1;
}
//c#에서는 딕셔너리 라고 한다.
//############################################################################################################################################
void StackTest(void) //리스트 ( 후입후출)
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
void QueTest(void) //리스트 ( 후입 선출)
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
void PQueTest(void)  //제일 큰 값부터 출력  //최대 힙트리 활용 
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


