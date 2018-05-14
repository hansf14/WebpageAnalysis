#include "LinkedStack.h"

//template <typename T>
//LinkedStack<T>::~LinkedStack()
//{
//	while (top)
//		this->pop();
//}
//
//template <typename T>
//int LinkedStack<T>::push(Element<T> const& srcElement)
//{
//	LinkedStackNode<T> *newNode = new LinkedStackNode();
//	if (!newNode)
//		return -1;
//	newNode->setElement(srcElement);
//	newNode->link = top;
//	top = newNode;
//	size++;
//	return 0;
//}
//
//template <typename T>
//Element<T> const LinkedStack<T>::pop()
//{
//	//if (isEmpty()) //TODO : EXCEPTION
//	//{
//	//	return E;
//	//}
//	LinkedStackNode<T> *targetNode = top;
//	Element<T> outputElement = targetNode->element;
//	top = top->link;
//	targetNode->link = NULL;
//	delete targetNode;
//	size--;
//	return outputElement;
//}
//
//template <typename T>
//Element<T> const& LinkedStack<T>::peek() const
//{
//	//if (isEmpty()) //TODO : EXCEPTION
//	//{
//	//	return E;
//	//}
//	return (top->element);
//}