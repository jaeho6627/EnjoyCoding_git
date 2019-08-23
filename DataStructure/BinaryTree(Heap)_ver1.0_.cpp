/*
파일명 : BinaryTree(HIP)_ver1.0_.cpp
목적 : 힙트리를 구현
작성자	: 정재호 ( jhjy5369@naver.com)
파일작성일 : 19.8.22
마지막수정 : 19.8.23

힙트리란
다른 말로 포화이진트리를 말함 낮은 레발부터 높은 레벨까지 빈공간이 없이 자리를 채우고 있는 트리를 의미함

큐 자료구조를 활용해 포화 이진트리를 완성함
트리에 data를 추가할때마다 큐에 추가된 노드의 왼쪽 오른쪽 맴버 포인터 변수의 주소 값을 저장한다.
트리에 자료를 추가할때 마다 큐에서 data를 peek해서 트리에 자료를 추가한 후 사용이 끝난 큐는 디큐한다.

미구현기능
	1. 사용이 끝난 메모리 할당해제
		ㄴ 큐와 트리의 데이터 할당해제
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

qNode* enqueue(qNode * pRear, bNode ** Data); //큐 enquequ 연산
bNode** peek(qNode * pFront);//큐 peek연산
qNode* dequeue(qNode* pFront);	//사용이 끝난 큐 데이터 디큐
qNode* treeEnqueue(bNode** pNode, qNode* pRear);	//트리 맴버 포인터 변수의 주소값을 큐에 저장
void createTree(bNode** pNode, int data);	//트리노드를 생성하
void creatNode(qNode** pFront, qNode** pRear, int data);	//트리에 값이저장되는 일련의 작업을 통제
void traversals(bNode * parentNode);	//생성된 트리를 순회



int main(void) {

	bNode * pRoot = NULL;
	qNode * pFront = NULL;
	qNode * pRear = NULL;

	pRear=enqueue(pRear, &pRoot); //먼저 큐에 루트노드를 가리키는 포인터 변수의 주소 값 저장
	pFront = pRear;

	creatNode(&pFront, &pRear, 10);//10추가
	creatNode(&pFront, &pRear, 20);//20추가
	creatNode(&pFront, &pRear, 30);//30추가
	creatNode(&pFront, &pRear, 40);//40추가
	creatNode(&pFront, &pRear, 50);//50추가
	creatNode(&pFront, &pRear, 60);//60추가
	creatNode(&pFront, &pRear, 70);//70추가

	traversals(pRoot);//트리 순회 함수

	//사용한 자료구조 할당해제

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