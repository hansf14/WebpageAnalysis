#ifndef LINKEDSTACK_H
#define LINKEDSTACK_H

#include "Element.h"


//front declaration
template <typename T>
class LinkedStack;

//LinkedStackNode Class
//Node for LinkedStack Class
template <typename T>
class LinkedStackNode
{
	friend class LinkedStack<T>;
private:
	//Element<T> element;
	Element<T> element;
	LinkedStackNode<T> *link;

public:
	LinkedStackNode() :element(), link(NULL){}
	~LinkedStackNode(){}

	void setData(T const& srcData){ element.data = srcData; }
	T const& getData() const { return element.data; }
};

template <typename T>
class LinkedStack
{
protected:
	LinkedStackNode<T> *top;
	int nCurNodeCnt;

public:
	//creator
	LinkedStack() :top(NULL), nCurNodeCnt(0){}

	//destructor
	~LinkedStack();

	//member functions
	bool isEmpty() const { return (top == NULL); }
	int getCurNodeCnt() const { return nCurNodeCnt; }

	int push(T const& srcData);
	int pop(T& outData);
	int pop();
	int peek(T& outData) const;
};

template <typename T>
LinkedStack<T>::~LinkedStack()
{
	while (top)
		this->pop();
}

template <typename T>
int LinkedStack<T>::push(T const& srcData)
{
	LinkedStackNode<T> *newNode = new LinkedStackNode<T>();
	if (!newNode)
		return -1;
	newNode->setData(srcData);
	newNode->link = top;
	top = newNode;
	nCurNodeCnt++;
	return 0;
}

template <typename T>
int LinkedStack<T>::pop(T& outData)
{
	if (isEmpty())
		return -1;
	LinkedStackNode<T> *targetNode = top;
	outData = top->element.data;
	top = top->link;
	targetNode->link = NULL;
	delete targetNode;
	nCurNodeCnt--;
	return 0;
}

template <typename T>
int LinkedStack<T>::pop()
{
	if (isEmpty())
		return -1;
	LinkedStackNode<T> *targetNode = top;
	top = top->link;
	targetNode->link = NULL;
	delete targetNode;
	nCurNodeCnt--;
	return 0;
}

template <typename T>
int LinkedStack<T>::peek(T& outData) const
{
	if (isEmpty())
		return -1;
	outData = top->element.data;
	return 0;
}

#endif