/***********************************************
파일명	: CPPLinkedList_ver1.0.cpp
작성자	: 정재호 (jhjy5369@naver.com)
수정일	: 2019.09.12
목적		: 단일연결리스트를 c++문법으로 변경
오류목록	: 실행시 메모리누수 2개 발생
***********************************************/
#include <iostream>
#include <string.h>
#include <crtdbg.h>

struct sNode
{
	int data;
	sNode* pNext;
};

class LinkedList
{
private:
	sNode* pBegin = NULL;
	sNode* pEnd = NULL;
	sNode* pFind = NULL;
	int nodeCount = 0;
public:
	void creatNode(int data);
	void findNodeData(int data);
	void deleteNodeData(int del);
	void InsertNodeData(int data, int insert);
	void printLinkedList();
	void DeleteLinkedList();
	void printFindData();
};

int main(void)
{
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);

	LinkedList List;

	List.creatNode(10);
	List.creatNode(20);
	List.creatNode(30);
	List.creatNode(40);
	List.creatNode(50);
	List.creatNode(60);
	List.creatNode(70);

	List.printLinkedList();

	List.findNodeData(40);
	List.printFindData();

	List.InsertNodeData(30, 80);
	List.printLinkedList();

	List.deleteNodeData(20);
	List.printLinkedList();

	List.DeleteLinkedList();
}

void LinkedList::creatNode(int data)
{
	sNode* pTemp = NULL;
	pTemp = new sNode();
	if (!pTemp)
		std::cout << "Malloc Errer" << std::endl;
	else
	{
		memset(pTemp, 0, sizeof(pTemp));
		pTemp->data = data;
		if (!pBegin)
			pBegin = pTemp;
		else
			pEnd->pNext = pTemp;
		pEnd = pTemp;
	}
}
void LinkedList::printFindData()
{
	if (pFind)
		std::cout << "Find: " << pFind->data << std::endl;
	else
		std::cout << "Notting Here~" << std::endl;
}
void LinkedList::findNodeData(int data)
{
	sNode* pNode = pBegin;
	if (!pNode)
	{
		std::cout << "List is noting here" << std::endl;
	}

	while (pNode)
	{
		if (pNode->data == data)
		{
			pFind = pNode;
			pNode = NULL;
		}
		else
		{
			pNode = pNode->pNext;
			if (!pNode)
				std::cout << "\"" <<data <<"\" "<< "I can't find this." << std::endl;
		}
	}
}
void LinkedList::deleteNodeData(int del)
{
	sNode* pNode = pBegin;
	sNode* pPre = NULL;

	if (!pNode)
		std::cout << "Noting list here" << std::endl;

	while (pNode)
	{
		if (pNode->data == del)
		{
			/*if (pNode == pBegin || pNode == pEnd)
				{
					if (pNode != pEnd)
					{
						pBegin = pNode->pNext;
						delete pNode;
					}
					else if (pNode != pBegin)
					{
						pEnd = pPre;
						delete pNode;
					}
					else
					{
						pBegin = NULL;
						pEnd = NULL;
						delete pNode;
					}
				}*/
			if (pNode == pBegin)
				pBegin = pBegin->pNext;
			else if (pNode == pEnd)
				pEnd = pPre;
			else
				pPre->pNext = pNode->pNext;
			pNode->pNext = NULL;
			delete pNode;
			break;
		}
		pPre = pNode;
		pNode = pNode->pNext;
	}

}
void LinkedList::InsertNodeData(int data, int insert)
{
	findNodeData(data);
	if (!pFind)
		std::cout << data << "is no here" << std::endl;
	else
	{
		sNode* pTemp = NULL;
		pTemp = new(sNode);
		if (!pTemp)
			std::cout << "malloc errer" << std::endl;
		else
		{
			pTemp->data = insert;
			pTemp->pNext = pFind->pNext;
			pFind->pNext = pTemp;
			pFind = NULL;
		}
	}
}
void LinkedList::printLinkedList()
{
	if (!pBegin || !pEnd)
		std::cout << "I can't print this";

	sNode* pPrint = pBegin;
	while (pPrint)
	{
		std::cout << pPrint->data;
		if (pPrint->pNext)
		{
			std::cout << ", ";
			pPrint = pPrint->pNext;
		}
		else
			pPrint = NULL;
	}
	std::cout << std::endl;
}
void LinkedList::DeleteLinkedList()
{
	if (!pBegin || !pEnd)
		std::cout << "I can't remove list" << std::endl;

	sNode* pDel = NULL;
	sNode* pNode = pBegin;
	while (!pNode)
	{
		pDel = pNode;
		if(pNode->pNext)
			pNode = pNode->pNext;
		pDel->pNext = NULL;
		delete pDel;
	}
	pBegin = NULL;
	pEnd = NULL;
}