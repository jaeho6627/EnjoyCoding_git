/*******************************************
�����̸� : LinkedList(Circul)_ver1.0.cpp
���۳�¥ : 19.08.14
������¥ : 00.00.00
�� �� �� : ����ȣ(hoje)
�� �� �� : jhjy5369@naver.com
�� �� �� : https://blog.naver.com/jhjy5369
���ϸ��� : ȯ�� ���� ����Ʈ�� �����ϰ� ����
�ڵ弳�� : 
	1. ȯ�� ���Ḯ��Ʈ�� �����ϱ� ���� �Ϲ� ���� ��� ��带 ����ü�� ���� �Ͽ���.
	2. ��� ���� �׻� ���۳���� ����Ű�� �Ϲ� ��� �ڷ����� ����Ʈ�� �����ϴ� ��尡 �ȴ�.
	3. ��� �����͸� �̿��� ����Ʈ�� �������� ǥ���� �д�.
	4. ������ ���ǻ� ����Ʈ�� �߰��ϴ� �����ʹ� �׻� ����Ʈ�� ������ ��� �ڿ� �߰��ȴ�. 
	5. �߰��� ���� ����Ʈ�� �߰��ϴ� �۾��� ��ġ�� ó�� ��带 ����Ű���� �ؾ��Ѵ�.
	6. ����Ʈ�� ��尡 �ϳ��ۿ� ���� ��� �ش� ����� ��ũ�� NULL�� �����Ѵ�.
	7. ������ �߻��� �� �ִ� ����� ��� Ȯ���� ����� �ڵ��ȣ�� ����� ���� �������� �Ǵ� ��� ������ ������ Ȯ���� �� �ֵ��� ���;���
������� : 
	1. ����ü �ڷ���
	2. �����ڵ尪�� ������ ������ �ڷ���
	3. ����� �Լ����� ����
	4. main �Լ� ����
	5. ����Ʈ �߰�, ��� �߰�, ����Ʈ ��ü ��� �Լ�
	6. ����Ʈ ���� ��� ���� ���
	7. ����Ʈ data �˻�
����������ǥ :
	1. ��ġ ������ �ش� data ����ϴ� �Լ�
	2. �˻� data ����
	3. ��ġ ������ data ����
	4. ����Ʈ ��ü ����
	5. ȯ�� ���Ḯ��Ʈ���� Ȯ���ϴ� �Լ�
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
���� �Ϲ� ���Ḯ��Ʈ(Linked List)�� �߰������� ������ ��尡 ù ��带 ����Ű���� �Ѵ�.
��带 �߰��Ҷ� ����Ʈ�� ù ��尡 ���� ��� �����忡 ���� �� �� ù ����� ��ũ�� NULL�� ��
�ι�° ��尡 �߰��� �� ���� ��尡 �߰��Ǹ� �������� �ڸ��� �߰��� ��� �׻� ù ��带 ��ũ�ϵ��� ����
(���*�� �̿��� ������ ��带 �׻� ����Ű���� ��) ( ������ ���� ��� ��尡 ����Ű�� ù ��带 ����Ű�� ��带 �ǹ�)
*/
typedef struct node {
	int data;
	struct node * pLink;
}NODE;

typedef struct hnode {
	int CurrNode;
	NODE DumNode;
}hNODE;

typedef enum error{NONE, LISTALLOTERROR, NODEALLOTERROR, PRINTERROR, LISTDELERROR, NODEDELERROR, NODEFINDERROR}ERRORCODE;


//��� �߰�
NODE * CreateNode(hNODE * header, NODE * pEnd, int data);
//��� �˻�
NODE * FindNode(hNODE * Header, NODE * pEnd, int data);
//��� ����
ERRORCODE DelNode(hNODE * Header, int data);
//����Ʈ ����
hNODE * CreateCirLinkL(void);
//����Ʈ ����
ERRORCODE DeleteCirLinkL(hNODE * Header);
//����Ʈ ���
void PrintCirLinkL(hNODE * Header, NODE * pEnd, int count);
//��� ���� ���
void cPrintCirLinkL(hNODE * header);

int main(void) {
	
	//����Ʈ�� ����
	hNODE* Header = CreateCirLinkL();
	//����Ʈ�� ������ ���
	NODE* pEndNODE = Header->DumNode.pLink;
	NODE* pFindNODE = NULL;
	
	pEndNODE = CreateNode(Header, pEndNODE, 10);//10����߰�
	pEndNODE = CreateNode(Header, pEndNODE, 20);//20����߰�
	pEndNODE = CreateNode(Header, pEndNODE, 30);//30����߰�
	pEndNODE = CreateNode(Header, pEndNODE, 40);//40����߰�
	
	PrintCirLinkL(Header, pEndNODE, 1);//����Ʈ ���
	cPrintCirLinkL(Header);
	pFindNODE=FindNode(Header, pEndNODE, 20);//20��� �˻�
	if (pFindNODE) {
		printf("Find data : %d\n", pFindNODE->data);
	} //�˻���� ���
	
	
	//30��� ����
	//����Ʈ ���
	//����Ʈ ����
	//����Ʈ ���

	return 0;
}
//��� �߰�
NODE * CreateNode(hNODE * header, NODE * pEnd, int data) {
	NODE * pStart = header->DumNode.pLink;
	NODE * pTemp = new NODE;
	memset(pTemp, 0, sizeof(pTemp));
	pTemp->data = data;
	
	if (header == NULL) {
		printf("[Error %d] There's no list", ERRORCODE::LISTALLOTERROR);
		return NULL;
	}
	else if (pTemp == NULL) {
		printf("[Error %d] Failed to add data", ERRORCODE::NODEALLOTERROR);
		return NULL;
	}

	if (pEnd == NULL) {
		header->DumNode.pLink = pTemp;
	}
	else {
		pEnd->pLink = pTemp;
		pTemp->pLink = pStart;
	}
	header->CurrNode++;

	return pTemp;
}
////��� �˻�
NODE * FindNode(hNODE * Header, NODE * pEnde, int data) {
	NODE * Start = Header->DumNode.pLink;

	if (Header == NULL) {
		printf("[Error %d] There's no list", ERRORCODE::LISTALLOTERROR);
		return NULL;
	}
	else if (Header->DumNode.pLink == NULL) {
		printf("[Error %d] There's no data", ERRORCODE::NODEALLOTERROR);
		return NULL;
	}

	while (Start != pEnde) {
		if (Start->data == data) {
			return Start;
		}
		Start = Start->pLink;
	}
	return NULL;
}
////��� ����
//ERRORCODE DelNode(hNODE * Header, int data) {
//}
//����Ʈ ����
hNODE * CreateCirLinkL(void) {
	hNODE * pTemp = NULL;
	pTemp = new hNODE;
	if (pTemp == NULL) {
		printf("[Error %d] Failed to add list", ERRORCODE::LISTALLOTERROR);
		return pTemp;
	}
	memset(pTemp, 0, sizeof(hNODE));
	return pTemp;
}
////����Ʈ ����
//ERRORCODE DeleteCirLinkL(hNODE * Header) {
//
//}
//����Ʈ ���
void PrintCirLinkL(hNODE * Header, NODE * pEnd, int count) {
	
	NODE * pStart = Header->DumNode.pLink;
	int PrintCount = 0;
	if (Header == NULL) {
		printf("[Error %d] There's no list", ERRORCODE::LISTALLOTERROR);
		return;
	}
	else if (Header->DumNode.pLink == NULL) {
		printf("[Error %d] There's no data", ERRORCODE::NODEALLOTERROR);
		return;
	}
	else if (pStart->pLink == NULL) {
		printf("List data \n%d", pStart->data);
	}
	else {
		printf("List data \n");
		while (PrintCount < count) {
			printf("%d ", pStart->data);
			if (pStart == pEnd) {
				PrintCount++;
				printf("\n");
			}
			pStart = pStart->pLink;
		}
	}
}
//��� ���� ���
void cPrintCirLinkL(hNODE * header) {
	if (header == NULL) {
		printf("[Error %d] There's no list", ERRORCODE::LISTALLOTERROR);
		return;
	}
	else {
		printf("Data node : %d\n", header->CurrNode);
	}
}