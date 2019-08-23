/*
���ϸ� : BinaryTree(Heap)_ver1.1_.cpp
���� : ��Ʈ���� ����
�ۼ���	: ����ȣ ( jhjy5369@naver.com)
�����ۼ��� : 19.8.22
���������� : 19.8.23

��Ʈ����
�ٸ� ���� ��ȭ����Ʈ���� ���� ���� ���ߺ��� ���� �������� ������� ���� �ڸ��� ä��� �ִ� Ʈ���� �ǹ���

ť �ڷᱸ���� Ȱ���� ��ȭ ����Ʈ���� �ϼ���
Ʈ���� data�� �߰��Ҷ����� ť�� �߰��� ����� ���� ������ �ɹ� ������ ������ �ּ� ���� �����Ѵ�.
Ʈ���� �ڷḦ �߰��Ҷ� ���� ť���� data�� peek�ؼ� Ʈ���� �ڷḦ �߰��� �� ����� ���� ť�� ��ť�Ѵ�.
�������
1. ��ȭ����Ʈ�� ����
2. ť����
3. enqueue
4. dequeue
5. peek
6. Ʈ�� ��� ��ȸ
7. �޸� �Ҵ�����(��ü)
�̱������
	1. ����Լ��� ������� �ʰ� Ʈ�� ������ ��ȸ
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <crtdbg.h>
struct bNode {
	int data;
	bNode * pLeft;
	bNode * pRight;
};

struct qNode {
	bNode ** dp_Data;
	qNode * pNext;
};
//Ʈ�� �Ҵ翡 ����� ť�� ��� �ڷ���
struct nNode {
	bNode * pData;
	nNode* pNext;
};

qNode* enqueue(qNode * pRear, bNode ** Data); //ť enquequ ����
bNode** peek(qNode * pFront);//ť peek����
qNode* dequeue(qNode* pFront);	//����� ���� ť ������ ��ť
qNode* treeEnqueue(bNode** pNode, qNode* pRear);	//Ʈ�� �ɹ� ������ ������ �ּҰ��� ť�� ����
void createTree(bNode** pNode, int data);	//Ʈ����带 ������
void creatNode(qNode** pFront, qNode** pRear, int data);	//Ʈ���� ��������Ǵ� �Ϸ��� �۾��� ����
void traversals(bNode * parentNode);	//������ Ʈ���� ��ȸ

void delmalloc(bNode*& pRoot, qNode*& pFront, qNode*& qRear);
nNode* Newenqueue(nNode* pRear, bNode* pdata);//���ο� ť�� ���� �Լ�
void delOld(qNode*& pFront, qNode*& qRear);//������ ť�� �Ҵ����� �� �Լ�
void deltree(nNode*& pFront, nNode*& pRear, bNode*& pRoot);//Ʈ���� ��带 �Ҵ������ϴ� �Լ�
bNode* Newpeek(nNode* pFront);//���� ������ ť���� ���� �տ� ��带 ��ũ
void Newdequeue(nNode*& pFront);//���� ������ ť���� ���� �տ� ��带 ��ť

//�Ҵ� ���� �Լ�
//�� ť �ڷᱸ�� �Ҵ�����
//�� Ʈ�� �Ҵ�����
//	�� ť �ڷᱸ�� Ȱ�� �Ҵ����� 


int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// �޸� ���� �˻�

	bNode * pRoot = NULL;
	qNode * pFront = NULL;
	qNode * pRear = NULL;

	pRear=enqueue(pRear, &pRoot); 
	pFront = pRear;

	creatNode(&pFront, &pRear, 10);
	creatNode(&pFront, &pRear, 20);
	creatNode(&pFront, &pRear, 30);
	creatNode(&pFront, &pRear, 40);
	creatNode(&pFront, &pRear, 50);
	creatNode(&pFront, &pRear, 60);
	creatNode(&pFront, &pRear, 70);

	traversals(pRoot);

	delmalloc(pRoot, pFront, pRear);//����� �ڷᱸ�� �Ҵ�����

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

void delmalloc(bNode*& pRoot, qNode*& pFront, qNode*& pRear) {
	nNode* nFront = NULL;
	nNode* nRear = NULL;
	delOld(pFront, pRear);//���������� ť ��ü �ʱ�ȭ ( �Ҵ����� )
	nRear = Newenqueue(nRear, pRoot);//���ο� ť ��� ����( Ʈ���� ��Ʈ ��� )
	nFront = nRear;
	deltree(nFront, nRear, pRoot);//Ʈ���� ���ʺ��� ������ ���� �������� �Ҵ� ���� + ���ÿ� ť�Ҵ�����
}
nNode* Newenqueue(nNode* pRear, bNode* pdata)//���ο� ť�� ���� �Լ�
{
	nNode* pTemp = NULL;
	pTemp = new nNode;
	if (!pTemp) return NULL;
	memset(pTemp, 0, sizeof(nNode));

	pTemp->pData = pdata;
	if (pRear) {
		pRear->pNext = pTemp;
	}

	return pTemp;
}
//���ο� queue���� �ڷḦ ��ũ
bNode* Newpeek(nNode* pFront) {
	nNode* pNode = NULL;
	if (!pFront) return NULL;

	pNode = pFront;
	if (pNode->pData) return pNode->pData;
	else return NULL;
}
//���ο� ť�� ��ť
void Newdequeue(nNode*& pFront) {
	nNode* pDel = NULL;
	if (!pFront) return;

	pDel = pFront;
	if (pFront->pNext) {
		pFront = pFront->pNext;
	}
	else {
		pFront = NULL;
	}
	delete pDel;
}
void delOld(qNode*& pFront, qNode*& pRear)//������ ť�� �Ҵ����� �� �Լ�
{
	qNode* pNode = NULL;
	qNode* pDel = NULL;
	if (!pFront) return;
	if (!pRear) return;
	pNode = pFront;
	if (!pNode) return;

	while (pNode) {
		pDel = pNode;
		if (pNode != pRear) {
			pNode = pNode->pNext;
		}
		else  pNode = NULL; 
		delete pDel;
	}
	pFront = NULL;
	pRear = NULL;

}
void deltree(nNode*& pFront, nNode*& pRear, bNode*& pRoot)//Ʈ���� ��带 �Ҵ������ϴ� �Լ�
{
	bNode* pDel = NULL;
	if (!pFront) return;
	if (!pRear) return;
	if (!pRoot) return;
	while (pFront) {
		pDel = Newpeek(pFront);
		if (pDel->pLeft) {
			pRear = Newenqueue(pRear, pDel->pLeft);
		}

		if (pDel->pRight) {
			pRear = Newenqueue(pRear, pDel->pRight);
		}

		delete pDel;
		Newdequeue(pFront);
	}
	pRear = NULL;
}
