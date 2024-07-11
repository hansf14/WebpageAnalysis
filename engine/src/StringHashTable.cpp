#include "StringHashTable.h"

////////////////////////////////////////////////////////////
//StringHashCode

StringHashCode::StringHashCode(StringHashCode const& other)
{
	memcpy(this, &other, sizeof(StringHashCode));
}

StringHashCode::StringHashCode(String const& srcString)
{
	CharHash1 = (short(srcString[1] & 0x0F) << 12) +
		(short(srcString[2] & 0x3F) << 6) +
		(srcString[3] & 0x3F);

	CharHash2 = (short(srcString[4] & 0x0F) << 12) +
		(short(srcString[5] & 0x3F) << 6) +
		(srcString[6] & 0x3F);
}

////////////////////////////////////////////////////////////
//StringHashTable

StringHashTable::StringHashTable()
{
	pMainBucket = new StringHashMainBucket[INITIAL_STRING_BUCKET_SIZE];
	nMaxBuckets = INITIAL_STRING_BUCKET_SIZE;
	nCurBuckets = 0;
	nCurStringTotal = 0;
}

StringHashTable::StringHashTable(int const numBuckets)
{
	pMainBucket = new StringHashMainBucket[numBuckets];
	nMaxBuckets = numBuckets;
	nCurBuckets = 0;
	nCurStringTotal = 0;
}

//SubBucketTree <- insert(copy occur) SubBucket
//LinkedList<LinkedList<StringBasicInfo>> <- insert(copy occur) LinkedList<StringBasicInfo> 
//LinkedList<StringBasicInfo> <- insert(copy occur) StringBasicInfo
//
//SubBucketTree : its' node key : CharHash2
//LinkedList<LinkedList<StringBasicInfo>> : its' node Key : StringLen
//LinkedList<StringBasicInfo> : its' node Key : nCurStringTotal + 1
//StringBasicInfo : the data Key(ID) : nCurStringTotal + 1
int StringHashTable::add(String const& newString)
{
	int ID = -1;
	if (isValidKeyString(newString) == false)
	{
		printf("Invalid Keyword\n");
		return ID;
	}
	
	//Convert hash to index
	StringHashCode newHashCode(newString);
	int idx = (newHashCode.CharHash1 & 0xFFFF) - 0x4E00;
	while (idx >= nMaxBuckets)
	{
		//printf("Expanded for index : %d\n",idx);
		expand();
	}

	//Check MainBucket
	if (pMainBucket[idx].isEmpty() == true)
	{
		//MainBucket is empty : SubBucketTree : NULL
		//MainBucket
		pMainBucket[idx].setHashCode(newHashCode.CharHash1);
		pMainBucket[idx].m_pSubBucketTree = new AVLTree<StringHashSubBucket>();
		//asssert pMainBucket[idx].m_pSubBucketTree != NULL

		//SubBucket
		//SubBucket ID : CharHash2
		StringHashSubBucket SubBucket;
		SubBucket.setHashCode(newHashCode.CharHash2);
		SubBucket.m_pLenListList = new LinkedList<LinkedList<StringBasicInfo>>();
		//asssert pMainBucket[idx].m_pLenListList != NULL

		//Insert
		AVLTreeNode<StringHashSubBucket> *pSubBucketNode = pMainBucket[idx].m_pSubBucketTree->insert(SubBucket, newHashCode.CharHash2);; //<- Shallow copy occur!!!!
		SubBucket.m_pLenListList = NULL; //because of shallow copy, need to prevent double dealloc (Temporary solution)
		if (!pSubBucketNode)
		{ //Fail
			printf("Error : StringHashTable::add() : Cannot insert node in SubBucketTree\n");
			/*delete pMainBucket[idx].m_pSubBucketTree;
			pMainBucket[idx].m_pSubBucketTree = NULL;
			delete SubBucket.m_pLenListList;*/
			return ID;
		}
		else
		{ //Success
			LinkedList<StringBasicInfo>* pLenList = new LinkedList<StringBasicInfo>();
			ID = nCurStringTotal + 1;
			pLenList->append(StringBasicInfo(newString, ID), ID);

			StringHashSubBucket *pSubBucket = pSubBucketNode->getData();
			int stringLen = newString.getTotalLength();
			pSubBucket->m_pLenListList->appendList(pLenList, stringLen);

			nCurBuckets++;
		}
	}
	else
	{
		//MainBucket is not empty : SubBucketTree : !NULL
		//Check SubBucket
		AVLTreeNode<StringHashSubBucket> *pSubBucketNode = pMainBucket[idx].m_pSubBucketTree->search(newHashCode.CharHash2);
		if (!pSubBucketNode)
		{
			//SubBucket with the CharHash2 not exist -> create & insert & append
			StringHashSubBucket SubBucket;
			SubBucket.setHashCode(newHashCode.CharHash2);
			SubBucket.m_pLenListList = new LinkedList<LinkedList<StringBasicInfo>>();

			//Insert
			pSubBucketNode = pMainBucket[idx].m_pSubBucketTree->insert(SubBucket, newHashCode.CharHash2); //<- Shallow copy occur!!!!
			SubBucket.m_pLenListList = NULL; //because of shallow copy, need to prevent double dealloc (Temporary solution)
			if (!pSubBucketNode)
			{ //Fail
				printf("Error : StringHashTable::add() : Cannot insert node in SubBucketTree\n");
				/*delete pMainBucket[idx].m_pSubBucketTree;
				pMainBucket[idx].m_pSubBucketTree = NULL;
				delete SubBucket.m_pLenListList;*/
				return ID;
			}
			else
			{ //Success
				LinkedList<StringBasicInfo>* pLenList = new LinkedList<StringBasicInfo>();
				ID = nCurStringTotal + 1;
				pLenList->append(StringBasicInfo(newString, ID), ID);

				StringHashSubBucket *pSubBucket = pSubBucketNode->getData();
				int stringLen = newString.getTotalLength();
				pSubBucket->m_pLenListList->appendList(pLenList, stringLen);
			}
		}
		else
		{
			//SubBucket with the CharHash2 already exist -> just insert
			//assert pSubBucketNode->getData() : pSubBucket != NULL
			//assert pSubBucket->m_pLenListList != NULL
			
			LinkedList<LinkedList<StringBasicInfo>> *pLenListList = pSubBucketNode->getData()->m_pLenListList;
			LinkedListNode<LinkedList<StringBasicInfo>> *pLenListListNode = pLenListList->search(newString.getTotalLength());
			if (!pLenListListNode)
			{
				//List that stores (StringLen == newString's len) not exist
				LinkedList<StringBasicInfo>* pLenList = new LinkedList<StringBasicInfo>();
				ID = nCurStringTotal + 1;
				pLenList->append(StringBasicInfo(newString, ID), ID);

				StringHashSubBucket *pSubBucket = pSubBucketNode->getData();
				int stringLen = newString.getTotalLength();
				pSubBucket->m_pLenListList->appendList(pLenList, stringLen);

			}
			else
			{
				//List that stores (StringLen == newString's len) already exist
				LinkedList<StringBasicInfo>* pLenList = pLenListListNode->getNodeData();
				ID = nCurStringTotal + 1;
				pLenList->append(StringBasicInfo(newString, ID), ID);
			}
		}
	}
	nCurStringTotal++;

	return ID;
}

void StringHashTable::expand()
{
	//because there's no supported "realloc" for "new"ed obejcts
	int nNewMaxBuckets = 2 * (this->nMaxBuckets);
	StringHashMainBucket *pNewBucket = new StringHashMainBucket[nNewMaxBuckets]; //relocated
	memcpy(pNewBucket, this->pMainBucket, (this->nMaxBuckets)*sizeof(StringHashMainBucket));
	//delete[] pMainBucket;
	this->pMainBucket = pNewBucket;
	this->nMaxBuckets = nNewMaxBuckets;
}

AVLTree<StringHashSubBucket>* StringHashTable::doesFirstStrCharMatch(String const& firstChineseChar) const
{
	//Check if the first character is qualified to be hashed (qualified to be keyword)
	if (isValidKeyStringChar(firstChineseChar) == false)
		return NULL;

	//Check if it's invalid HashCode
	StringHashCode keyHashCode(firstChineseChar);
	int idx = (keyHashCode.CharHash1 & 0xFFFF) - 0x4E00;
	if (idx < 0 || idx >= nMaxBuckets)
		return NULL;

	//Check MainBucket
	if (pMainBucket[idx].isEmpty())
		return NULL;
	else
		return pMainBucket[idx].m_pSubBucketTree;
}

LinkedList<LinkedList<StringBasicInfo>>* StringHashTable::doesSecondStrCharMatch
(String const& keyString, AVLTree<StringHashSubBucket>* subBucketTree) const
{
	if (isValidKeyString(keyString) == false)
		return NULL;
	//assert the first character hash match check already passed

	//Check SubBucket
	StringHashCode keyHashCode(keyString);
	AVLTreeNode<StringHashSubBucket> *pSubBucketNode =
		subBucketTree->search(keyHashCode.CharHash2);
	if (!pSubBucketNode)
		return NULL;
	else
	{
		StringHashSubBucket *pSubBucket = pSubBucketNode->getData();
		if (pSubBucket->isEmpty())
		{//Error (something is wrong. not qualifies the logic mechanism)
			printf("Error : StringHashTable::search() : pSubBucket == NULL\n");
			return NULL;
		}
		else
			return pSubBucket->m_pLenListList;
	}
}

bool StringHashTable::search(String const& keyString) const
{
	////Check if the first two characters are qualified to be hashed (qualified to be keyword)
	//if (isValidKeyString(keyString) == false)
	//	return false;

	////Check if it's invalid HashCode
	//StringHashCode keyHashCode(keyString);
	//int idx = (keyHashCode.CharHash1 & 0xFFFF) - 0x4E00;
	//if (idx < 0 || idx >= nMaxBuckets)
	//	return false;

	////Check MainBucket
	//if (this->pMainBucket[idx].isEmpty())
	//	return false;

	////Check SubBucket
	//AVLTreeNode<StringHashSubBucket> *pSubBucketNode = 
	//	pMainBucket[idx].m_pSubBucketTree->search(keyHashCode.CharHash2);
	//if (!pSubBucketNode)
	//	return false;
	//else
	//{
	//	StringHashSubBucket *pSubBucket = pSubBucketNode->getData();
	//	if (pSubBucket->isEmpty())
	//	{//Error (something is wrong. not qualifies the logic mechanism)
	//		printf("Error : StringHashTable::search() : pSubBucket == NULL\n");
	//		return false;
	//	}
	//	else
	//	{
	//		//Check Length
	//		int stringLen = keyString.getTotalLength();
	//		LinkedListNode<LinkedList<StringBasicInfo>>* pLenListListNode =
	//			pSubBucket->m_pLenListList->search(stringLen);
	//		if (!pLenListListNode)
	//			return false;
	//		else
	//		{
	//			//Check string
	//			LinkedList<StringBasicInfo>* pLenList = pLenListListNode->getNodeData();
	//			if (!pLenList)
	//			{//Error (something is wrong. not qualifies the logic mechanism)
	//				printf("Error : StringHashTable::search() : pLenList == NULL\n");
	//				return false;
	//			}
	//			else
	//			{
	//				/*LinkedListIter<StringBasicInfo> iter(pLenList);
	//				while (iter.isValid())
	//				{
	//					if (iter.getNodeData()->m_string == keyString)
	//						return true;
	//					iter.next();
	//				}*/
	//			}
	//		}
	//	}
	//}
	
	return false;
}

bool StringHashTable::isValidKeyString(String const& string) const
{
	//All the keywords in the StringHashTable has 0xEA code
	//Check if the certain string has this code
	//(Check if it's qualified string keyword)

	typedef unsigned char BYTE;
	BYTE QualificationCode = 0xEA; //EA(1110 1010)
	
	BYTE firstCode = (BYTE(string[1] & 0xF0)) +
		(BYTE(string[2] & 0xC0) >> 4) +
		(BYTE(string[3] & 0xC0) >> 6);
	BYTE secondCode = (BYTE(string[4] & 0xF0)) +
		(BYTE(string[5] & 0xC0) >> 4) +
		(BYTE(string[6] & 0xC0) >> 6);

	if (firstCode != QualificationCode ||
		secondCode != QualificationCode)
		return false;
	else
		return true;
}

bool StringHashTable::isValidKeyStringChar(String const& stringChar) const
{
	typedef unsigned char BYTE;
	BYTE QualificationCode = 0xEA; //EA(1110 1010)
	
	BYTE firstCode = (BYTE(stringChar[1] & 0xF0)) +
		(BYTE(stringChar[2] & 0xC0) >> 4) +
		(BYTE(stringChar[3] & 0xC0) >> 6);

	if (firstCode != QualificationCode)
		return false;
	else
		return true;
}