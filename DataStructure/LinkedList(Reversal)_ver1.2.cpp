/**************************************************************************************
�����̸�	:	LinkedList_ver1.2(Reversal).cpp
�� �� ��	:	����ȣ(Jung - Jae ho, Hoje)
�� �� ��	:	https://jhjy5369.blog.me
git		:	https://github.com/jaeho6627
�ۼ���¥	:	19.08.15
�ڵ弳��	:	���� ���� ����Ʈ�� ���� ����� ����Ʈ�� ������ ����� ����
			�Ϻ� �ڵ�� ������ �ۼ��ߴ� LinkedList_ver1.1.cpp�� ��� ����Ʈ�� ������ �Լ��� ����
�������	:	����Ʈ������ ������ ������ �Լ� ( )
**************************************************************************************/
#include <stdio.h>
#include <stdlib.h> //�޸� �����Ҵ� ���
#include <crtdbg.h> //�޸� ���� Ž�� ���
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

	pBegin = ReverseLinkedList(pBegin);			//�����Լ� ����Ʈ�� ���� �� ȣ���ϸ� �ȵ� (����ó��)
	
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

	pBegin = ReverseLinkedList(pBegin);			//�����Լ�

	PrintLinkedList(pBegin);					//�����Լ� ��� ���

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
		//����Ʈ�� ���µ� ȣ���
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
			printf("�� �̻� ����Ҽ� �ִ� �޸𸮰� �����ϴ�!");
		}

		if (pStart == NULL)
			pStart = pNode;

		PrintLinkedList(pStart);
	}

	DeleteLinkedList(pStart); 
}

/*
���ο� ��� �����͸� ����� ����Ʈ�� ������� ���޹޾� �������� ������ �Լ��� ȣ���ߴ� �������� ���� ������ ���� �ּ� ���� �����Ѵ�.
*/
//����Ʈ ����
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