#ifndef AVL_TREE_H
#define AVL_TREE_H

#include <stdio.h>
#include <memory.h>
#include "LinkedStack.h"

////////////////////////////////////////////////

//front declare
template <typename T, typename Key>
class AVLTree;
template <typename T, typename Key>
class AVLTreeNode;

template <typename T>
class FileFunctor;

////////////////////////////////////////////////

template <typename T, typename Key = int>
class AVLTreeNodeData
{
	template <typename T, typename Key>
	friend class AVLTree;
	template <typename T, typename Key>
	friend class AVLTreeNode;
	//friend class AVLTreeNode;
private:
	T m_data; //value
	Key const m_key; //key

public:
	AVLTreeNodeData(T const& data, Key const& key) : m_data(data),m_key(key) {}
	virtual ~AVLTreeNodeData(){}

	T* getData(){ return &m_data; }
	//void print(){ data.print(); }
};

template <typename T, typename Key = int>
class AVLTreeNode
{
	template <typename T, typename Key>
	friend class AVLTree;
private:
	AVLTreeNodeData<T, Key> m_NodeData;
	int height;
	int BF; //balacne factor
	AVLTreeNode<T, Key>* pCLeft, *pCRight;

public:
	AVLTreeNode(T const& data, Key const& key) : m_NodeData(data, key), height(1), BF(0), pCLeft(NULL), pCRight(NULL){}
	virtual ~AVLTreeNode(){}

	//void print() const { m_NodeData.m_data.print(); }
	T* getData(){return m_NodeData.getData(); }
};

template <typename T, typename Key = int>
class AVLTree
{
private:
	AVLTreeNode<T, Key> *pRoot;

public:
	AVLTree() : pRoot(NULL) {}
	virtual ~AVLTree();

	virtual AVLTreeNode<T, Key> *search(Key key) const; //search (iterative)
	AVLTreeNode<T, Key> *insert(T const& data, Key key);
	int remove(Key key);
	bool isEmpty() const { return pRoot == NULL; }

	template <typename ReferredObj>
	void traverseInOrder(FileFunctor<ReferredObj>& func) const;
	void print() const;
	
private:
	//Adjust Height and BF value
	void updateHeightAndBF(AVLTreeNode<T, Key> *pNode);
	//Adjust balance
	void rebalance(LinkedStack<AVLTreeNode<T, Key> *>& stack);

	
	AVLTreeNode<T,Key>* rotateLL(AVLTreeNode<T,Key> *pParent);
	AVLTreeNode<T,Key>* rotateLR(AVLTreeNode<T,Key> *pParent);
	AVLTreeNode<T,Key>* rotateRR(AVLTreeNode<T,Key> *pParent);
	AVLTreeNode<T,Key>* rotateRL(AVLTreeNode<T,Key> *pParent);

	void deleteInternal(AVLTreeNode<T,Key> *pNode); //delete (recursive)
	void printInternal(AVLTreeNode<T,Key> *pNode, int level, char const*const NodeType) const;

	template <typename ReferredObj>
	void traverseInOrderInternal(AVLTreeNode<T, Key> *root, FileFunctor<ReferredObj>& func) const;
};

template <typename T, typename Key = int>
AVLTree<T, Key>::~AVLTree()
{
	deleteInternal(pRoot);
}

template <typename T, typename Key = int>
void AVLTree<T, Key>::deleteInternal(AVLTreeNode<T,Key> *pNode)
{
	if (pNode != NULL)
	{
		deleteInternal(pNode->pCLeft);
		deleteInternal(pNode->pCRight);
		delete pNode;
	}
}

template <typename T, typename Key = int>
void AVLTree<T, Key>::print() const
{
	printf("-[Height BF Nodetype]- Key Val\n");
	printInternal(pRoot, 0, "Root");
}

template <typename T, typename Key = int>
void AVLTree<T, Key>::printInternal(AVLTreeNode<T, Key> *pNode, int level, char const*const NodeType) const
{
	for (int i = 0; i < level; i++)
		printf("    ");

	if (pNode != NULL)
	{
		printf("-[%d %d %s]- ", pNode->height, pNode->BF, NodeType);
		//pNode->data.print(); //key, value
		printf("\n");

		printInternal(pNode->pCLeft, level + 1, "LEFT");
		printInternal(pNode->pCRight, level + 1, "RIGHT");
	}
	else
		printf("NULL\n");
}

template <typename T, typename Key = int>
AVLTreeNode<T, Key>* AVLTree<T, Key>::search(Key key) const
{
	AVLTreeNode<T, Key>* pNode = pRoot;
	while (pNode)
	{	
		if (key < pNode->m_NodeData.m_key)
			pNode = pNode->pCLeft;
		else if (key > pNode->m_NodeData.m_key)
			pNode = pNode->pCRight;
		else
			return pNode;
	}
	return NULL;
}

template <typename T, typename Key = int>
AVLTreeNode<T, Key> *AVLTree<T, Key>::insert(T const& data, Key key)
{
	AVLTreeNode<T, Key> *pParent = NULL;
	LinkedStack<AVLTreeNode<T,Key> *> stack;
	//stack : record possibly-needs-to-reblanced node
	//from the total AVLTree's root node to inserted node's parent node

	pParent = pRoot;
	while (pParent) 
	{
		stack.push(pParent); //back-up the parent node for later re-balancing
		if (key < pParent->m_NodeData.m_key)
		{
			if (pParent->pCLeft != NULL)
				pParent = pParent->pCLeft;
			else //found suitable place to insert
				break;
		}
		else if (key > pParent->m_NodeData.m_key)
		{
			if (pParent->pCRight != NULL)
				pParent = pParent->pCRight;
			else
				break;
		}
		else
		{
			printf("Warning : AVLTree::insert() : key duplication\n");
			return NULL;
		}
	}

	AVLTreeNode<T, Key>* pNew = new AVLTreeNode<T,Key>(data,key);
	if (pParent == NULL)
		pRoot = pNew;
	else 
	{
		if (pNew->m_NodeData.m_key < pParent->m_NodeData.m_key)
			pParent->pCLeft = pNew;
		else
			pParent->pCRight = pNew;
	}

	rebalance(stack);

	return pNew;
}

template <typename T, typename Key = int>
int AVLTree<T,Key>::remove(Key key)
{
	//reblance from the total AVLTree's root node to inserted node's parent node
	AVLTreeNode<T, Key>* pParent = NULL;
	AVLTreeNode<T, Key>* pTarget = NULL;

	LinkedStack<AVLTreeNode<T, Key> *> stackMain;
	LinkedStack<AVLTreeNode<T, Key> *> stackSub;
	//stackMain, stackSub : record possibly-needs-to-reblanced node
	//stackMain <=> insert()'s stack
	//from the total AVLTree's root node to delete-target node's parent node
	//+ to-be-replaced node(successor)
	//stackSub
	//from delete-target-node's left-child node to predecessor node
	//**Order : stackSub -> stackMain(successor -> delete-target node's parent node-> ... -> root node)

	pParent = NULL;
	pTarget = pRoot;
	while (pTarget)
	{
		if (key == pTarget->m_NodeData.m_key)
			break;
		pParent = pTarget;
		stackMain.push(pParent);

		if (key < pTarget->m_NodeData.m_key)
			pTarget = pTarget->pCLeft;
		else
			pTarget = pTarget->pCRight;
	}
	if (!pTarget)
	{
		printf("Error : AVLTree::remove() : Key [%d] is not found.\n", key);
		return -1;
	}

	if (pTarget->pCLeft == NULL && pTarget->pCRight == NULL)
	{ //Degree : 0
		if (pParent)
		{
			if (pParent->pCLeft == pTarget)
				pParent->pCLeft = NULL;
			else
				pParent->pCRight = NULL;
		}
		else
			pRoot = NULL;
	}
	else if (pTarget->pCLeft != NULL && pTarget->pCRight != NULL)
	{ //Degree : 2
		AVLTreeNode<T, Key>* pPredecessor = NULL;
		AVLTreeNode<T, Key>* pSuccessor = pTarget->pCLeft;
		stackSub.push(pSuccessor);
		while (pSuccessor->pCRight)
		{
			pPredecessor = pSuccessor;

			pSuccessor = pSuccessor->pCRight;
			stackSub.push(pSuccessor);
		}
		{
			AVLTreeNode<T, Key> *pToBeReplacedNode = NULL;
			stackSub.pop(pToBeReplacedNode);
			stackMain.push(pToBeReplacedNode);
		}

		if (pPredecessor)
		{
			pPredecessor->pCRight = pSuccessor->pCLeft;
			pSuccessor->pCLeft = pTarget->pCLeft;

			stackSub.push(pPredecessor->pCRight);
		}
		pSuccessor->pCRight = pTarget->pCRight;

		if (pParent)
		{
			if (pParent->pCLeft == pTarget)
				pParent->pCLeft = pSuccessor;
			else
				pParent->pCRight = pSuccessor;
		}
		else
			pRoot = pSuccessor;
	}
	else
	{ //Degree : 1
		AVLTreeNode<T, Key>* pChild = NULL;
		if (pTarget->pCLeft)
			pChild = pTarget->pCLeft;
		else
			pChild = pTarget->pCRight;

		if (pParent)
		{
			if (pParent->pCLeft == pTarget)
				pParent->pCLeft = pChild;
			else
				pParent->pCRight = pChild;
		}
		else
			pRoot = pChild;
	}
	delete pTarget;

	rebalance(stackSub);
	rebalance(stackMain);

	return 0;
}

template <typename T, typename Key>
template <typename ReferredObj>
void AVLTree<T, Key>::traverseInOrder(FileFunctor<ReferredObj>& func) const
{
	if (pRoot)
		traverseInOrderInternal(pRoot, func);
}

template <typename T, typename Key>
template <typename ReferredObj>
void AVLTree<T, Key>::traverseInOrderInternal(AVLTreeNode<T, Key> *root, FileFunctor<ReferredObj>& func) const
{
	if (root)
	{
		traverseInOrderInternal(root->pCLeft, func);
		func.operator()<T>(*(root->getData()));
		traverseInOrderInternal(root->pCRight, func);
	}
}

template <typename T, typename Key = int>
void AVLTree<T, Key>::updateHeightAndBF(AVLTreeNode<T, Key> *pNode)
{
	if (!pNode)
		return;

	int leftHeight = 0;
	int rightHeight = 0;

	//update height
	if (pNode->pCLeft)
		leftHeight = pNode->pCLeft->height;
	if (pNode->pCRight)
		rightHeight = pNode->pCRight->height;

	pNode->height = 1 + ((leftHeight > rightHeight) ? leftHeight : rightHeight);
	pNode->BF = leftHeight - rightHeight;
}

template <typename T, typename Key = int>
void AVLTree<T, Key>::rebalance(LinkedStack<AVLTreeNode<T, Key> *>& stack)
{
	AVLTreeNode<T, Key> *pParent = NULL;
	AVLTreeNode<T, Key> *pNode = NULL;
	AVLTreeNode<T, Key> *pChild = NULL;
	AVLTreeNode<T, Key> *pNew = NULL;

	while (stack.isEmpty() == false) 
	{
		stack.pop(pNode);
		if (!pNode)
		{
			printf("Error : AVLTree::rebalance()\n");
			break;
		}
		updateHeightAndBF(pNode);

		//The node(*pNode) already satisfies the AVLTree condition
		if (pNode->BF >= -1 && pNode->BF <= 1)
			continue;

		//The node(*pNode) doesn't statisfy the AVLTree condition
		//after reblancing by rotation, the node(*pNode) is not the root node of the subtree anymore
		//So, back up the new root node of the subtree to pNew
		if (pNode->BF > 1)
		{
			pChild = pNode->pCLeft;
			if (pChild->BF > 0)
				pNew = rotateLL(pNode);
			else
				pNew = rotateLR(pNode);
		}
		else if (pNode->BF < -1)
		{
			pChild = pNode->pCRight;
			if (pChild->BF < 0)
				pNew = rotateRR(pNode);
			else
				pNew = rotateRL(pNode);
		}

		//Finally reset the parent(pNode's previous parent node)'s link
		//to the new root node (*pNew) of the subtree
		//if the parent(pNode's previous parent node) is NULL, pNode was previously
		//the root node of the total AVLTree.
		//In this case, set the new root node (*pNew) as the new root node the total AVLTree.
		stack.peek(pParent);
		if (pParent)
		{
			if (pParent->pCLeft == pNode)
				pParent->pCLeft = pNew;
			else
				pParent->pCRight = pNew;
		}
		else
			pRoot = pNew;
	}
}

template <typename T, typename Key = int>
AVLTreeNode<T, Key>* AVLTree<T, Key>::rotateLL(AVLTreeNode<T, Key> *pParent)
{
	if (!pParent)
		return NULL;

	AVLTreeNode<T, Key> *pCLeft  = pParent->pCLeft;
	pParent->pCLeft = pCLeft->pCRight;
	pCLeft->pCRight = pParent;

	updateHeightAndBF(pParent);
	updateHeightAndBF(pCLeft);
	return pCLeft; //pCLeft becomes the new root node of the subtree
}

template <typename T, typename Key = int>
AVLTreeNode<T, Key>* AVLTree<T, Key>::rotateRR(AVLTreeNode<T, Key> *pParent)
{
	if (!pParent)
		return NULL;

	AVLTreeNode<T, Key> *pCRight = pParent->pCRight;
	pParent->pCRight = pCRight->pCLeft;
	pCRight->pCLeft = pParent;

	updateHeightAndBF(pParent);
	updateHeightAndBF(pCRight);

	return pCRight; //pCRight becomes the new root node of the subtree
}

template <typename T, typename Key = int>
AVLTreeNode<T, Key>* AVLTree<T, Key>::rotateLR(AVLTreeNode<T, Key> *pParent)
{
	if (!pParent)
		return NULL;

	AVLTreeNode<T, Key> *pReturn = NULL;
	AVLTreeNode<T, Key> *pCLeft = pParent->pCLeft;
	pParent->pCLeft = rotateRR(pCLeft);
	pReturn = rotateLL(pParent);

	return pReturn;
}

template <typename T, typename Key = int>
AVLTreeNode<T, Key>* AVLTree<T, Key>::rotateRL(AVLTreeNode<T, Key> *pParent)
{
	if (!pParent)
		return NULL;

	AVLTreeNode<T, Key> *pReturn = NULL;
	AVLTreeNode<T, Key> *pRightNode = pParent->pCRight;
	pParent->pCRight = rotateLL(pRightNode);
	pReturn = rotateRR(pParent);

	return pReturn;
}

#endif