/*
���ϸ� : BinaryTree(Heap)_ver1.3_.cpp
���� : ��Ʈ���� ����
�ۼ���	: ����ȣ ( jhjy5369@naver.com)
�����ۼ��� : 19.8.22
���������� : 19.8.27

�������
1. ��ȭ����Ʈ�� ����
2. ť����
3. enqueue
4. dequeue
5. peek
6. Ʈ�� ��� ��ȸ
7. Ʈ�� �ݺ� ��ȸ
�̱������
	1. ������ �̿��� Ʈ�� ��ȸ
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

bNode* addRoot(int data);//��Ʈ ��忡 10�� ������ �Լ�
qNode* enqueue(qNode* pRear, bNode* data);//��Ʈ �����Ͱ� ����Ű�� ����� �ּҰ��� ť�� �����ϴ� �Լ�
qNode* dequeue(qNode* pFront);
void addTree(qNode*& pFront, qNode*& pRear, int data);//ť�� ����� �ּҰ��� �������� ���� ���� �����ϴ� �Լ�
void retraversals(bNode* parentNode);//Ʈ���� �Լ�
void traversals(bNode* parentNode);// no ���

int main(void) {
	bNode* pRoot=NULL;
	qNode* pFront=NULL;
	qNode* pRear=NULL;

	pRoot = addRoot(10);//Ʈ���� 10 ����
	pRear = enqueue(pRear, pRoot);//Ʈ�� root node �� �ּҰ��� ť�� ����
	pFront = pRear;

	addTree(pFront, pRear, 20);//ť�� ����� �ּҰ��� �������� 20 ����
	addTree(pFront, pRear, 30);//�� ����� �ּҰ��� �������� 30 ����
	addTree(pFront, pRear, 40);//ť�� ����� �ּҰ��� �������� 40 ����
	addTree(pFront, pRear, 50);//ť�� ����� �ּҰ��� �������� 50 ����
	addTree(pFront, pRear, 60);//ť�� ����� �ּҰ��� �������� 60 ����
	addTree(pFront, pRear, 70);//ť�� ����� �ּҰ��� �������� 70 ����


	traversals(pRoot);//�ݺ��� ��ȸ
	retraversals(pRoot);//��� �Լ� ��ȸ


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

