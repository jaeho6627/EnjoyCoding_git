/******************************************
�����̸�	: DoubleLinkedList_ver1.3.cpp
�ڵ����	: ȯ�� ���� ���� ����ũ�� ����
�ۼ�����	: 19.08.14
��������	: 19.08.15
�� �� ��	: ����ȣ
�� �� ��	: http://jhjy5369.blog.me/NBlogWlwLayout.nhn?blogId=jhjy5369
�����ڵ�	:
	1. ����Ʈ ����
	2. ������
	3. ����Ʈ ���(������, ������)
	4. ���˻� (������, ������)
	5. ������
	6. ����Ʈ����
	7. �Լ� ����ó��
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
void printDouList_f(hnode* pHeader, node* const pEnd);//����Ʈ ���(��)
void printDouList_d(hnode* pHeader, node* const pEnd);//����Ʈ ���(��)
node* findDouList_f(node* const pBegin, node* const pEnd, int data);//���˻�(��)
node* findDouList_d(node* const pBegin, node* const pEnd, int data);//���˻�(��)
node* delDouNode(hnode* pHeader, node* pEnd, int data);//������
node* delDouList(hnode*& pHeader, node* const pEnd);//����Ʈ ����

int main(void) {
	hnode * pHeader = NULL;
	node * pEnd = NULL;
	node* pPrint = NULL;

	pEnd = createNode(pHeader, pEnd, 10);					//����Ʈ�� �������� �ʾ����� ��带 ������ ���

	pHeader = createList();
	if (pHeader == NULL) {
		return 0;
	}

	pEnd = createNode(pHeader, pEnd, 10);
	pEnd = createNode(pHeader, pEnd, 20);
	pEnd = createNode(pHeader, pEnd, 30);
	pEnd = createNode(pHeader, pEnd, 40);
	pEnd = createNode(pHeader, pEnd, 50);

	printDouList_f(pHeader, pEnd);
	printDouList_d(pHeader, pEnd);

	pPrint = findDouList_f(pHeader->pBegin, pEnd, 30);
	if (pPrint != NULL) {
		printf("print data: %d\n", pPrint->data);
	}//�˻��� ��� ���

	pPrint = findDouList_d(pEnd, pHeader->pBegin, 100);		//����Ʈ�� ���� 100�� �˻�
	if (pPrint != NULL) {
		printf("print data: %d\n", pPrint->data);
	}//�˻��� ��� ���

	pEnd = delDouNode(pHeader, pEnd, 50);		//����Ʈ�� ������ ��带 ������ ���
	printDouList_f(pHeader, pEnd);
	printDouList_d(pHeader, pEnd);

	pEnd = delDouNode(pHeader, pEnd, 10);		//����Ʈ�� ù��° ��带 ������ ���
	printDouList_f(pHeader, pEnd);
	printDouList_d(pHeader, pEnd);

	pEnd = delDouList(pHeader, pEnd);
	printDouList_f(pHeader, pEnd);				//����Ʈ ��� (��µǸ� �ȵ�)
	pEnd = delDouList(pHeader, pEnd);			//���� ����Ʈ�� ������ ���

	return 0;
}

//����Ʈ ����
hnode* createList(void) {
	hnode* pTemp = NULL;
	pTemp = new hnode;
	if (pTemp == NULL) {								//�����Ҵ翡 �������� ���
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

	if (pTemp == NULL) {								//�����Ҵ翡 �������� ���
		printf("��� ������ ������ �ֽ��ϴ�.");
		return NULL;
	}
	if(pHeader==NULL){									//����Ʈ�� ���µ� ��带 ������ ���
		printf("���� ����Ʈ�� �������� �ʾҽ��ϴ�.\n");
		return NULL;
	}
	else if (pEnd == NULL && pHeader->pBegin == NULL) {			//���� ����Ʈ�� �����Ͱ� ���� �� ó��
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
void printDouList_f(hnode* const pHeader, node* const pEnd) {
	if(pHeader==NULL){											//����Ʈ�� ���µ� ���
		printf("����Ʈ�� �����ϴ�.\n");
		return;
	}
	else if (pHeader->pBegin == NULL && pEnd == NULL) {			//����Ʈ�� �����Ͱ� ����
		printf("����Ʈ ��¿� ������ �ֽ��ϴ�.\n");
		return;
	}

	node* pPnode = pHeader->pBegin;
	printf("List data : ");
	while (pPnode != pEnd) {
		printf("%d ", pPnode->data);
		pPnode = pPnode->pNextNode;
	}
	printf("%d\n", pPnode->data);
}
//����Ʈ ��� (������)
void printDouList_d(hnode* const pHeader,node* const pEnd) {
	if (pHeader == NULL) {
		printf("����Ʈ�� �����ϴ�.\n");
		return;
	}
	else if (pHeader->pBegin == NULL && pEnd == NULL) {
		printf("����Ʈ ��¿� ������ �ֽ��ϴ�.\n");
		return;
	}

	node* pPnode = pEnd;
	printf("List data : ");
	while (pPnode != pHeader->pBegin) {
		printf("%d ", pPnode->data);
		pPnode = pPnode->pPreNode;
	}
	printf("%d\n", pPnode->data);
}
//���˻�(��)
node* findDouList_f(node* const pBegin, node* const pEnd, int data) {
	node* pNode = pBegin;
	if (pBegin == NULL) {
		printf("����� �����Ͱ� �����ϴ�.\n");
		return NULL;
	}
	else if (pEnd == NULL) {								//����Ʈ�� �������� �� �� ���� ��� 
		printf("����Ʈ�� �Ҿ��� �մϴ�.\n");
		return NULL;
	}

	while (pNode != pEnd) {
		if (pNode->data == data) {
			return pNode;
		}
		pNode = pNode->pNextNode;
	}
	if (pNode->data == data) {
		return pNode;
	}
	else {
		printf("ã�� ���� �����ϴ�.\n");
		return NULL;
	}
}
//���˻�(��)
node* findDouList_d(node* const pBegin, node* const pEnd, int data) {
	node* pNode = pBegin;
	if (pBegin == NULL) {
		printf("����� �����Ͱ� �����ϴ�.\n");
		return NULL;
	}
	else if (pEnd == NULL) {
		printf("����Ʈ�� �Ҿ��� �մϴ�.\n");
		return NULL;
	}

	while (pNode != pEnd) {
		if (pNode->data == data) {
			return pNode;
		}
		pNode = pNode->pPreNode;
	}
	if (pNode->data == data) {
		return pNode;
	}
	else {
		printf("ã�� ���� �����ϴ�.\n");
		return NULL;
	}
}
//��� ����
node* delDouNode(hnode* pHeader, node* pEnd, int data) {
	node* pNode = NULL;
	node* pDelNext = NULL;
	node* pDelPre = NULL;
	if (pHeader == NULL) {
		printf("����Ʈ�� �����ϴ�.\n");
		return NULL;
	}
	else if (pHeader->pBegin == NULL) {			//�����Ͱ� ���µ� ���Ÿ� �䱸
		printf("����� �����Ͱ� �����ϴ�.\n");
		return NULL;
	}
	pNode = findDouList_f(pHeader->pBegin, pEnd, data);
	if (pNode == NULL) {						//ã�� ���� ���� ���
		return pEnd;
	}
	pDelNext = pNode->pNextNode;
	pDelPre = pNode->pPreNode;

	pDelNext->pPreNode = pDelPre;
	pDelPre->pNextNode = pDelNext;

	if (pNode == pEnd) {
		pEnd = pEnd->pPreNode;
	}
	else if (pNode == pHeader->pBegin) {
		pHeader->pBegin = pNode->pNextNode;
	}

	delete pNode;
	pHeader->nodecount--;

	return pEnd;
}
//����Ʈ ����
node* delDouList(hnode*& pHeader, node* const pEnd) {
	if (pHeader == NULL) {
		printf("������ ����Ʈ�� �����ϴ�.\n");
		return NULL;
	}
	else if (pHeader->pBegin == NULL) {
		printf("������ �����Ͱ� �����ϴ�.\n");
		return NULL;
	}

	node* pNode = pHeader->pBegin;
	node* pNext = pNode->pNextNode;
	pEnd->pNextNode = NULL;		//�̸� ������ ����� ������ ���� ����
	while (pNode!=NULL) {
		delete pNode;
		pNode = pNext;
		if (pNext != NULL) {
			pNext = pNext->pNextNode;
		}
	}
	delete pHeader;
	pHeader = NULL;
	return NULL;
}