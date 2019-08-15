/******************************************
파일이름	: DoubleLinkedList_ver1.0.cpp
코드목적	: 환형 이중 연결 리스크를 구현
작성요일	: 19.08.14
수정요일	: 00.00.00
작 성 자	: 정재호
블 로 그	: http://jhjy5369.blog.me/NBlogWlwLayout.nhn?blogId=jhjy5369
구현코드	: 
미구현코드:
	2. 노드검색 (역방향, 정방향)
	3. 노드삭제
	4. 리스트삭제
구현코드	:
	1. 리스트 생성
	2. 노드생성
	3. 리스트 출력(정방향, 역방향)

******************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
이중연결노드는 링크부분이 이전노드와 이후노드 둘다 가리킨다.
노드에 링크 부분이 두 개 있는 모양이다.
노드 생성시 이전 노드를 가리키는 링크를 이전 노드의 주소값을 가리키게 하고 다음 노드를 가리키게 하는 링크를 다음 노드의 주소값을 저장하면 된다.

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

hnode* createList(void); //리스트 생성
node* createNode(hnode* pHeader, node* pEnd, int data);//노드생성
void printDouList_f(node* const pBegin, node* const pEnd);//리스트 출력(정)
void printDouList_d(node* const pBegin, node* const pEnd);//리스트 출력(역)
node* findDouList_f(node* const pBegin, node* const pEnd, int data);//노드검색(정)
node* findDouList_d(node* const pBegin, node* const pEnd, int data);//노드검색(역)
//노드삭제
//리스트 삭제

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

	//30노드 검색(정방향)
	//검색된 노드 출력

	//20노드 검색(역방향)
	//검색된 노드 출력
	
	//40노드 삭제
	//리스트 출력

	//리스트 삭제
	//리스트 출력 (출력되면 안됨)
	return 0;
}

//리스트 생성
hnode* createList(void) {
	hnode* pTemp = NULL;
	pTemp = new hnode;
	if (pTemp == NULL) {
		printf("리스트 할당이 정상적이지 않습니다.\n");
		return pTemp;
	}
	memset(pTemp, 0, sizeof(hnode));
	return pTemp;
}
//노드생성
node* createNode(hnode* const pHeader, node* pEnd, int data) {
	node* pTemp = new node;
	pTemp->data = data;
	
	if (pTemp == NULL) {
		printf("노드 생성에 오류가 있습니다.");
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
//리스트 출력 (정방향)
void printDouList_f(node* const pBegin, node* const pEnd) {
	if (pBegin == NULL || pEnd == NULL) {
		printf("리스트 출력에 문제가 있습니다.\n");
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
//리스트 출력 (역방향)
void printDouList_d(node* const pBegin, node* const pEnd) {
	if (pBegin == NULL || pEnd == NULL) {
		printf("리스트 출력에 문제가 있습니다.\n");
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
//노드검색(정)
node* findDouList_f(node* const pBegin, node* const pEnd, int data) {
	
}
//노드검색(역)
node* findDouList_d(node* const pBegin, node* const pEnd, int data) {

}