#include "StringLinkedList.h"


void StringLinkedList::print() const
{
	StringLinkedListNode *pTargetNode = head;
	while (pTargetNode)
	{
		pTargetNode->print();
		pTargetNode = pTargetNode->next;
	}
}

StringLinkedList::~StringLinkedList()
{
	StringLinkedListNode *pNextNode = NULL;
	while (head)
	{
		pNextNode = head->next;
		delete head;
		head = pNextNode;
	}
}

void StringLinkedList::append(String const& srcString)
{
	StringLinkedListNode *pNewNode = NULL;
	if (!head) //empty list
	{
		pNewNode = new StringLinkedListNode(srcString);
		head = pNewNode;
		tail = pNewNode;
		return;
	}
	pNewNode = new StringLinkedListNode(srcString);
	tail->next = pNewNode;
	tail = pNewNode;

	size++;
}

int StringLinkedList::remove(StringLinkedListNode*& pTargetNode)
{
	if (!pTargetNode)
		return -1;

	if (pTargetNode == head)
	{
		delete pTargetNode;
		head = NULL;
		tail = NULL;
		return 0;
	}
	StringLinkedListNode *pPrev = head;
	while (pPrev->next && (pPrev->next != pTargetNode))
		pPrev = pPrev->next;
	pPrev->next = pTargetNode->next;
	if (pTargetNode == tail)
		tail = pPrev;
	delete pTargetNode;

	size--;
	return 0;
}

StringLinkedListNode* StringLinkedList::search(String const& keyString) const
{
	StringLinkedListNode *pTargetNode = head;
	while (pTargetNode)
	{
		if (pTargetNode->str == keyString)
			return pTargetNode;
		pTargetNode = pTargetNode->next;
	}
	return NULL;
}

//void removeAll(const String srcString)
//{
//
//}


//StringLinkedListNode* searchAll(const String srcString)
//{
//
//}

int StringLinkedList::writeFile(String const& filename) const
{
	if (this->isEmpty())
		return 0;

	std::locale china("chs");
	std::ofstream fout;
	fout.imbue(china);

	int lenFileName = filename.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name is too long\n");
		return -1;
	}
	
	//delete previous file
	std::remove(filename.peekStringToCharPointer());
	//std::ios::app support bigger data writing/reading than std::ios::trunc
	fout.open(filename.peekStringToCharPointer(), std::ios::out | std::ios::app);
	if (!fout.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	StringLinkedListNode *pNode = this->head; //the list isn't empty (head != NULL)
	String const* pCurrStr = &pNode->str;
	String const* pNextStr = pCurrStr;
	char *p = NULL;
	while (pNode)
	{
		while (pCurrStr)
		{
			p = pCurrStr->peekStringToCharPointer(pNextStr);
			fout.write(p, pCurrStr->getStringChunkLength());
			pCurrStr = pNextStr;
		}
		pNode = pNode->next;
		if (pNode)
			pCurrStr = &pNode->str;
	}

	fout.close();

	return 0;
}

int StringLinkedList::writeFile(String const& filename, char delim) const
{
	if (this->isEmpty())
		return 0;

	std::locale china("chs");
	std::ofstream fout;
	fout.imbue(china);

	int lenFileName = filename.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name is too long\n");
		return -1;
	}

	//delete previous file
	std::remove(filename.peekStringToCharPointer());
	//std::ios::app support bigger data writing/reading than std::ios::trunc
	fout.open(filename.peekStringToCharPointer(), std::ios::out | std::ios::app);
	if (!fout.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	StringLinkedListNode *pNode = this->head; //the list isn't empty (head != NULL)
	String const* pCurrStr = &pNode->str;
	String const* pNextStr = pCurrStr;
	char *p = NULL;
	while (pNode)
	{
		while (pCurrStr)
		{
			p = pCurrStr->peekStringToCharPointer(pNextStr);
			fout.write(p, pCurrStr->getStringChunkLength());
			pCurrStr = pNextStr;
		}
		fout.put(delim);
		pNode = pNode->next;
		if (pNode)
			pCurrStr = &pNode->str;
	}

	fout.close();

	return 0;
}