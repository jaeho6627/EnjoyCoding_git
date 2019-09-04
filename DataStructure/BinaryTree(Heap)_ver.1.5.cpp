/*
파일이름	: BinaryTree(Stack)_ver.1.5.cpp
작 성 자	: 정재호 (jhjy5369@naver.com)
코드목적	: 스택을 사용해 재귀함수를 사용하지 않고 트리의 요소를 순회하는 함수 정의
수 정 일	: 19.9.4
수정내용	: 잘못된 힙 트리 구현 -> 최소 힙 트리 구현 완료
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

struct sNode {//스택의 노드 자료구조
	bNode* nodeData;
	sNode* pNext;

};

bNode* addRoot(int data);
qNode* enqueue(qNode* pRear, bNode* data);
qNode* dequeue(qNode* pFront);
void addTree(qNode*& pFront, qNode*& pRear, int data);
void retraversals(bNode* parentNode);
void traversals(bNode* parentNode);

void check_heap(bNode* pNode); //최소 힙 트리 구현

//스택관련 함수
void push(sNode*& pFront, bNode* data);
bNode* pop(sNode*& pFront);

//스택을 활용해 순회하는 함수
void stacktraver(bNode* parentNode);


int main(void) {
	bNode* pRoot = NULL;
	qNode* pFront = NULL;
	qNode* pRear = NULL;

	pRoot = addRoot(80);
	pRear = enqueue(pRear, pRoot);
	pFront = pRear;

	addTree(pFront, pRear, 30);
	addTree(pFront, pRear, 70);
	addTree(pFront, pRear, 90);
	addTree(pFront, pRear, 10);
	addTree(pFront, pRear, 20);
	addTree(pFront, pRear, 40);


	traversals(pRoot);
	/*retraversals(pRoot);
	stacktraver(pRoot);*/

	return 0;
}

//큐에 트리 주소값(데이터) 저장
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

//트리의 투트 노드를 만들어주는 함수
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

	if (!(pNode->nodeData->pLeft)) { //왼 쪽이 빈 경우
		pNode->nodeData->pLeft = pTemp; //왼쪽에 노드를 추가
		pTemp->pRenode = pNode->nodeData;	//추가한 노드의 이전 부모 노드로 queue에 저장되어 있는 최상위 노드의 데이터 값의 주소를 넣는다.
		check_heap(pTemp); //부모와 자식의 값을 비교해 큰 값을 아래로 내린다.
	}
	else if (!(pNode->nodeData->pRight)) { //오른쪽이 빈 경우
		pNode->nodeData->pRight = pTemp;
		pTemp->pRenode = pNode->nodeData;
		check_heap(pTemp);
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

//스택 관련 함수
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
void check_heap(bNode* pNode) {
	bNode* pParent = pNode->pRenode;

	while (pParent->data > pNode->data) //부호를 반대로 하면 최소힙 , 최대힙 둘다 구현 가능
	{
		int nData = 0;

		nData = pNode->data;
		pNode->data = pParent->data;
		pParent->data = nData;

		if(!pParent->pRenode){
			break;
		}

		pParent = pParent->pRenode;
		pNode = pNode->pRenode;
	}
	return;
}
