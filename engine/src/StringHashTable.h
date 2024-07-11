#ifndef STRING_HASH_TABLE_H
#define STRING_HASH_TABLE_H

#include "String.h"
#include "LinkedList.h"
#include "AVLTree.h"

//TODO : Memory deallocation
//Too much complicated because of possible pointer shallow copy..(memory dealloc duplication)
//Need smart pointer!!!!
//Temporarily had to let StringHashTable do all this process at once

//Each Chinese character occupies 3 bytes in UTF-8
//and each code is made of following structure : 1110 xxxx | 10xx xxxx | 10xx xxxx
//So, for every chinese character in UTF-8, can be expressed perfectly unique in 2 bytes
//Moreover, Simplified Chinese is from E4B880 ~ E9BEBB (20924 in total)
//(4 + 6 + 6) bits -> 16 bits -> 2 bytes
//cf>
//http://baike.baidu.com/link?url=ie2YItYzEkdPY2WTwts0NGt4N-TjSiw_HTVCOkshSLKVzO3DlIh3XJZjEsF3YCUAQOpaVk7nKtX7aVevHNos0_
//http://blog.csdn.net/qiaqia609/article/details/8069678
//https://zhidao.baidu.com/question/1047887004693001899.html

#define CHINESE_CHARACTER_LEN 3

///////////////////////////////////////////////////////
//front declare
class StringHashMainBucket;
class StringBasicInfo;
class StringHashSubBucket;
class StringHashTable;

template <typename T>
class FileFunctor;

///////////////////////////////////////////////////////

typedef short int StringCharHashCode;

#pragma pack(push,1)
class StringHashCode
{
	friend class StringHashTable;
public:
	//Assumption : the string is made of only and at least 2 or more chinese characters
	StringCharHashCode CharHash1,CharHash2;

public:
	StringHashCode(StringHashCode const& other);
	StringHashCode(String const& srcString);

	//explicit operator int() const;
	//bool operator==(StringHashCode const& other) const;
	//bool operator!=(StringHashCode const& other) const;
};
#pragma pack(pop)

//#pragma pack(push,1)
//class QualificationCode
//{
//	friend class StringHashTable;
//public:
//	//Assumption : the string is made of only and at least 2 or more chinese characters
//	StringCharHashCode CharHash1, CharHash2;
//
//public:
//	StringHashCode(StringHashCode const& other);
//	StringHashCode(String const& srcString);
//
//	//explicit operator int() const;
//	//bool operator==(StringHashCode const& other) const;
//	//bool operator!=(StringHashCode const& other) const;
//};
//#pragma pack(pop)


class StringHashMainBucket
{
	friend class StringHashTable;
	template <typename T>
	friend class FileFunctor;
	//friend class FileFunctor<StringHashTable>;

private:
	//Data field
	StringCharHashCode m_firstCharHash;

	//Link field (to prevent collision)
	AVLTree<StringHashSubBucket> *m_pSubBucketTree;

private:
	StringHashMainBucket() : m_firstCharHash(0), m_pSubBucketTree(NULL) {}
public:
	//StringHashTable does deallocation of the Tree instead
	virtual ~StringHashMainBucket(){ delete m_pSubBucketTree; }

private:
	bool isEmpty(){ return m_pSubBucketTree == NULL; }
	void setHashCode(StringCharHashCode firstCharHash){ m_firstCharHash = firstCharHash; }
};

class StringBasicInfo
{
public:
	String m_string;
	int m_ID;

public:
	StringBasicInfo(String const& string, int ID) : m_string(string), m_ID(ID){}
	~StringBasicInfo(){}

public:
	void print()
	{
		printf("["); m_string.print(); printf("]");
		printf("[ID : %d]\n",m_ID);
	}
};

class StringHashSubBucket
{
	friend class StringHashTable;
	template <typename T>
	friend class FileFunctor;

private:
	StringCharHashCode m_secondCharHash;
	LinkedList<LinkedList<StringBasicInfo>>* m_pLenListList;

private:
	StringHashSubBucket() : m_secondCharHash(0), m_pLenListList(NULL){}
public:
	virtual ~StringHashSubBucket()
	{
		if (!m_pLenListList)
			return;
		
		typedef LinkedList<StringBasicInfo> LenList;
		typedef LinkedList<LenList> LenListList;
		typedef LinkedListNode<LenList> LenListListNode;

		LinkedListIter<LenList> iter(m_pLenListList);
		while (iter.isValid())
		{
			LenListListNode* pListNode = iter.curr();
			LenList* pList = pListNode->getNodeData();
			
			iter.next();
			delete pList;
		}
		m_pLenListList->setHead(NULL);
		m_pLenListList->setTail(NULL);
		delete m_pLenListList;
	}

private:
	bool isEmpty() const { return m_pLenListList == NULL; }
	void setHashCode(StringCharHashCode secondCharHash){ m_secondCharHash = secondCharHash; }
};


#define INITIAL_STRING_BUCKET_SIZE 7000

class StringHashTable
{
	template <typename T>
	friend class FileFunctor;

	StringHashMainBucket *pMainBucket;
public:
	int nMaxBuckets; //count total number of buckets created
	int nCurBuckets; //count number of currently being used buckets
	int nCurStringTotal; //count total number of strings stored

public:
	StringHashTable();
	StringHashTable(int const numBuckets);
	~StringHashTable(){ delete[] pMainBucket; }

	int add(String const& newString);
	bool search(String const& keyString) const;
	//bool search(String const& keyString) const;
	AVLTree<StringHashSubBucket>* doesFirstStrCharMatch(String const& firstChineseChar) const;
	LinkedList<LinkedList<StringBasicInfo>>* doesSecondStrCharMatch
		(String const& keyString, AVLTree<StringHashSubBucket>* subBucketTree) const;
	
private:
	bool isValidKeyString(String const& string) const;
	bool isValidKeyStringChar(String const& stringChar) const;
	void expand();
};

#endif