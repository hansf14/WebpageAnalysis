#include "FileFunctor.h"


////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//template explicit specializations
////////////////////////////////////////////////////////////////////////
//write function variations
//StringHashTable

template <>
int FileFunctor<StringHashTable>::write()
{
	//CurReferredObj : StringHashTable
	//Need backup pointer to restore reference
	//because not like other write function, this function does interation instead
	StringHashTable const* pRefBackup = m_pReferredHashTable;
	for (int i = 0; i < m_pReferredHashTable->nMaxBuckets; i++)
	{
		if (m_pReferredHashTable->pMainBucket[i].isEmpty())
			continue;

		//CurReferredObj at least may change to StringSubBucket
		//CurReferredObj at most may change to StringBasicInfo
		m_pReferredHashTable->pMainBucket[i].m_pSubBucketTree->traverseInOrder(*this);
		//CurReferredObj restore
		m_pReferredHashTable = pRefBackup;
	}
	return 0;
}

template<>
template<>
int FileFunctor<StringHashTable>::write<StringHashSubBucket>()
{
	StringHashSubBucket const* RefBackup = m_pReferredSubBucket;
	if (m_pReferredSubBucket->isEmpty())
		return 0;
	//Because SubBucket is not empty, ListList must not be empty
	//CurReferredObj at least may change to LinkedList<StringBasicInfo>
	//CurReferredObj at most may change to StringBasicInfo
	m_pReferredSubBucket->m_pLenListList->traverse(*this);
	return 0;
}

template<>
template<>
int FileFunctor<StringHashTable>::write<LinkedList<StringBasicInfo>>()
{
	//printf("Called\n");
	if (m_pReferredList->isEmpty())
		return 0;
	//CurReferredObj may change to StringBasicInfo
	m_pReferredList->traverse(*this);
	m_fout << std::endl;
	return 0;
}

template<>
template<>
int FileFunctor<StringHashTable>::write<StringBasicInfo>()
{
	char *pAddr = m_pReferredStringInfo->m_string.peekStringToCharPointer();
	int len = m_pReferredStringInfo->m_string.getTotalLength();
	m_fout.write(pAddr, len);
	m_fout << " ";
	return 0;
}

/////////////////////////////////////////////////////////////////////////////////////
//KeywordAVLTree
//TODO : partial (not complete) specialization (int->Key)

template <>
int FileFunctor<KeywordAVLTree<int>>::write()
{
	if (m_pReferredKeywordTree->isEmpty())
		return 0;
	m_pReferredKeywordTree->traverseInOrder(*this);
	return 0;
}

template <>
template <>
int FileFunctor<KeywordAVLTree<int>>::write<Keyword<int>>()
{
	char *pAddr = m_pReferredKeyword->m_string.peekStringToCharPointer();
	int len = m_pReferredKeyword->m_string.getTotalLength();
	m_fout.write(pAddr, len);
	m_fout << " ";
	return 0;
}

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
//template explicit instantiation
////////////////////////////////////////////////////////////////////////
//StringHashTable
template
int FileFunctor<StringHashTable>::write();

template
int FileFunctor<StringHashTable>::write<StringHashSubBucket>();

template
int FileFunctor<StringHashTable>::write();

template
int FileFunctor<StringHashTable>::write<StringBasicInfo>();

////////////////////////////////////////////////////////////////////////
//KewordAVLTree<int>

template
int FileFunctor<KeywordAVLTree<int>>::write();

template
int FileFunctor<KeywordAVLTree<int>>::write<Keyword<int>>();

////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////