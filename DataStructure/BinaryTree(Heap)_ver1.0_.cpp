/*
���ϸ� : BinaryTree(HIP)_ver1.0_.cpp
���� : ��Ʈ���� ����
�ۼ���	: ����ȣ ( jhjy5369@naver.com)
�����ۼ��� : 19.8.22
���������� : 19.8.23

��Ʈ����
�ٸ� ���� ��ȭ����Ʈ���� ���� ���� ���ߺ��� ���� �������� ������� ���� �ڸ��� ä��� �ִ� Ʈ���� �ǹ���

ť �ڷᱸ���� Ȱ���� ��ȭ ����Ʈ���� �ϼ���
Ʈ���� data�� �߰��Ҷ����� ť�� �߰��� ����� ���� ������ �ɹ� ������ ������ �ּ� ���� �����Ѵ�.
Ʈ���� �ڷḦ �߰��Ҷ� ���� ť���� data�� peek�ؼ� Ʈ���� �ڷḦ �߰��� �� ����� ���� ť�� ��ť�Ѵ�.

�̱������
	1. ����� ���� �޸� �Ҵ�����
		�� ť�� Ʈ���� ������ �Ҵ�����
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
struct bNode {
	int data;
	bNode * pLeft;
	bNode * pRight;
};

struct qNode {
	bNode ** dp_Data;
	qNode * pNext;
};

qNode* enqueue(qNode * pRear, bNode ** Data); //ť enquequ ����
bNode** peek(qNode * pFront);//ť peek����
qNode* dequeue(qNode* pFront);	//����� ���� ť ������ ��ť
qNode* treeEnqueue(bNode** pNode, qNode* pRear);	//Ʈ�� �ɹ� ������ ������ �ּҰ��� ť�� ����
void createTree(bNode** pNode, int data);	//Ʈ����带 ������
void creatNode(qNode** pFront, qNode** pRear, int data);	//Ʈ���� ��������Ǵ� �Ϸ��� �۾��� ����
void traversals(bNode * parentNode);	//������ Ʈ���� ��ȸ



int main(void) {

	bNode * pRoot = NULL;
	qNode * pFront = NULL;
	qNode * pRear = NULL;

	pRear=enqueue(pRear, &pRoot); //���� ť�� ��Ʈ��带 ����Ű�� ������ ������ �ּ� �� ����
	pFront = pRear;

	creatNode(&pFront, &pRear, 10);//10�߰�
	creatNode(&pFront, &pRear, 20);//20�߰�
	creatNode(&pFront, &pRear, 30);//30�߰�
	creatNode(&pFront, &pRear, 40);//40�߰�
	creatNode(&pFront, &pRear, 50);//50�߰�
	creatNode(&pFront, &pRear, 60);//60�߰�
	creatNode(&pFront, &pRear, 70);//70�߰�

	traversals(pRoot);//Ʈ�� ��ȸ �Լ�

	//����� �ڷᱸ�� �Ҵ�����

	return 0;
}

qNode* enqueue(qNode * pRear, bNode ** Data) {
	qNode * pTemp = NULL;
	pTemp = new qNode;
	
	if (!pTemp) return NULL;
	memset(pTemp, 0, sizeof(qNode));
	pTemp->dp_Data = Data;

	if (pRear) {
		pRear->pNext = pTemp;
	}
	return pTemp;
}
bNode** peek(qNode * pFront) {
	bNode** pPeek = (pFront->dp_Data);
	return pPeek;
}
void createTree(bNode** pNode, int data) {
	(*pNode) = new bNode;
	if (*pNode) {
		memset(*pNode, 0, sizeof(bNode));
		(*pNode)->data = data;
	}
	return;
}
qNode* treeEnqueue(bNode** pNode, qNode* pRear) {
	pRear = enqueue(pRear, &((*pNode)->pLeft));
	pRear = enqueue(pRear, &((*pNode)->pRight));
	return pRear;
}
qNode* dequeue(qNode* pFront) {
	qNode * pNode = NULL;
	if (!(pFront->pNext)) {
		delete pFront;
		return NULL;
	}
	pNode = pFront->pNext;
	delete pFront;
	return pNode;
}

void creatNode(qNode** pFront, qNode** pRear, int data) {
	bNode** dpTree = peek(*pFront);
	createTree(dpTree, data);
	*pRear = treeEnqueue(dpTree, *pRear);
	*pFront = dequeue(*pFront);
}
void traversals(bNode * parentNode) {
	if (!parentNode) return;

	printf("%d ", parentNode->data);

	traversals(parentNode->pLeft);

	traversals(parentNode->pRight);

	
}