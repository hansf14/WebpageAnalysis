#ifndef STRING_LINKED_LIST_H
#define STRING_LINKED_LIST_H

#include "String.h"
#include "LinkedList.h"

#pragma warning (disable:4309)

//front declare

template <typename Key, typename HeaderData>
class StringLinkedList;


template <typename Key = int>
class StringLinkedListNode : public LinkedListNode<String, Key>
{
	template <typename Key, typename HeaderData>
	friend class StringLinkedList;
public:
	StringLinkedListNode(String const& string, Key const& key){ printf("Called\n"); }
	virtual ~StringLinkedListNode(){}
	void print(){ m_data->print(); printf("\n");}
};


template <typename Key = int, typename HeaderData = int>
class StringLinkedList : public LinkedList<String, Key, HeaderData>
{
public:
	StringLinkedList(){}
	virtual ~StringLinkedList(){}

	int writeFile(String const& filename) const;
	int writeFile(String const& filename, char delim) const;
};


template <typename Key, typename HeaderData>
int StringLinkedList<Key, HeaderData>::writeFile(String const& filename) const
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

	//write txt in UTF-8
	char typeUTF8[] = { 0xEF, 0xBB, 0xBF };
	fout.write(typeUTF8, 3);

	LinkedListNode<String, Key> *pNode = reinterpret_cast<LinkedListNode<String, Key> *>(this->head); //the list isn't empty (head != NULL)
	//StringLinkedListNode<Key> *pNode = reinterpret_cast<StringLinkedListNode<Key> *>(this->head); //the list isn't empty (head != NULL)
	String const* pCurrStr = pNode->m_data;
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
		//pNode = reinterpret_cast<StringLinkedListNode<Key> *>(pNode->next);
		pNode = pNode->next;
		if (pNode)
			pCurrStr = pNode->m_data;
	}

	fout.close();

	return 0;
}

template <typename Key, typename HeaderData>
int StringLinkedList<Key, HeaderData>::writeFile(String const& filename, char delim) const
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

	//write txt in UTF-8
	char const typeUTF8[] = { 0xEF, 0xBB, 0xBF };
	fout.write(typeUTF8, 3);

	LinkedListNode<String, Key> *pNode = reinterpret_cast<LinkedListNode<String,Key> *>(this->head); //the list isn't empty (head != NULL)
	//StringLinkedListNode<Key> *pNode = reinterpret_cast<StringLinkedListNode<Key> *>(this->head); //the list isn't empty (head != NULL)
	String const* pCurrStr = pNode->m_data;
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
		//pNode = reinterpret_cast<StringLinkedListNode<Key> *>(pNode->next);
		//fout << delim;
		fout.put(delim);
		pNode = pNode->next;
		if (pNode)
			pCurrStr = pNode->m_data;
	}

	fout.close();

	return 0;
}

#endif