#ifndef MAIN_MODULE_H
#define MAIN_MODULE_H

#include <iostream>

#include "StringHashTable.h"
#include "KeywordAVLTree.h"
#include "StringLinkedList.h"
#include "DocLinkedList.h"

#include "FileFunctor.h"


#pragma warning (disable:4309)
#pragma warning (disable:4996)

////////////////////////////////////////////////////////////////////////
//initDictionary

//init (chinese) dictionary
//Uses HashTable for more oragnized and faster search of strings
//and the HashTable uses StringLinkedLists internally (only when occurs collision in buckets)
//cf> independent usage of StringLinkedList is also no prob (but in terms of search, it's too slow)
//dstStringHashTable : to store word list
//dicFileName (.dic) : chineseDicFileName
extern int initDictionary(String const& dicFileName,
	StringHashTable& dstKeywordHashTable, KeywordAVLTree<int>& dstKeywordTree);

extern int initDictionary(String const& dicFileName, StringHashTable& dstKeywordHashTable);

////////////////////////////////////////////////////////////////////////
//extractInfo

//extract html info
//srcFileName (.html) : sourceHTMLFileName
//dstFileName (.info) : parsedHTMLFileName
extern int extractInfo(String const& srcFileName, String const& dstFileName);

////////////////////////////////////////////////////////////////////////
//divideWords

//No duplication of keyword.. just increase the count internally
//srcFileName (.info) : parsedHTMLFileName
//dstFileName (.txt) : dividedWordsFileName
extern int divideWords(String const& srcFileName, String const& dstFileName,
	StringHashTable const& srcKeywordgHashTable, KeywordAVLTree<int>& srcKeywordTree, Doc<int>& doc);

extern int divideWords(String const& srcFileName, String const& dstFileName,
	StringHashTable const& srcKeywordgHashTable);

////////////////////////////////////////////////////////////////////////
//initModule (Wrapper function)

extern int extractKeywords(StringHashTable& KeywordHashTable, KeywordAVLTree<int>& KeywordTree);
extern int extractKeywordsFast(StringHashTable& KeywordHashTable);

#endif