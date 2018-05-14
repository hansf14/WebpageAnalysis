#ifndef DOC_LINKED_LIST_H
#define DOC_LINKED_LIST_H

#include "LinkedList.h"

//front declare
template <typename Key, typename HeaderData>
class DocLinkedList;


template <typename Key = int>
class Doc
{
	template <typename Key, typename HeaderData>
	friend class DocLinkedList;

private:
	String m_strFileName;
	Key m_DocID;
	int m_Times;
	
public:
	Doc(String const& filename, Key ID) :m_strFileName(filename), m_DocID(ID), m_Times(0){}
	virtual ~Doc(){}

public:
	void increaseTimes(){ m_Times++; }

	Key const& getID() const { return m_DocID; }
	int getTimes() const{ return m_Times; }
//	String const& getFileName{ return m_strFileName; }

	virtual void print()
	{
		printf("["); m_strFileName.print(); printf("]");
		printf("[ID : %4d][Times : %d]\n",m_DocID,m_Times);
	}
};

template <typename Key = int, typename HeaderData = int>
class DocLinkedList : public LinkedList<Doc<Key>, Key, HeaderData>
{
public:
	DocLinkedList(){}
	virtual ~DocLinkedList(){}

public:
	int edit(Key const& ID, String const& newFileName, Key const& newID, int times)
	{
		LinkedListNode<Doc<Key>, Key>* pDocLinkedListNode = this->search(ID);
		if (!pDocLinkedListNode)
		{
			Doc<Key>* pDoc = pDocLinkedListNode->getNodeData();
			pDoc->m_DocID = newID;
			pDoc->m_strFileName = newFileName;
			pDoc->m_Times = times;

			return 0;
		}
		else
			return -1;
	}

	int edit(Key const& ID, Key const& newID, int times)
	{
		LinkedListNode<Doc<Key>, Key>* pDocLinkedListNode = this->search(ID);
		if (!pDocLinkedListNode)
		{
			Doc<Key>* pDoc = pDocLinkedListNode->getNodeData();
			pDoc->m_DocID = newID;
			pDoc->m_Times = times;

			return 0;
		}
		else
			return -1;
	}
};


#endif