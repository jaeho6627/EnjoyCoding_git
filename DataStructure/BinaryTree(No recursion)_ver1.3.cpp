/*
파일명 : BinaryTree(Heap)_ver1.3_.cpp
목적 : 힙트리를 구현
작성자	: 정재호 ( jhjy5369@naver.com)
파일작성일 : 19.8.22
마지막수정 : 19.8.27

구현기능
1. 포화이진트리 생성
2. 큐생성
3. enqueue
4. dequeue
5. peek
6. 트리 재귀 순회
7. 트리 반복 순회
미구현기능
	1. 스택을 이용한 트리 순회
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

bNode* addRoot(int data);//루트 노드에 10을 자장할 함수
qNode* enqueue(qNode* pRear, bNode* data);//루트 포인터가 가리키는 노드의 주소값을 큐에 저장하는 함수
qNode* dequeue(qNode* pFront);
void addTree(qNode*& pFront, qNode*& pRear, int data);//큐에 저장된 주소값을 기준으로 다음 값을 저장하는 함수
void retraversals(bNode* parentNode);//트레블 함수
void traversals(bNode* parentNode);// no 재귀

int main(void) {
	bNode* pRoot=NULL;
	qNode* pFront=NULL;
	qNode* pRear=NULL;

	pRoot = addRoot(10);//트리에 10 저장
	pRear = enqueue(pRear, pRoot);//트리 root node 의 주소값을 큐에 저장
	pFront = pRear;

	addTree(pFront, pRear, 20);//큐에 저장된 주소값을 기준으로 20 저장
	addTree(pFront, pRear, 30);//쿠에 저장된 주소값을 기준으로 30 저장
	addTree(pFront, pRear, 40);//큐에 저장된 주소값을 기준으로 40 저장
	addTree(pFront, pRear, 50);//큐에 저장된 주소값을 기준으로 50 저장
	addTree(pFront, pRear, 60);//큐에 저장된 주소값을 기준으로 60 저장
	addTree(pFront, pRear, 70);//큐에 저장된 주소값을 기준으로 70 저장


	traversals(pRoot);//반복문 순회
	retraversals(pRoot);//재귀 함수 순회


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

