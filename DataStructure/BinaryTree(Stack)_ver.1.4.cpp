/*
�����̸�	: BinaryTree(Stack)_ver.1.4.cpp
�� �� ��	: ����ȣ (jhjy5369@naver.com)
�ڵ����	: ������ ����� ����Լ��� ������� �ʰ� Ʈ���� ��Ҹ� ��ȸ�ϴ� �Լ� ����
�� �� ��	: 19.8.28
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>

struct bNode {
	bNode * pRenode;
	int data;
	bNode * pLeft;
	bNode * pRight;
};

struct qNode {
	bNode* nodeData;
	qNode* pNext;
};

struct sNode {//������ ��� �ڷᱸ��
	bNode* nodeData;
	sNode* pNext;

};

bNode* addRoot(int data);
qNode* enqueue(qNode* pRear, bNode* data);
qNode* dequeue(qNode* pFront);
void addTree(qNode*& pFront, qNode*& pRear, int data);
void retraversals(bNode* parentNode);
void traversals(bNode* parentNode);

//���ð��� �Լ�
void push(sNode*& pFront, bNode* data);
bNode* pop(sNode*& pFront);

//������ Ȱ���� ��ȸ�ϴ� �Լ�
void stacktraver(bNode* parentNode);


int main(void) {
	bNode* pRoot = NULL;
	qNode* pFront = NULL;
	qNode* pRear = NULL;

	pRoot = addRoot(10);
	pRear = enqueue(pRear, pRoot);
	pFront = pRear;

	addTree(pFront, pRear, 20);
	addTree(pFront, pRear, 30);
	addTree(pFront, pRear, 40);
	addTree(pFront, pRear, 50);
	addTree(pFront, pRear, 60);
	addTree(pFront, pRear, 70);


	traversals(pRoot);
	retraversals(pRoot);
	stacktraver(pRoot);

	return 0;
}

//ť�� Ʈ�� �ּҰ�(������) ����
qNode* enqueue(qNode* pRear, bNode* data) {
	qNode* pTemp = NULL;
	pTemp = new qNode;
	if (!pTemp) return NULL;
	memset(pTemp, 0, sizeof(qNode));

	pTemp->nodeData = data;

	if (pRear) {
		pRear->pNext = pTemp;
	}

	return pTemp;
}

qNode* dequeue(qNode* pFront) {
	qNode* pDel = pFront;
	qNode* pNext = pDel->pNext;
	delete pDel;
	return pNext;
}

qNode* peek(qNode* pFront) {
	qNode* pNode = pFront;
	return pNode;
}

//Ʈ���� ��Ʈ ��带 ������ִ� �Լ�
bNode* addRoot(int data) {
	bNode* pTemp = NULL;
	pTemp = new bNode;
	memset(pTemp, 0, sizeof(bNode));
	pTemp->data = data;
	return pTemp;
}

void addTree(qNode*& pFront, qNode*& pRear, int data) {
	qNode* pNode = peek(pFront);

	bNode* pTemp = NULL;
	pTemp = new bNode;
	if (!pTemp) return;
	else {
		memset(pTemp, 0, sizeof(bNode));
		pTemp->data = data;
		pRear = enqueue(pRear, pTemp);
	}

	if (!(pNode->nodeData->pLeft)) {
		pNode->nodeData->pLeft = pTemp;
		pTemp->pRenode = pNode->nodeData;
	}
	else if (!(pNode->nodeData->pRight)) {
		pNode->nodeData->pRight = pTemp;
		pTemp->pRenode = pNode->nodeData;
		pFront = pFront->pNext;
		delete pNode;
	}
	return;
}
void retraversals(bNode * parentNode) {
	if (!parentNode) return;

	retraversals(parentNode->pLeft);

	retraversals(parentNode->pRight);

	printf("%d ", parentNode->data);
}

void traversals(bNode * parentNode) {
	bNode * pNode = parentNode;
	bNode * pPre = NULL;
	while (1) {
		
		if (pNode->pRight == pPre || pNode->pRight == NULL) {
			printf("%d ", pNode->data);
			if (pNode == parentNode) {
				printf("\n");
				break;
			}
			pPre = pNode;
			pNode = pNode->pRenode;
		}
		else if (pNode->pLeft == pPre || pNode->pLeft == NULL) {
			pNode = pNode->pRight;
		}
		else {
			
			pNode = pNode->pLeft;
		}
		
	}

}

//���� ���� �Լ�
void push(sNode*& pFront, bNode* data) {
	sNode* pTemp = NULL;
	if (data) {

		pTemp = new sNode;
		if (!pTemp) return;

		memset(pTemp, 0, sizeof(sNode));

		pTemp->nodeData = data;
		if (pFront) {
			pTemp->pNext = pFront;
		}
		pFront = pTemp;
	}
}

bNode* pop(sNode*& pFront) {
	sNode* pNode = NULL;
	if (!pFront) return NULL;

	pNode = pFront;
	if (pFront->pNext)
		pFront = pFront->pNext;
	else pFront = NULL;

	return pNode->nodeData;
}

void stacktraver(bNode* parentNode) {
	sNode* pFront = NULL;
	bNode* pNode = NULL;

	if (!parentNode) return;

	pNode = parentNode;
	push(pFront, pNode);

	while (pFront) {
		pNode = pop(pFront);// pFront->nodeData;
		printf("%d ", pNode->data);
		push(pFront, pNode->pRight);
		push(pFront, pNode->pLeft);
		
		delete pNode;
	}
	printf("\n");
}