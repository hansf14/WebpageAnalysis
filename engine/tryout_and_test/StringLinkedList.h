#ifndef STRINGLINKEDLIST_H
#define STRINGLINKEDLIST_H

#include "String.h"


class StringLinkedListNode
{
	friend class StringLinkedList;
public:
	String str;
protected:
	StringLinkedListNode *next;
	//StringLinkedListNode *prev;

public:
	StringLinkedListNode() :str(), next(NULL) {} //,prev(NULL){}
	explicit StringLinkedListNode(String const& srcString) : str(srcString), next(NULL){}//, prev(NULL){}
	~StringLinkedListNode(){}
	void print(){ str.print(); printf(" "); }

};


class StringLinkedList
{
protected:
	//Data field
	int size; //count the nodes

	//Link field
	//StringLinkedListNode headerNode;
	StringLinkedListNode* head;
	StringLinkedListNode* tail;

public:
	StringLinkedList() : head(NULL), tail(NULL), size(0){}
	~StringLinkedList();

	bool isEmpty() const { return(head == NULL); };
	int getSize() const { return size; }

	void append(String const& srcString); //add at last
	int remove(String const& keyString); //TODO //return remove result in int value
	int remove(StringLinkedListNode*& pTargetNode); //if successful, assign pTargetNode to NULL
	
	StringLinkedListNode* search(String const& keyString) const;
	void print() const;

	//void removeAll(const String srcString); //TODO
	//StringLinkedListNode* searchAll(const String srcString); //TODO

	int writeFile(String const& filename) const;
	int writeFile(String const& filename, char delim) const;

};

#endif