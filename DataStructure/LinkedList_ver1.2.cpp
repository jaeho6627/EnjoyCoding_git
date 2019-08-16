/*##################################
단일연결리스트
파일명: LinkedList_empty.cpp
작성자: 정재호(jhjy5369@naver.com)
마지막수정날짜: 2019.08.16
버전: 1.20
###################################*/

#include <stdio.h>
#include <stdlib.h> //메모리 동적할당 헤더
#include <crtdbg.h> //메모리 누수 탐지 헤더
//#include  "linkedlistClass.h"

struct SNode {
	int nData;
	SNode* pNext;
};

SNode* CreateNode(SNode* pNode, int data); 
SNode* FindNodeData(SNode* pStart, int data); 
void InsertNodeData(SNode* pStart, int data, int insert); 
SNode* DeleteNodeData(SNode* pStart, int del); 
void PrintLinkedList(SNode* pStart); 
void DeleteLinkedList(SNode*& pStart);
//void ReverseLinkedList(SNode* pStart); //

									  
void InputAdd();


int main()
{
	//_CrtSetBreakAlloc(71); //메모리 누수시 번호를 넣으면 할당하는 위치에 브레이크 포인트를 건다.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //메모리 누수 검사 

	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	//노드 추가 테스트
	pEnd = CreateNode(pEnd, 10);
	pBegin = pEnd; //마지막 노드를 알아야 검색이 가능하므로 저장해둔다.

	pEnd = CreateNode(pEnd, 20);
	pEnd = CreateNode(pEnd, 30);
	pEnd = CreateNode(pEnd, 40);
	pEnd = CreateNode(pEnd, 50);

	PrintLinkedList(pBegin);

	SNode* pFind = FindNodeData(pBegin, 40);
	if (pFind != NULL)
		printf("Find:%d\n", pFind->nData);

	InsertNodeData(pBegin, 30, 60);//노드 삽입

	PrintLinkedList(pBegin);

	pBegin = DeleteNodeData(pBegin, 60);//노드 삭제

	PrintLinkedList(pBegin);

	DeleteLinkedList(pBegin); //모든노드삭제 - 이 함수를 호출하지않을시 메모리가 누수됨.
	PrintLinkedList(pBegin); //모든 리스트를 할당 해제했지만 begin이 가리키는 메모리 주소는 그대로 라서 출력시 쓰레기 값을 출력함 And errer
}


SNode* CreateNode(SNode* pNode, int data)
{
	SNode* pTemp = NULL;
	pTemp = new SNode();
	pTemp->nData = data;
	if (pNode != NULL)
		pNode->pNext = pTemp;
	return pTemp;
}

SNode* FindNodeData(SNode* pStart, int data) //찾는 노드가 없는 경우
{
	/*while (pStart != NULL) { //ver1.0
		if (pStart->nData == data) {
			return pStart;
		}
		
		pStart = pStart->pNext;
	
	}*/

	while (pStart->nData != data) {	//ver1.2
		pStart = pStart->pNext;
		if (pStart == NULL) {
			printf("%d can not find.\n", data);
			return NULL;
		}
	}

	
	return pStart;
}

void InsertNodeData(SNode* pStart, int data, int insert) //추가할 데이터의 추가할 위치의 이전 노드 값을 찾는데 없는 경우
{
	SNode* pNode = pStart;
	SNode* pInsert = NULL;
	pInsert = new SNode;
	pInsert->nData = insert;
	pNode = FindNodeData(pStart, data);

	if (pNode == NULL) {
		printf("%d can not find", data);
		pNode = pStart;
		while (pNode->pNext != NULL) { //임의로 마지막 위치에 노드 추가
			pNode = pNode->pNext;
		}
	}

	pInsert->pNext = pNode->pNext;
	pNode->pNext = pInsert;
	return;
}

SNode* DeleteNodeData(SNode* pStart, int del) //지울 data가 없는데 제거를 명령하면
{
	SNode* pPre = NULL;
	SNode* pNode = pStart;

	if (pNode->nData == del) {
		pStart = pNode->pNext;
		delete pNode;
		return pStart;
	}
	else {
		while (pNode->nData != del) {
			pPre = pNode;
			pNode = pNode->pNext;
			if (pNode == NULL) { //루프를 돌아도 del과 동일한 data를 못찾고 pNode에 저장된 값이 NULL인 경우
				printf("can not fine %d to delete data", del);
				return pStart;
			}
		}
		pPre->pNext = pNode->pNext;
		delete pNode;
	}
	return pStart;
}

void PrintLinkedList(SNode* pStart) //리스트가 없는데 리스트를 출력한다면
{
	SNode* pNode = pStart;
	printf("data:");
	if (pNode == NULL) {
		//리스트가 없는데 호출됨
		printf("Nothing List here");
	}
	while (pNode)
	{
		printf("%d", pNode->nData);
		pNode = pNode->pNext;

		if (pNode != NULL)
			printf(",");
	}
	printf("\n");
}

void DeleteLinkedList(SNode*& pStart) //리스트가 없을 때 리스트를 지우면 
{
	SNode* pNode = pStart;
	SNode* pDel = NULL;
	if (pNode == NULL) {
		//리스트가 없는데 호출됨
		printf("Nothing List here\n");
	}
	while (pNode) {
		pDel = pNode;
		pNode = pNode->pNext;
		delete pDel;
	}
	pStart = NULL;
	printf("All list deleted.\nNow program exit.\n");
}

void InputAdd()
{
	SNode* pStart = NULL;
	SNode* pNode = NULL;
	int nData = 0;

	//동적할당을 하면 프로그램이 사용자에 의해서 사용되는 메모리가 결정된다.
	//쉽게말해서, 컴파일단계에서 100개를 만들고 쓴다면, 
	//사용하지않더라도 100개의 메모리를 사용할수밖에없다.
	//그리고, 100개 이상의 메모리도 사용할수없다.
	//그러나, 동적할당을 하면 사용자가 추가한 메모리만큼만 메모리가 사용되고 
	//메모리용량이 허용하는 한 추가가 된다.
	while (nData != -1)
	{
		scanf("%d", &nData);
		pNode = CreateNode(pNode, nData);

		if (pNode == NULL)
		{
			printf("더 이상 사용할수 있는 메모리가 없습니다!");
		}

		if (pStart == NULL)
			pStart = pNode;

		PrintLinkedList(pStart);
	}

	DeleteLinkedList(pStart); //모든노드삭제 - 이 함수를 호출하지않을시 메모리가 누수됨.
}