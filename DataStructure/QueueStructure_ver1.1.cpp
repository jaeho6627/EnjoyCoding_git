/*
�����̸�	:	QueueStructure_ver1.1.cpp
���ϼ���	:	ť �ڷᱸ�� ����
�� �� ��	:	����ȣ(Jung Jae-ho, Hoje)
�� �� ��	:	https://jhjy5369.blog.me
git		:	https://github.com/jaeho6627
�ۼ���¥	:	19.08.16
�ڵ����	:	ť �ڷᱸ���� �⺻ ���(enqueue, dequeue, peek)�� ť�� �߰����� �Լ� ����
			Queue Data Structure basic funstions(enqueue, dequeue, peek) and Add-in definition
�����Ϸ���
	1. enqueue
	2. dequeue
	3. peek
	5. find
	6. print
	7. delete
��������
	1. ��ũ ����� ã�� ������ ���� // �Լ� ��ȯ�� ���� �� �߸��� �������� �˻縦 �Ѵ��� ����� ����
	2. delete ���� �� ��� ���� // pNext�� NULL�϶� ���� �����ϴ� ��찡 �־���
								�ش� ���� ���� pRear�� ���Ÿ� ����ϴ� pDel�� ��ġ�� ���� ������ �Ҵ� �����ϰ� �������� Ż����
�̱������
	1. ����ó��
*/
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

struct sNode {
	int data;
	sNode * pNext;
};
/*
1. enqueue
	2. dequeue
	3. peek
	4. find
	5. print
	6. delete
*/
sNode* enqueue(sNode* pTop, int data);
sNode* q_peek(sNode* pFront);
sNode* q_find(sNode* pFront, sNode* pRear, int data);
void q_print(sNode* pFront, sNode* pRear);
sNode* dequeue(sNode* pFront);
sNode* q_delete(sNode*& pFront, sNode* pRear);

int main(void) {
	sNode * pFront = NULL;
	sNode * pRear = NULL;
	sNode * pPrint = NULL;
	
	pRear = enqueue(pRear, 10); //10��� �߰�
	pFront = pRear;
	pRear = enqueue(pRear, 20);
	pRear = enqueue(pRear, 30);
	pRear = enqueue(pRear, 40);
	pRear = enqueue(pRear, 50);
	pRear = enqueue(pRear, 60);
	q_print(pFront, pRear);


	pPrint = q_find(pFront, pRear, 30);
	if (pPrint != NULL) { //error point
		printf("Find data : %d\n", pPrint->data);
	}
	pPrint = q_peek(pFront);
	if (pPrint != NULL) { //error point
		printf("Peek data : %d\n", pPrint->data);
	}
	

	pFront = dequeue(pFront);
	q_print(pFront, pRear);

	
	pRear = q_delete(pFront, pRear); //error point
	q_print(pFront, pRear);
	
	return 0;
}
sNode* enqueue(sNode* pTop, int data) {
	sNode* pRear = NULL;
	sNode* pTemp = new sNode;
	

	if (pTemp == NULL) {
		return NULL;
	}
	
	pTemp->data = data;

	if(pTop != NULL) {
		pRear = pTop;
		pRear->pNext = pTemp;
	}
	return pTemp;
}
sNode* q_peek(sNode* pFront) {
	sNode* pTemp = NULL;
	if (pFront == NULL) {
		return NULL;
	}
	pTemp = pFront;
	return pTemp;
}
sNode* q_find(sNode* pFront, sNode* pRear, int data) {
	sNode* pNode = NULL;

	if (pFront == NULL || pRear == NULL) {
		return NULL;
	}
	pNode = pFront;

	while (pNode != NULL) {
		if (pNode->data == data) {
			return pNode;
		}
		else {
			pNode = pNode->pNext;
		}
	}
	return NULL;
}
void q_print(sNode* pFront, sNode* pRear) {
	sNode* pNode = NULL;
	if (pFront == NULL || pRear == NULL) {
		printf("No data\n");
		return;
	}
	pNode = pFront;
	while (pNode != NULL) {
		if (pNode == pRear) {
			printf("%d\n", pNode->data);
			return;
		}
		printf("%d ->", pNode->data);
		pNode = pNode->pNext;
	}
}
sNode* dequeue(sNode* pFront) {
	sNode* pDel = NULL;
	sNode* pNext = NULL;
	if (pFront == NULL) {
		return NULL;
	}
	pDel = pFront;
	pNext = pDel->pNext;
	printf("del : %d\n", pDel->data);
	delete pDel;
	return pNext;
}
sNode* q_delete(sNode*& pFront, sNode* pRear) {
	sNode* pDel = NULL;
	sNode* pNextDel = NULL;
	if (pFront == NULL || pRear == NULL) {
		return NULL;
	}

	pNextDel = pFront->pNext;
	pDel = pFront;
	while (pDel != NULL) {
		delete pDel;
		pDel = pNextDel;
		if (pDel == pRear) {
			delete pDel;
			return NULL;
		}
		pNextDel = pNextDel->pNext;
	}
	pFront = NULL;
	return NULL;
}