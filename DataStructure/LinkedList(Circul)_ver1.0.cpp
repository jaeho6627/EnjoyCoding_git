/*******************************************
파일이름 : LinkedList(Circul)_ver1.0.cpp
제작날짜 : 19.08.14
수정날짜 : 00.00.00
제 작 자 : 정재호(hoje)
이 메 일 : jhjy5369@naver.com
블 로 그 : https://blog.naver.com/jhjy5369
파일목적 : 환형 연결 리스트를 이해하고 구현
코드설명 : 
	1. 환형 연결리스트를 구현하기 위해 일반 노드와 헤더 노드를 구조체로 정의 하였다.
	2. 헤더 노드는 항상 시작노드을 가리키며 일반 노드 자료형은 리스트를 구성하는 노드가 된다.
	3. 노드 포인터를 이용해 리스트의 마지막을 표시해 둔다.
	4. 구현의 편의상 리스트에 추가하는 데이터는 항상 리스트의 마지막 노드 뒤에 추가된다. 
	5. 추가된 노드는 리스트에 추가하는 작업을 마치면 처음 노드를 가리키도록 해야한다.
	6. 리스트에 노드가 하나밖에 없을 경우 해당 노드의 링크를 NULL로 저장한다.
	7. 에러가 발생할 수 있는 경우을 모두 확인해 실행시 코드번호를 출력해 무슨 에러인지 또는 어디에 에러가 났는지 확인할 수 있도록 도와야함
구현목록 : 
	1. 구조체 자료형
	2. 에러코드값을 저장할 열거형 자료형
	3. 사용할 함수들의 선언
	4. main 함수 정의
	5. 리스트 추가, 노드 추가, 리스트 전체 출력 함수
	6. 리스트 현재 노드 개수 출력
	7. 리스트 data 검색
다음구현목표 :
	1. 위치 값으로 해당 data 출력하는 함수
	2. 검색 data 삭제
	3. 위치 값으로 data 삭제
	4. 리스트 전체 삭제
	5. 환형 연결리스트인지 확인하는 함수
********************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*
기존 일반 연결리스트(Linked List)에 추가적으로 마지막 노드가 첫 노드를 가리키도록 한다.
노드를 추가할때 리스트의 첫 노드가 없을 경우 헤더노드에 연결 후 이 첫 노드의 링크를 NULL로 함
두번째 노드가 추가될 때 부터 노드가 추가되면 마지막에 자리에 추가될 경우 항상 첫 노드를 링크하도록 변경
(노드*를 이용해 마지막 노드를 항상 가리키도록 함) ( 마지막 노드는 헤더 노드가 가리키는 첫 노드를 가리키는 노드를 의미)
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


//노드 추가
NODE * CreateNode(hNODE * header, NODE * pEnd, int data);
//노드 검색
NODE * FindNode(hNODE * Header, NODE * pEnd, int data);
//노드 제거
ERRORCODE DelNode(hNODE * Header, int data);
//리스트 생성
hNODE * CreateCirLinkL(void);
//리스트 삭제
ERRORCODE DeleteCirLinkL(hNODE * Header);
//리스트 출력
void PrintCirLinkL(hNODE * Header, NODE * pEnd, int count);
//노드 개수 출력
void cPrintCirLinkL(hNODE * header);

int main(void) {
	
	//리스트를 생성
	hNODE* Header = CreateCirLinkL();
	//리스트의 마지막 노드
	NODE* pEndNODE = Header->DumNode.pLink;
	NODE* pFindNODE = NULL;
	
	pEndNODE = CreateNode(Header, pEndNODE, 10);//10노드추가
	pEndNODE = CreateNode(Header, pEndNODE, 20);//20노드추가
	pEndNODE = CreateNode(Header, pEndNODE, 30);//30노드추가
	pEndNODE = CreateNode(Header, pEndNODE, 40);//40노드추가
	
	PrintCirLinkL(Header, pEndNODE, 1);//리스트 출력
	cPrintCirLinkL(Header);
	pFindNODE=FindNode(Header, pEndNODE, 20);//20노드 검색
	if (pFindNODE) {
		printf("Find data : %d\n", pFindNODE->data);
	} //검색결과 출력
	
	
	//30노드 제거
	//리스트 출력
	//리스트 제거
	//리스트 출력

	return 0;
}
//노드 추가
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
////노드 검색
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
////노드 제거
//ERRORCODE DelNode(hNODE * Header, int data) {
//}
//리스트 생성
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
////리스트 삭제
//ERRORCODE DeleteCirLinkL(hNODE * Header) {
//
//}
//리스트 출력
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
//노드 개수 출력
void cPrintCirLinkL(hNODE * header) {
	if (header == NULL) {
		printf("[Error %d] There's no list", ERRORCODE::LISTALLOTERROR);
		return;
	}
	else {
		printf("Data node : %d\n", header->CurrNode);
	}
}