#ifndef KEYWORD_AVL_TREE_H
#define KEYWORD_AVL_TREE_H

#include "String.h"
#include "AVLTree.h"
#include "DocLinkedList.h"

//front declare
template <typename Key>
class KeywordAVLTreeNodeData;

template <typename Key = int>
class Keyword
{
	template <typename Key>
	friend class KeywordAVLTreeNodeData;
public:
	String m_string; //ref only
private:
	Key m_ID;
	int m_DF; //found in how many document files
	int m_Occur; //found how many times in total
	DocLinkedList<Key>* m_pDocLinkedList;

public:
	Keyword(String const& string, Key ID)
		: m_string(string), m_ID(ID), m_DF(0), m_Occur(0), m_pDocLinkedList(NULL)
	{}
	~Keyword(){}

public:
	void increaseDF(){ m_DF++; }
	void increaseOccur(){ m_Occur++; }

	Key getID()const{ return m_ID; }
	int getDF()const{ return m_DF; }
	int getOccur()const{ return m_Occur; }

	Doc<Key>* insert(Doc<Key> const& doc)
	{
		if (!m_pDocLinkedList)
			m_pDocLinkedList = new DocLinkedList<Key>();
		LinkedListNode<Doc<Key>>* pDocLinkedListNode = m_pDocLinkedList->append(doc,doc.getID());
		return pDocLinkedListNode->getNodeData();
	}

	Doc<Key>* searchDoc(Key ID)
	{
		if (!m_pDocLinkedList)
			m_pDocLinkedList = new DocLinkedList<Key>();
		LinkedListNode<Doc<Key>, Key>* pDocLinkedListNode = m_pDocLinkedList->search(ID);
		if (pDocLinkedListNode)
			return pDocLinkedListNode->getNodeData();
		else
			return NULL;
	}
	
	void print()
	{
		printf("["); m_string.print(); printf("]"); printf("[ID : %5d]\n", m_ID);
	}
};

template <typename Key = int>
class KeywordAVLTreeNodeData : public AVLTreeNodeData<Keyword<Key>>
{
private:
	Keyword<Key> keyword;
public:
	KeywordAVLTreeNodeData(String const& string, Key ID) : keyword(string, ID){}
	virtual ~KeywordAVLTreeNodeData(){}

public:
	void increaseDF(){ keyword.increaseDF(); }
	void increaseOccur(){ keyword.increaseOccur(); }
};

template <typename Key = int>
class KeywordAVLTree : public AVLTree<Keyword<Key>>
{
public:
	KeywordAVLTree(){}
	virtual ~KeywordAVLTree(){}

public:
	virtual Keyword<Key>* search(Key ID)
	{
		AVLTreeNode<Keyword<Key>, Key>* pTreeNode =
			(static_cast<AVLTree<Keyword<Key>, Key> *>(this))->search(ID);
		return pTreeNode->getData();
	}

	void increaseDF(Key ID)
	{
		KeywordAVLTreeNodeData<Key> *pNode = this->search(ID);
		if (pNode)
			pNode->increaseDF();
	}

	void increaseOccur(Key ID)
	{
		KeywordAVLTreeNodeData<Key> *pNode = this->search(ID);
		if (pNode)
			pNode->increaseOccur();
	}

};

#endif