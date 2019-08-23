/*
파일명 : BinaryTree(Heap)_ver1.1_.cpp
목적 : 힙트리를 구현
작성자	: 정재호 ( jhjy5369@naver.com)
파일작성일 : 19.8.22
마지막수정 : 19.8.23

힙트리란
다른 말로 포화이진트리를 말함 낮은 레발부터 높은 레벨까지 빈공간이 없이 자리를 채우고 있는 트리를 의미함

큐 자료구조를 활용해 포화 이진트리를 완성함
트리에 data를 추가할때마다 큐에 추가된 노드의 왼쪽 오른쪽 맴버 포인터 변수의 주소 값을 저장한다.
트리에 자료를 추가할때 마다 큐에서 data를 peek해서 트리에 자료를 추가한 후 사용이 끝난 큐는 디큐한다.
구현기능
1. 포화이진트리 생성
2. 큐생성
3. enqueue
4. dequeue
5. peek
6. 트리 재귀 순회
7. 메모리 할당해제(전체)
미구현기능
	1. 재귀함수를 사용하지 않고 트리 데이터 순회
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
//트리 할당에 사용할 큐의 노드 자료형
struct nNode {
	bNode * pData;
	nNode* pNext;
};

qNode* enqueue(qNode * pRear, bNode ** Data); //큐 enquequ 연산
bNode** peek(qNode * pFront);//큐 peek연산
qNode* dequeue(qNode* pFront);	//사용이 끝난 큐 데이터 디큐
qNode* treeEnqueue(bNode** pNode, qNode* pRear);	//트리 맴버 포인터 변수의 주소값을 큐에 저장
void createTree(bNode** pNode, int data);	//트리노드를 생성하
void creatNode(qNode** pFront, qNode** pRear, int data);	//트리에 값이저장되는 일련의 작업을 통제
void traversals(bNode * parentNode);	//생성된 트리를 순회

void delmalloc(bNode*& pRoot, qNode*& pFront, qNode*& qRear);
nNode* Newenqueue(nNode* pRear, bNode* pdata);//새로운 큐를 만들 함수
void delOld(qNode*& pFront, qNode*& qRear);//기존의 큐를 할당해제 할 함수
void deltree(nNode*& pFront, nNode*& pRear, bNode*& pRoot);//트리의 노드를 할당해제하는 함수
bNode* Newpeek(nNode* pFront);//새로 생성된 큐에서 제일 앞에 노드를 피크
void Newdequeue(nNode*& pFront);//새로 생성된 큐에서 제일 앞에 노드를 디큐

//할당 해제 함수
//ㄴ 큐 자료구조 할당해제
//ㄴ 트리 할당해제
//	ㄴ 큐 자료구조 활용 할당해제 


int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);// 메모리 누수 검사

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

	delmalloc(pRoot, pFront, pRear);//사용한 자료구조 할당해제

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
	delOld(pFront, pRear);//더블포인터 큐 전체 초기화 ( 할당해제 )
	nRear = Newenqueue(nRear, pRoot);//새로운 큐 노드 생성( 트리의 루트 노드 )
	nFront = nRear;
	deltree(nFront, nRear, pRoot);//트리를 왼쪽부터 차래로 낮은 레벨부터 할당 해제 + 동시에 큐할당해제
}
nNode* Newenqueue(nNode* pRear, bNode* pdata)//새로운 큐를 만들 함수
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
//새로운 queue에서 자료를 피크
bNode* Newpeek(nNode* pFront) {
	nNode* pNode = NULL;
	if (!pFront) return NULL;

	pNode = pFront;
	if (pNode->pData) return pNode->pData;
	else return NULL;
}
//새로운 큐의 디큐
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
void delOld(qNode*& pFront, qNode*& pRear)//기존의 큐를 할당해제 할 함수
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
void deltree(nNode*& pFront, nNode*& pRear, bNode*& pRoot)//트리의 노드를 할당해제하는 함수
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
