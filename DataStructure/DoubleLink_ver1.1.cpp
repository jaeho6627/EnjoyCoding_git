/******************************************
�����̸�	: DoubleLinkedList_ver1.0.cpp
�ڵ����	: ȯ�� ���� ���� ����ũ�� ����
�ۼ�����	: 19.08.14
��������	: 00.00.00
�� �� ��	: ����ȣ
�� �� ��	: http://jhjy5369.blog.me/NBlogWlwLayout.nhn?blogId=jhjy5369
�����ڵ�	: 
�̱����ڵ�:
	2. ���˻� (������, ������)
	3. ������
	4. ����Ʈ����
�����ڵ�	:
	1. ����Ʈ ����
	2. ������
	3. ����Ʈ ���(������, ������)

******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
���߿������ ��ũ�κ��� �������� ���ĳ�� �Ѵ� ����Ų��.
��忡 ��ũ �κ��� �� �� �ִ� ����̴�.
��� ������ ���� ��带 ����Ű�� ��ũ�� ���� ����� �ּҰ��� ����Ű�� �ϰ� ���� ��带 ����Ű�� �ϴ� ��ũ�� ���� ����� �ּҰ��� �����ϸ� �ȴ�.

*/

struct node {
	int data;
	struct node * pPreNode;
	struct node * pNextNode;
};

struct hnode {
	int nodecount;
	node * pBegin;
};

hnode* createList(void); //����Ʈ ����
node* createNode(hnode* pHeader, node* pEnd, int data);//������
void printDouList_f(node* const pBegin, node* const pEnd);//����Ʈ ���(��)
void printDouList_d(node* const pBegin, node* const pEnd);//����Ʈ ���(��)
node* findDouList_f(node* const pBegin, node* const pEnd, int data);//���˻�(��)
node* findDouList_d(node* const pBegin, node* const pEnd, int data);//���˻�(��)
//������
//����Ʈ ����

int main(void) {
	hnode * const pHeader = createList();
	node * pEnd = NULL;
	node* pPrint = NULL;
	
	if (pHeader == NULL) {
		return 0;
	}
	pEnd = createNode(pHeader, pEnd, 10);
	pEnd = createNode(pHeader, pEnd, 20);
	pEnd = createNode(pHeader, pEnd, 30);
	pEnd = createNode(pHeader, pEnd, 40);
	pEnd = createNode(pHeader, pEnd, 50);

	printDouList_f(pHeader->pBegin, pEnd);
	printDouList_d(pEnd, pHeader->pBegin);

	//30��� �˻�(������)
	//�˻��� ��� ���

	//20��� �˻�(������)
	//�˻��� ��� ���
	
	//40��� ����
	//����Ʈ ���

	//����Ʈ ����
	//����Ʈ ��� (��µǸ� �ȵ�)
	return 0;
}

//����Ʈ ����
hnode* createList(void) {
	hnode* pTemp = NULL;
	pTemp = new hnode;
	if (pTemp == NULL) {
		printf("����Ʈ �Ҵ��� ���������� �ʽ��ϴ�.\n");
		return pTemp;
	}
	memset(pTemp, 0, sizeof(hnode));
	return pTemp;
}
//������
node* createNode(hnode* const pHeader, node* pEnd, int data) {
	node* pTemp = new node;
	pTemp->data = data;
	
	if (pTemp == NULL) {
		printf("��� ������ ������ �ֽ��ϴ�.");
		return NULL;
	}

	if (pEnd == NULL&&pHeader->pBegin==NULL) {
		pHeader->pBegin = pTemp;
	}
	else {
		node* const pBegin = pHeader->pBegin;

		pEnd->pNextNode = pTemp;
		pTemp->pPreNode = pEnd;

		pBegin->pPreNode = pTemp;
		pTemp->pNextNode = pBegin;

	}
	pHeader->nodecount++;
	return pTemp;
}
//����Ʈ ��� (������)
void printDouList_f(node* const pBegin, node* const pEnd) {
	if (pBegin == NULL || pEnd == NULL) {
		printf("����Ʈ ��¿� ������ �ֽ��ϴ�.\n");
		return;
	}

	node* pPnode = pBegin;
	printf("List data : ");
	while (pPnode != pEnd) {
		printf("%d ", pPnode->data);
		pPnode = pPnode->pNextNode;
	}
	printf("%d\n", pPnode->data);
}
//����Ʈ ��� (������)
void printDouList_d(node* const pBegin, node* const pEnd) {
	if (pBegin == NULL || pEnd == NULL) {
		printf("����Ʈ ��¿� ������ �ֽ��ϴ�.\n");
		return;
	}

	node* pPnode = pBegin;
	printf("List data : ");
	while (pPnode != pEnd) {
		printf("%d ", pPnode->data);
		pPnode = pPnode->pPreNode;
	}
	printf("%d\n", pPnode->data);
}
//���˻�(��)
node* findDouList_f(node* const pBegin, node* const pEnd, int data) {
	
}
//���˻�(��)
node* findDouList_d(node* const pBegin, node* const pEnd, int data) {

}