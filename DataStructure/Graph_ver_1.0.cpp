/*
파일이름	: Graph_ver_1.0.cpp
작 성 자	: 정재호 (jhjy5369@naver.com)
파일목적	: 그래프 자료구조를 구현 순회하는 함수 구현
작성일자	: 2019.08.29
수정일자	: 2019.08.30
구현기능	: 그래프 순회
미구현기능 : 
	1. 그래프 생성
	2. 그래프 할당해제
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct gNode {
	int data;
	gNode* pLink_1;
	gNode* pLink_2;
	gNode* pLink_3;
};

struct sNode {
	gNode* pData;
	sNode* pNext;
};
gNode* creatNode(int data);//그래프 연결 함수
void Print(gNode* pSeed);//그래프 연결 확인 함수

//스택 관련 함수
sNode* push(sNode* pFront, gNode* pData);
sNode* pop(sNode*& pFront);
gNode* peek(sNode* pFront);
bool serch(sNode* pFront, gNode* pData);

int main(void) {
	gNode* Anode = creatNode(10);
	gNode* Bnode = creatNode(20);
	gNode* Cnode = creatNode(30);
	gNode* Dnode = creatNode(40);
	gNode* Enode = creatNode(50);
	
	Anode->pLink_1 = Bnode;
	Bnode->pLink_1 = Cnode;
	Bnode->pLink_2 = Dnode;
	Bnode->pLink_3 = Enode;
	Cnode->pLink_1 = Dnode;
	Cnode->pLink_2 = Enode;
	Dnode->pLink_1 = Enode;

	Print(Anode);



	return 0;
}
gNode* creatNode(int data) {
	gNode* pTemp = NULL;
	pTemp = new gNode;
	if (!pTemp) return NULL;

	memset(pTemp, 0, sizeof(gNode));
	pTemp->data = data;
	return pTemp;
}
void Print(gNode* pSeed) {
	sNode* pFront = NULL;
	sNode* pNode = NULL;

	pFront = push(pFront, pSeed);

	pNode = pFront;

	while (pNode) {
		gNode* pPoint = NULL;
		pPoint = peek(pNode);
		pFront = pop(pNode);

		printf("< %d ", pPoint->data);
		if (pPoint->pLink_1 || pPoint->pLink_2 || pPoint->pLink_3) {
			printf(": ");
			if (pPoint->pLink_1) {
				printf("%d ", pPoint->pLink_1->data);
				
			}
			if (pPoint->pLink_2) {
				if (pPoint->pLink_1) printf(",");
				printf("%d ", pPoint->pLink_2->data);
				
			}
			if (pPoint->pLink_3) {
				if (pPoint->pLink_1 || pPoint->pLink_2) printf(",");
				printf("%d ", pPoint->pLink_3->data);
				
			}
		}
		printf(">\n");
		if(pPoint->pLink_3) 
			if (serch(pFront, pPoint->pLink_3)) 
				pFront = push(pFront, pPoint->pLink_3);
		if(pPoint->pLink_2) 
			if (serch(pFront, pPoint->pLink_2)) 
				pFront = push(pFront, pPoint->pLink_2);
		if(pPoint->pLink_1) 
			if (serch(pFront, pPoint->pLink_1))	
				pFront = push(pFront, pPoint->pLink_1);
		
		pNode = pFront;
	}
	return;
}

sNode* push(sNode* pFront, gNode* pData) {
	sNode* pTemp = NULL;
	pTemp = new sNode;
	if (!pTemp) return NULL;
	memset(pTemp, 0, sizeof(sNode));

	pTemp->pData = pData;

	if (pFront) {
		pTemp->pNext = pFront;
	}
	return pTemp;
}
sNode* pop(sNode*& pFront) {
	sNode* pDel = NULL;
	if (!pFront)return NULL;
	pDel = pFront;
	if (pFront->pNext) {
		pFront = pFront->pNext;
	}
	else {
		pFront = NULL;
	}
	delete pDel;
	return pFront;
}
gNode* peek(sNode* pFront) {
	gNode* pTemp = NULL;
	if (!pFront)return NULL;

	pTemp = pFront->pData;

	return pTemp;
}
bool serch(sNode* pFront, gNode* pData) {
	sNode* pNode = NULL;
	if (!pData) return false;
	else if (!pFront) return true;
	else {
		pNode = pFront;
		while (pNode->pData != pData) {
			if (pNode->pNext) {
				pNode = pNode->pNext;
			}
			else {
				return true;
			}
		}
		return false;
	}
}