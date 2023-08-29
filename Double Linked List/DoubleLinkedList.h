#pragma once
class DoubleLinkedList
{
protected:
	int m_Size = 0;

	struct Node
	{
		Node(int a_Data) : m_Data{ a_Data }, m_Next{ nullptr }, m_Previous{ nullptr } {}

		void Destroy()
		{
			if (m_Next != nullptr)
			{
				m_Next->Destroy();
			}
			delete this;
		}

		int	  m_Data;
		Node* m_Next;
		Node* m_Previous;
	};

	Node* m_Head;
	Node* m_Tail;

	Node* NodeAt(int a_Index);

public:
	struct Iterator
	{
	private:
		Node* m_Value;

	public:
		Iterator(Node* a_Value) : m_Value{a_Value}{}

		Iterator& operator++() 	  // Prefix ++i
		{
			m_Value = m_Value->m_Next;
			return *this;
		}

		Iterator& operator++(int) // Postfix i++
		{
			Iterator Temp = *this;
			m_Value = m_Value->m_Next;
			return Temp;
		}

		friend bool operator!=(const Iterator& LeftHandSide, const Iterator& RightHandSide)
		{
			return LeftHandSide.m_Value != RightHandSide.m_Value;
		}

		friend bool operator==(const Iterator& LeftHandSide, const Iterator& RightHandSide)
		{
			return LeftHandSide.m_Value == RightHandSide.m_Value;
		}

		int operator*()
		{
			return m_Value->m_Data;
		}

		Node* operator->()
		{
			return m_Value;
		}
	};

	// === Constructors ===
	DoubleLinkedList();
	~DoubleLinkedList();

	// Adding an Element
	void PushFront(int a_Item);			  // Adds the item at the front of the list		   
	void PushBack(int a_Item);			  // Adds the item at the end of the list
	void PushAt(int a_Item, int a_Index); // Adds the item at the index in the list

	// Removing an Element
	void PullFront();			 // Removes an item from the front of the list
	void PullBack();			 // Removes an item from the front of the list
	void PullFrom(int a_Index);  // Removes an item from the list at the index
	void PullThis(int a_Search); // Removes the first item from the list that matches the search

	int  GetItemCount() { return m_Size; }
	bool IsEmpty() { return m_Size == 0; }
	int  ItemAtFront();
	int  ItemAtEnd();
	int  operator[](int a_Index);

	bool AttemptSort();

	Iterator Begin() { return Iterator(m_Head); }
	Iterator End() { return Iterator(m_Tail->m_Next); }
};

