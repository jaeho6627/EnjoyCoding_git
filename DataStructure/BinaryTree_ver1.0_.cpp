/*
파일이름	:	BinaryTree_ver1.0_.cpp
파일설명	:	이진 트리 구현
작성자		:	정재호(jhjy5369@naver.com)
작성일		:	19.08.19
마지막수정일:	19.08.19
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

Bnode * createNode(int data);// 노드 생성
Bnode * leftNode(Bnode * pLeft);// 왼쪽 자식 설정
Bnode * rightNode(Bnode * pRight);// 오른쪽 자식 설정
void traversals(Bnode * parentNode);// 이진 배열 순회
void printData(Bnode * pNode);

int main(void) {
	Bnode * pRoot = createNode(10);		//최 상위 노드, 루트 노드
	Bnode * pLeft = createNode(20);		//자식 노드, 왼쪽
	Bnode * pRight = createNode(30);		//자식 노드, 오른쪽
	Bnode * pLd = createNode(40);		//자식 노드
	Bnode * pRd = createNode(50);		//자식 노드

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
}// 노드 생성
Bnode * leftNode(Bnode * pLeft) {
	if (!pLeft) {
		return NULL;
	}
	return pLeft;
}// 왼쪽 자식 설정
Bnode * rightNode(Bnode * pRight) {
	if (!pRight) {
		return NULL;
	}
	return pRight;
}// 오른쪽 자식 설정
void traversals(Bnode * parentNode) {
	if(!parentNode) return;

	traversals(parentNode->pLeft);
	
	traversals(parentNode->pRight);

	printData(parentNode);
}// 이진 배열 순회
void printData(Bnode* pNode) {
	printf("%d ", pNode->data);
}