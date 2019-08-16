/*##################################
���Ͽ��Ḯ��Ʈ
���ϸ�: LinkedList_empty.cpp
�ۼ���: ����ȣ(jhjy5369@naver.com)
������������¥: 2019.08.16
����: 1.20
###################################*/

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
//void ReverseLinkedList(SNode* pStart); //

									  
void InputAdd();


int main()
{
	//_CrtSetBreakAlloc(71); //�޸� ������ ��ȣ�� ������ �Ҵ��ϴ� ��ġ�� �극��ũ ����Ʈ�� �Ǵ�.
	//_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF); //�޸� ���� �˻� 

	SNode* pBegin = NULL;
	SNode* pEnd = NULL;

	//��� �߰� �׽�Ʈ
	pEnd = CreateNode(pEnd, 10);
	pBegin = pEnd; //������ ��带 �˾ƾ� �˻��� �����ϹǷ� �����صд�.

	pEnd = CreateNode(pEnd, 20);
	pEnd = CreateNode(pEnd, 30);
	pEnd = CreateNode(pEnd, 40);
	pEnd = CreateNode(pEnd, 50);

	PrintLinkedList(pBegin);

	SNode* pFind = FindNodeData(pBegin, 40);
	if (pFind != NULL)
		printf("Find:%d\n", pFind->nData);

	InsertNodeData(pBegin, 30, 60);//��� ����

	PrintLinkedList(pBegin);

	pBegin = DeleteNodeData(pBegin, 60);//��� ����

	PrintLinkedList(pBegin);

	DeleteLinkedList(pBegin); //�������� - �� �Լ��� ȣ������������ �޸𸮰� ������.
	PrintLinkedList(pBegin); //��� ����Ʈ�� �Ҵ� ���������� begin�� ����Ű�� �޸� �ּҴ� �״�� �� ��½� ������ ���� ����� And errer
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

SNode* FindNodeData(SNode* pStart, int data) //ã�� ��尡 ���� ���
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

void InsertNodeData(SNode* pStart, int data, int insert) //�߰��� �������� �߰��� ��ġ�� ���� ��� ���� ã�µ� ���� ���
{
	SNode* pNode = pStart;
	SNode* pInsert = NULL;
	pInsert = new SNode;
	pInsert->nData = insert;
	pNode = FindNodeData(pStart, data);

	if (pNode == NULL) {
		printf("%d can not find", data);
		pNode = pStart;
		while (pNode->pNext != NULL) { //���Ƿ� ������ ��ġ�� ��� �߰�
			pNode = pNode->pNext;
		}
	}

	pInsert->pNext = pNode->pNext;
	pNode->pNext = pInsert;
	return;
}

SNode* DeleteNodeData(SNode* pStart, int del) //���� data�� ���µ� ���Ÿ� �����ϸ�
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
			if (pNode == NULL) { //������ ���Ƶ� del�� ������ data�� ��ã�� pNode�� ����� ���� NULL�� ���
				printf("can not fine %d to delete data", del);
				return pStart;
			}
		}
		pPre->pNext = pNode->pNext;
		delete pNode;
	}
	return pStart;
}

void PrintLinkedList(SNode* pStart) //����Ʈ�� ���µ� ����Ʈ�� ����Ѵٸ�
{
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

void DeleteLinkedList(SNode*& pStart) //����Ʈ�� ���� �� ����Ʈ�� ����� 
{
	SNode* pNode = pStart;
	SNode* pDel = NULL;
	if (pNode == NULL) {
		//����Ʈ�� ���µ� ȣ���
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

	//�����Ҵ��� �ϸ� ���α׷��� ����ڿ� ���ؼ� ���Ǵ� �޸𸮰� �����ȴ�.
	//���Ը��ؼ�, �����ϴܰ迡�� 100���� ����� ���ٸ�, 
	//��������ʴ��� 100���� �޸𸮸� ����Ҽ��ۿ�����.
	//�׸���, 100�� �̻��� �޸𸮵� ����Ҽ�����.
	//�׷���, �����Ҵ��� �ϸ� ����ڰ� �߰��� �޸𸮸�ŭ�� �޸𸮰� ���ǰ� 
	//�޸𸮿뷮�� ����ϴ� �� �߰��� �ȴ�.
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

	DeleteLinkedList(pStart); //�������� - �� �Լ��� ȣ������������ �޸𸮰� ������.
}