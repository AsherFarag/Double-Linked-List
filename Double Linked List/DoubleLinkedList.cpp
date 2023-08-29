#include "DoubleLinkedList.h"
#include <iostream>

DoubleLinkedList::Node* DoubleLinkedList::NodeAt(int a_Index)
{
	if (a_Index > m_Size)
		throw std::runtime_error("No Value at Index");

	Node* CurrentNode = m_Head;
	for (int i = 0; i < a_Index; ++i)
	{
		CurrentNode = CurrentNode->m_Next;
	}
	return CurrentNode;
}



DoubleLinkedList::DoubleLinkedList()
{
	m_Head = nullptr;
	m_Tail = nullptr;
	m_Size = 0;
}

DoubleLinkedList::~DoubleLinkedList()
{
	Node* CurrentNode = m_Head;

	for (int i = 1; i < m_Size; ++i)
	{
		CurrentNode = CurrentNode->m_Next;

		if (CurrentNode->m_Previous != nullptr)
			delete CurrentNode->m_Previous;
	}

	delete CurrentNode;
}


// ===== Push =====
void DoubleLinkedList::PushFront(int a_Item)
{
	Node* NewHead = new Node(a_Item);
	if (m_Head == nullptr)
	{
		m_Head = NewHead;
		m_Tail = NewHead;
	}
	else
	{
		NewHead->m_Next = m_Head;
		m_Head = NewHead;
	}
	m_Size++;
}

void DoubleLinkedList::PushBack(int a_Item)
{
	Node* NewTail = new Node(a_Item);
	if (m_Tail == nullptr)
	{
		m_Head = NewTail;
		m_Tail = NewTail;
	}
	else
	{
		NewTail->m_Previous = m_Tail;
		m_Tail = NewTail;
	}
	m_Size++;
}

void DoubleLinkedList::PushAt(int a_Item, int a_Index)
{
	if (a_Index == 0)
	{
		PushFront(a_Item);
		return;
	}

	if (a_Index >= m_Size)
	{
		PushBack(a_Item);
		return;
	}

	Node* NewNode = new Node(a_Item);

	Node* PreviousNode = NodeAt(a_Index - 1);
	Node* NextNode = PreviousNode->m_Next;

	PreviousNode->m_Next = NewNode;
	NextNode->m_Previous = NewNode;

	NewNode->m_Next = NextNode;
	NewNode->m_Previous = PreviousNode;

	m_Size++;
}


// ===== Pull =====
void DoubleLinkedList::PullFront()
{
	if (m_Head == nullptr)
	{
		return;
	}

	if (m_Size > 1)
	{
		m_Head = m_Head->m_Next;
		delete m_Head->m_Previous;
		m_Size--;
		return;
	}
		
	delete m_Head;
	m_Size--;
}
 
void DoubleLinkedList::PullBack()
{
	if (m_Head == nullptr)
	{
		return;
	}

	if (m_Size > 1)
	{
		m_Tail = m_Tail->m_Previous;
		delete m_Tail->m_Next;
		m_Size--;
		return;
	}

	delete m_Head;
	m_Size--;
}
 
void DoubleLinkedList::PullFrom(int a_Index)
{
	if (a_Index == 0)
	{
		PullFront();
		return;
	}

	if (a_Index >= m_Size)
	{
		PullBack();
		return;
	}

	Node* NodeToRemove = NodeAt(a_Index);
	NodeToRemove->m_Previous->m_Next = NodeToRemove->m_Next;
	NodeToRemove->m_Next->m_Previous = NodeToRemove->m_Previous;

	delete NodeToRemove;

	m_Size--;
}

void DoubleLinkedList::PullThis(int a_Search)
{
	
}



int DoubleLinkedList::ItemAtFront()
{
	if (m_Head != nullptr)
		return m_Head->m_Data;
}

int DoubleLinkedList::ItemAtEnd()
{
	if (m_Tail != nullptr)
		return m_Tail->m_Data;
}

int DoubleLinkedList::operator[](int a_Index)
{
	return NodeAt(a_Index)->m_Data;
}



bool DoubleLinkedList::AttemptSort()
{
	return false;
}
