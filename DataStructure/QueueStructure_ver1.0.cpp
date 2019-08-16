/*
�����̸�	:	QueueStructure_ver1.0.cpp
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
	4. find
	5. print
	6. delete
�������
	1. ��ũ ����� ã�� ������ ����
	2. delete ���� �� ��� ����
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
void q_delete(sNode*& pFront, sNode*& pRear);

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
	//error 1
	pPrint = q_find(pFront, pRear, 30);
	if (pPrint == NULL) {
		printf("print data : %d\n", pPrint->data);
	}

	pPrint = q_peek(pFront);
	if (pPrint == NULL) {
		printf("print data : %d\n", pPrint->data);
	}
	//error 1
	pFront = dequeue(pFront);

	q_print(pFront, pRear);
	//error 2
	q_delete(pFront, pRear);

	q_print(pFront, pRear);
	//error 2
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
		pNode = pNode->pNext;
	}
	if (pNode == NULL) {
		return NULL;
	}
}
void q_print(sNode* pFront, sNode* pRear) {
	sNode* pNode = NULL;
	if (pFront == NULL || pRear == NULL) {
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
void q_delete(sNode*& pFront, sNode*& pRear) {
	sNode* pDel = NULL;
	sNode* pNext = NULL;
	if (pFront == NULL || pRear == NULL) {
		return;
	}
	pDel = pFront;
	while (pDel != NULL) {
		pNext = pDel->pNext;
		delete pDel;
		pDel = pNext;
	}
	pFront = NULL;
	pRear = NULL;
}