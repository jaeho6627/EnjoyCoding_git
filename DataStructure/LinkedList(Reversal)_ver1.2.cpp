/**************************************************************************************
파일이름	:	LinkedList_ver1.2(Reversal).cpp
작 성 자	:	정재호(Jung - Jae ho, Hoje)
블 로 그	:	https://jhjy5369.blog.me
git		:	https://github.com/jaeho6627
작성날짜	:	19.08.15
코드설명	:	단일 연결 리스트를 응용 저장된 리스트를 뒤집는 기능을 구현
			일부 코드는 이전에 작성했던 LinkedList_ver1.1.cpp를 사용 리스트를 뒤집는 함수만 구현
구현기능	:	리스트내용의 순서를 뒤집는 함수 ( )
**************************************************************************************/
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
SNode * ReverseLinkedList(SNode* pStart);

									  
void InputAdd();


int main()
{
	//_CrtSetBreakAlloc(71); 
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); 

	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	pBegin = ReverseLinkedList(pBegin);			//반전함수 리스트가 없을 때 호출하면 안됨 (예외처리)
	
	pEnd = CreateNode(pEnd, 10);
	pBegin = pEnd; 

	pEnd = CreateNode(pEnd, 20);
	pEnd = CreateNode(pEnd, 30);
	pEnd = CreateNode(pEnd, 40);
	pEnd = CreateNode(pEnd, 50);

	PrintLinkedList(pBegin);

	SNode* pFind = FindNodeData(pBegin, 40);
	if (pFind != NULL)
		printf("Find:%d\n", pFind->nData);

	InsertNodeData(pBegin, 30, 60);

	PrintLinkedList(pBegin);

	pBegin = DeleteNodeData(pBegin, 60);

	PrintLinkedList(pBegin);

	pBegin = ReverseLinkedList(pBegin);			//반전함수

	PrintLinkedList(pBegin);					//반전함수 결과 출력

	DeleteLinkedList(pBegin);

	return 0;
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

SNode* FindNodeData(SNode* pStart, int data)
{
	while (pStart != NULL) {
		if (pStart->nData == data) {
			return pStart;
		}
		else {
			pStart = pStart->pNext;
		}
	}
	if (pStart == NULL) {
		printf("%d can not find.\n", data);
	}
	return pStart;
}

void InsertNodeData(SNode* pStart, int data, int insert) 
{
	SNode* pNode = pStart;
	SNode* pInsert = NULL;
	pInsert = new SNode;
	pInsert->nData = insert;
	pNode = FindNodeData(pStart, data);

	if (pNode == NULL) {
		printf("%d can not find", data);
		pNode = pStart;
		while (pNode->pNext != NULL) { 
			pNode = pNode->pNext;
		}
	}

	pInsert->pNext = pNode->pNext;
	pNode->pNext = pInsert;
	return;
}

SNode* DeleteNodeData(SNode* pStart, int del) 
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
			if (pNode == NULL) { 
				printf("can not fine %d to delete data", del);
				return pStart;
			}
		}
		pPre->pNext = pNode->pNext;
		delete pNode;
	}
	return pStart;
}

void PrintLinkedList(SNode* pStart) {

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

void DeleteLinkedList(SNode*& pStart)
{
	SNode* pNode = pStart;
	SNode* pDel = NULL;
	if (pNode == NULL) {

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

	DeleteLinkedList(pStart); 
}

/*
새로운 노드 포인터를 만들어 리스트를 순서대로 전달받아 역순으로 저장해 함수를 호출했던 지점으로 새로 정해진 시작 주소 값을 전달한다.
*/
//리스트 반전
SNode * ReverseLinkedList(SNode* pStart) {
	SNode * pNode = NULL;
	SNode * pPreNode = NULL;
	SNode * pTemp = NULL;

	if (pStart == NULL) {
		printf("Nothing List here\n");
		return NULL;
	}
	
	pNode = pStart;
	
	while (pNode != NULL) {
		if (pTemp == NULL) {
			
			pTemp = pNode;
			pNode = pNode->pNext;
			pTemp->pNext = NULL;

		}
		pPreNode = pNode;
		pNode = pNode->pNext;
		pPreNode->pNext = pTemp;
		pTemp = pPreNode;
	}
	return pTemp;
}