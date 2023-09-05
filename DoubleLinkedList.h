#pragma once
#include <iostream>

template <typename T> class DoubleLinkedList
{
protected:
	int m_Size = 0;

	struct Node
	{
		Node(T a_Data) : m_Data{ a_Data }, m_Next{ nullptr }, m_Previous{ nullptr } {}
		~Node() {}

		void Delete() // For Deleting the list
		{
			if (m_Next != nullptr)
				m_Next->Delete();
			delete this;
		}

		T	  m_Data;
		Node* m_Next;
		Node* m_Previous;
	};
	struct Iterator
	{
	public:
		Node* m_Value;

		Iterator(Node* a_Value) : m_Value{ a_Value } {}



		Iterator& operator++() 	  // Prefix ++i
		{
			m_Value = m_Value->m_Next;
			return *this;
		}

		Iterator operator++(int) // Postfix i++
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

		T& operator*()
		{
			return m_Value->m_Data;
		}

		T* operator->()
		{
			return &m_Value->m_Data;
		}
	};

	Node* m_Head;
	Node* m_Tail;

	Node* NodeAt(int a_Index) // Returns the Node at the Index
	{
		if (a_Index >= m_Size)
			throw std::out_of_range("No Value at Index");

		Node* CurrentNode = m_Head;
		for (int i = 0; i < a_Index; ++i)
		{
			CurrentNode = CurrentNode->m_Next;
		}
		return CurrentNode;
	}

	void  SwapNodes(Node* Larger, Node* Smaller)
	{
		Node* TempLargerPrevious = Larger->m_Previous;
		
		Larger->m_Previous = Smaller;
		Larger->m_Next = Smaller->m_Next;

		Smaller->m_Previous = TempLargerPrevious;
		Smaller->m_Next = Larger;

		if (Larger == m_Head)
			m_Head = Smaller;
		else
			Smaller->m_Previous->m_Next = Smaller;

		if (Smaller == m_Tail)
			m_Tail = Larger;
		else
			Larger->m_Next->m_Previous = Larger;
	}

public:
	#pragma region Constructors

	DoubleLinkedList()
	{
		m_Head = nullptr;
		m_Tail = nullptr;
		m_Size = 0;
	}

	~DoubleLinkedList()
	{
		m_Head->Delete();
	}

	#pragma endregion

	#pragma region Add

	void PushFront(const T& a_Item) // Adds the item at the front of the list
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

	void PushBack(const T& a_Item)	// Adds the item at the end of the list
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
			m_Tail->m_Next = NewTail;
			m_Tail = NewTail;
		}

		m_Size++;
	}

	void PushAt(const T& a_Item, int a_Index) // Adds the item at the index in the list
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

	#pragma endregion

	#pragma region Remove

	void RemoveFront() // Removes an item from the front of the list
	{
		if (m_Head == nullptr)
		{
			throw std::out_of_range("The List is Empty");
		}

		if (m_Size > 1)
		{
			m_Head = m_Head->m_Next;
			delete m_Head->m_Previous;
			m_Head->m_Previous = nullptr;
		}
		else
		{
			delete m_Head;
		}

		m_Size--;
	}

	void RemoveBack() // Removes an item from the back of the list
	{
		if (m_Tail == nullptr)
		{
			throw std::out_of_range("The List is Empty");
		}

		if (m_Size > 1)
		{
			m_Tail = m_Tail->m_Previous;
			delete m_Tail->m_Next;
			m_Tail->m_Next = nullptr;
		}
		else
		{
			delete m_Head;
		}

		m_Size--;
	}

	void RemoveFrom(Iterator* a_NodeToRemove) // Removes an item from the list at the Iterator
	{
		if (a_NodeToRemove->m_Value == m_Head)
		{
			RemoveFront();
			return;
		}
		if (a_NodeToRemove->m_Value == m_Tail)
		{
			RemoveBack();
			return;
		}

		a_NodeToRemove->m_Value->m_Previous->m_Next = a_NodeToRemove->m_Value->m_Next;
		a_NodeToRemove->m_Value->m_Next->m_Previous = a_NodeToRemove->m_Value->m_Previous;

		delete a_NodeToRemove->m_Value;

		m_Size--;
	}

	void RemoveThis(const T& a_Search) // Removes the first item from the list that matches the search
	{

	}

	#pragma endregion

	#pragma region Return Value

	int  Size() { return m_Size; }
	bool IsEmpty() { return m_Size == 0; }

	T& Front()
	{
		if (m_Head != nullptr)
			return m_Head->m_Data;
	}

	T& Back()
	{
		if (m_Tail != nullptr)
			return m_Tail->m_Data;
	}

	T& operator[](int a_Index)
	{
		return NodeAt(a_Index)->m_Data;
	}

	#pragma endregion

	void Sort()
	{
		// Bubble Sort Algorithm
		bool Swapped = false;
		do // Sorts atleast once
		{
			Swapped    = false;
			auto Left  = Begin(); 
			auto Right = Begin(); 
			// Right is an Iterator that will always be ONE node ahead of Left
			Right++; 

			while ( Right != End() )
			{
				// If the Value of Left is Greater than the Value or Right
				if (Left.m_Value->m_Data > Right.m_Value->m_Data)
				{
					SwapNodes(Left.m_Value, Right.m_Value);
					Right++; // Increment Right so it remains one node ahead of Left
					Swapped = true;
				}
				Left++;
				Right++;
			}
		} while (Swapped == true); // Continue Sorting until NO values have been Swapped
	}

	Iterator Begin() { return Iterator(m_Head); }
	Iterator End() { return Iterator(nullptr); }
};

