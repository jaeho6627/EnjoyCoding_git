/******************************************************************************************
�����̸�	:	StackStructer_ver1.0.cpp
���ϼ���	:	�����ڷᱸ�� ����.(Implement stack data structures.)
�� �� ��	:	����ȣ(Jung Jae_ho, Hoje)
�� �� ��	:	https://jhjy5369.blog.me
git		:	https://github.com/jaeho6627
�ۼ���¥	:	19.08.15
�ڵ��ǥ	:	�����ڷᱸ���� �⺻ ��� (push, pop, peek)�� ������ �߰����� �Լ��� ����.
			Stack Data Structure Basic Functions (Push, Pop, Peek) and Add-in Definition
�����Ϸ���
	1. push
	2. pop
	3. peek
	4. print
	5. delete
*******************************************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <crtdbg.h>

struct sNode
{
	int data;
	sNode * pNext;
};

void s_push(sNode** pTop, int data);				//data push
void s_pop(sNode** pTop);				//data pop
void s_peek(sNode* const pTop);				//data peek
void s_print(sNode* const pTop);		//stack print
void s_find(sNode* const pTop, const int data);			//data floor find
void s_delete(sNode** pTop);			//all stack delete

int main(void) {
	sNode * pTop = NULL;
	int nFloor = 0;
	int nData = 20;

	s_push(&pTop, 10);			//10 data push
	s_push(&pTop, 20);			//10 data push
	s_push(&pTop, 30);			//10 data push
	s_push(&pTop, 40);			//10 data push
	s_push(&pTop, 50);			//10 data push

	s_print(pTop);				//all stack print

	s_pop(&pTop);				//last input data pop
	s_pop(&pTop);

	s_print(pTop);

	s_peek(pTop);				//Top data print

	s_find(pTop, nData);
	if (nFloor > 0) {
		printf("%d data floor is floor %d\n", nData, nFloor);
	}

	s_delete(&pTop);			//all stack data deleted

	s_print(pTop);				//Nothing should be printed

	return 0;
}

void s_push(sNode** pTop, int data) {				//data push
	sNode  * pTemp = new sNode;
	if (pTemp == NULL) {
		return;
	}
	pTemp->data = data;
	pTemp->pNext = NULL;

	if (*pTop == NULL) {
		*pTop = pTemp;
	}
	else {
		pTemp->pNext = *pTop;
		*pTop = pTemp;
	}
	return;
}
void s_pop(sNode** pTop) {				//data pop
	sNode* pPop = NULL;
	if (*pTop == NULL) {
		return;
	}
	pPop = *pTop;
	*pTop = pPop->pNext;
	printf("%d data pop\n", pPop->data);
	delete pPop;
}
void s_peek(sNode* const pTop) {				//data peek
	if (pTop == NULL) {
		return;
	}
	printf("Top data [%d]\n", pTop->data);
}
	
void s_print(sNode* const pTop) {		//stack print
	sNode* pNode = NULL;
	int i = 1;
	if (pTop == NULL) {
		printf("Empty stack.\n");
		return;
	}
	pNode = pTop;
	while (pNode != NULL) {
		printf("%d. %d\n", i, pNode->data);
		pNode = pNode->pNext;
		i++;
	}
}
void s_find(sNode* const pTop, const int data) {			//data floor find
	sNode* pNode = NULL;
	int i = 1;
	if (pTop == NULL) {
		return;
	}
	pNode = pTop;
	while (pNode != NULL) {
		if (pNode->data == data) {
			printf("%d. %d\n", i, pNode->data);
			return;
		}
		pNode = pNode->pNext;
		i++;
	}
	return;
}
void s_delete(sNode** pTop) {			//all stack delete
	sNode* pNode = NULL;
	if (*pTop == NULL) {
		return;
	}

	while (*pTop != NULL) {
		pNode = *pTop;
		*pTop = pNode->pNext;
		delete pNode;
	}
}