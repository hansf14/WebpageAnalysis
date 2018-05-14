#ifndef LINKED_LIST_H
#define LINKED_LIST_H

////////////////////////////////////////////////////////////////

//front declare
template <typename NodeData, typename Key, typename HeaderData>
class LinkedList;
template<typename NodeData, typename Key>
class LinkedListNode;

template <typename T>
class FileFunctor;

template <typename Key, typename HeaderData>
class DocLinkedList;

template <typename Key, typename HeaderData>
class StringLinkedList;

////////////////////////////////////////////////////////////////


template<typename NodeData, typename Key = int, typename HeaderData = int>
class LinkedListIter
{
protected:
	LinkedList<NodeData, Key, HeaderData>* m_pList;
	LinkedListNode<NodeData, Key>* m_pCurNode;

private:
	//Nullify
	LinkedListIter()
	{}
public:
	LinkedListIter(LinkedList<NodeData, Key, HeaderData> *pList)
		: m_pList(pList), m_pCurNode(pList->head)
	{}
	LinkedListIter(LinkedListIter<NodeData, Key, HeaderData> const& other)
		: m_pList(other.m_pList), m_pCurNode(other.m_pCurNode)
	{}
	~LinkedListIter(){}
public:
	NodeData* getNodeData()
	{
		return m_pCurNode->getNodeData(); 
	}
	
	bool hasNext() //return the pointer of the next task pointer
	{
		return (m_pCurNode->next != NULL);
	}
	LinkedListNode<NodeData, Key>* next()
	{
		return (m_pCurNode = m_pCurNode->next);
	}
	LinkedListNode<NodeData, Key>* getNext()
	{
		return (m_pCurNode->next);
	}

	//bool hasPrev()
	//{
	//
	//}
	//Task *prev()
	//{
	//
	//}

	LinkedListNode<NodeData, Key>* curr()
	{
		return m_pCurNode;
	}
	
	void reset()
	{
		m_pCurNode = m_pList->head;
	}
	
	bool isValid()
	{
		return (m_pCurNode != NULL);
	}

public:
	LinkedListIter<NodeData, Key, HeaderData> const& operator=
		(LinkedListIter<NodeData, Key, HeaderData> const& iter)
	{
		this->m_pList = iter.m_pList;
		this->m_pCurNode = iter.m_pTaskCurr;
		return *this;
	}
};

template<typename NodeData, typename Key = int>
class LinkedListNode
{
	template<typename NodeData, typename Key, typename HeaderData>
	friend class LinkedListIter;
	template <typename NodeData, typename Key, typename HeaderData>
	friend class LinkedList;

	template <typename Key, typename HeaderData>
	friend class DocLinkedList;
	template <typename Key, typename HeaderData>
	friend class StringLinkedList;

protected:
	NodeData* m_data;
public:
	Key m_key;
protected:
	LinkedListNode<NodeData, Key> *next;
	//LinkedListNode<T> *prev;

public:
	LinkedListNode(NodeData const& data, Key const& key) : m_data(new NodeData(data)), m_key(key), next(NULL){}
private:
	LinkedListNode(NodeData* data, Key const& key) : m_data(data), m_key(key), next(NULL){}
public:
	virtual ~LinkedListNode(){ delete m_data; m_data = NULL; } 
	//To support nested LinkedList need to make it NULL to prevent dealloc duplicate

public:
	virtual void print(){ m_data->print(); }
	NodeData* getNodeData(){ return m_data; }
	Key const& getKey(){ return m_key; }

	void setNext(LinkedListNode<NodeData, Key> *link)
	{
		next = link;
	}
	LinkedListNode<NodeData, Key>* getNext()
	{
		return next;
	}
};

template <typename NodeData, typename Key = int, typename HeaderData = int>
class LinkedList
{
	template<typename NodeData, typename Key, typename HeaderData>
	friend class LinkedListIter;

	template <typename Key, typename HeaderData>
	friend class StringLinkedList;

	//Data field
public:
	HeaderData m_HeaderData;
protected:
	int size; //count the nodes
	
	//Link field
	LinkedListNode<NodeData, Key>* head;
	LinkedListNode<NodeData, Key>* tail;

public:
	LinkedList() : head(NULL), tail(NULL), size(0), m_HeaderData(){}
	virtual ~LinkedList();

	bool isEmpty() const { return(head == NULL); };
	int getSize() const { return size; }

	LinkedListNode<NodeData, Key>* append(NodeData const& data, Key const& key); //add at last
	LinkedListNode<NodeData, Key>* appendList(NodeData* list, Key const& key);
	int remove(Key const& key); //TODO //return remove result in int value
	int remove(LinkedListNode<NodeData, Key>*& pTargetNode); //if successful, assign pTargetNode to NULL (TODO)

	//void removeAll(const String srcString); //TODO
	//StringLinkedListNode* searchAll(const String srcString); //TODO

	LinkedListNode<NodeData, Key>* search(Key const& key) const;
	LinkedListNode<NodeData, Key>* search(NodeData const& data) const;

	template <typename ReferredObj>
	void traverse(FileFunctor<ReferredObj>& func) const;

	virtual void print() const;

	void setHead(LinkedListNode<NodeData, Key>*	link)
	{
		head = link;
	}
	void setTail(LinkedListNode<NodeData, Key>*	link)
	{
		tail = link;
	}
	LinkedListNode<NodeData, Key>** getHead()
	{
		return head;
	}
	LinkedListNode<NodeData, Key>** getTail()
	{
		return tail;
	}
};

template <typename NodeData, typename Key, typename HeaderData>
LinkedList<NodeData, Key, HeaderData>::~LinkedList()
{
	LinkedListNode<NodeData, Key> *pNextNode = NULL;
	while (head)
	{
		pNextNode = head->next;
		delete head;
		head = pNextNode;
	}
}

template <typename NodeData, typename Key, typename HeaderData>
LinkedListNode<NodeData, Key>* LinkedList<NodeData, Key, HeaderData>::append(NodeData const& data, Key const& key)
{
	LinkedListNode<NodeData, Key> *pNewNode = NULL;
	if (!head) //empty list
	{
		pNewNode = new LinkedListNode<NodeData, Key>(data, key);
		head = pNewNode;
		tail = pNewNode;

		size++;
		return pNewNode;
	}
	pNewNode = new LinkedListNode<NodeData, Key>(data, key);
	tail->next = pNewNode;
	tail = pNewNode;

	size++;
	return pNewNode;
}

template <typename NodeData, typename Key, typename HeaderData>
LinkedListNode<NodeData, Key>* LinkedList<NodeData, Key, HeaderData>::appendList(NodeData* list, Key const& key)
{
	LinkedListNode<NodeData, Key> *pNewNode = NULL;
	if (!head) //empty list
	{
		pNewNode = new LinkedListNode<NodeData, Key>(list, key);
		head = pNewNode;
		tail = pNewNode;

		size++;
		return pNewNode;
	}
	pNewNode = new LinkedListNode<NodeData, Key>(list, key);
	tail->next = pNewNode;
	tail = pNewNode;

	size++;
	return pNewNode;
}

template <typename NodeData, typename Key, typename HeaderData>
int LinkedList<NodeData, Key, HeaderData>::remove(Key const& key)
{
	LinkedListNode<NodeData, Key>* pTargetNode = head;
	LinkedListNode<NodeData, Key>* pPrev = NULL;
	while (pTargetNode && pTargetNode->m_key != key)
	{
		pPrev = pTargetNode;
		pTargetNode = pTargetNode->next;
	}
	if (!pTargetNode) //Not exist
		return -1;

	if (pTargetNode == head)
		head = pTargetNode->next;
	if (pTargetNode == tail)
	{
		pPrev->next = NULL;
		tail = pPrev;
	}
	delete pTargetNode;
	size--;
	return 0;
}

template <typename NodeData, typename Key, typename HeaderData>
int LinkedList<NodeData, Key, HeaderData>::remove(LinkedListNode<NodeData, Key>*& pTargetNode)
{
	if (!pTargetNode)
		return -1;

	if (pTargetNode == head)
	{
		head = pTargetNode->next;
		delete pTargetNode;
		size--;
		return 0;
	}

	LinkedListNode<NodeData> *pPrev = head;
	while (pPrev->next && (pPrev->next != pTargetNode))
		pPrev = pPrev->next;
	pPrev->next = pTargetNode->next;
	if (pTargetNode == tail)
		tail = pPrev;
	delete pTargetNode;

	size--;
	return 0;
}

template <typename NodeData, typename Key, typename HeaderData>
LinkedListNode<NodeData, Key>* LinkedList<NodeData, Key, HeaderData>::search(Key const& key) const
{
	LinkedListNode<NodeData, Key> *pTargetNode = head;
	while (pTargetNode)
	{
		if (pTargetNode->m_key == key)
			return pTargetNode;
		pTargetNode = pTargetNode->next;
	}
	return NULL;
}

template <typename NodeData, typename Key, typename HeaderData>
LinkedListNode<NodeData, Key>* LinkedList<NodeData, Key, HeaderData>::search(NodeData const& data) const
{
	LinkedListNode<NodeData, Key> *pTargetNode = head;
	while (pTargetNode)
	{
		if (pTargetNode->m_data == data)
			return pTargetNode;
		pTargetNode = pTargetNode->next;
	}
	return NULL;
}

template <typename NodeData, typename Key, typename HeaderData>
template <typename ReferredObj>
void LinkedList<NodeData, Key, HeaderData>::traverse(FileFunctor<ReferredObj>& func) const
{
	LinkedListNode<NodeData, Key> *pNode = head;
	while (pNode)
	{
		func.operator() < NodeData > (*(pNode->getNodeData()));
		pNode = pNode->next;
	}
}

template <typename NodeData, typename Key, typename HeaderData>
void LinkedList<NodeData, Key, HeaderData>::print() const
{
	LinkedListNode<NodeData, Key>* pTargetNode = head;
	while (pTargetNode)
	{
		pTargetNode->print();
		pTargetNode = pTargetNode->next;
	}
}

//void removeAll(const String srcString)
//{
//
//}


//StringLinkedListNode* searchAll(const String srcString)
//{
//
//}

#endif