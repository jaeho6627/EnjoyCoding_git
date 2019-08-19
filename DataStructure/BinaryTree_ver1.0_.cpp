/*
�����̸�	:	BinaryTree_ver1.0_.cpp
���ϼ���	:	���� Ʈ�� ����
�ۼ���		:	����ȣ(jhjy5369@naver.com)
�ۼ���		:	19.08.19
������������:	19.08.19
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//node
struct Bnode {
	int data;
	Bnode* pLeft;
	Bnode* pRight;
};

Bnode * createNode(int data);// ��� ����
Bnode * leftNode(Bnode * pLeft);// ���� �ڽ� ����
Bnode * rightNode(Bnode * pRight);// ������ �ڽ� ����
void traversals(Bnode * parentNode);// ���� �迭 ��ȸ
void printData(Bnode * pNode);

int main(void) {
	Bnode * pRoot = createNode(10);		//�� ���� ���, ��Ʈ ���
	Bnode * pLeft = createNode(20);		//�ڽ� ���, ����
	Bnode * pRight = createNode(30);		//�ڽ� ���, ������
	Bnode * pLd = createNode(40);		//�ڽ� ���
	Bnode * pRd = createNode(50);		//�ڽ� ���

	pRoot->pLeft = leftNode(pLeft);
	pRoot->pRight = rightNode(pRight);

	pLeft->pLeft = leftNode(pLd);
	pLeft->pRight = rightNode(pRd);

	traversals(pRoot);

	return 0;
}
Bnode * createNode(int data) {
	Bnode * pTemp = (Bnode*)malloc(sizeof(Bnode));
	memset(pTemp, 0, sizeof(Bnode));
	pTemp->data = data;
	return pTemp;
}// ��� ����
Bnode * leftNode(Bnode * pLeft) {
	if (!pLeft) {
		return NULL;
	}
	return pLeft;
}// ���� �ڽ� ����
Bnode * rightNode(Bnode * pRight) {
	if (!pRight) {
		return NULL;
	}
	return pRight;
}// ������ �ڽ� ����
void traversals(Bnode * parentNode) {
	if(!parentNode) return;

	traversals(parentNode->pLeft);
	
	traversals(parentNode->pRight);

	printData(parentNode);
}// ���� �迭 ��ȸ
void printData(Bnode* pNode) {
	printf("%d ", pNode->data);
}