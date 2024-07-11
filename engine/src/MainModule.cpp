#include "MainModule.h"

////////////////////////////////////////////////////////////////////////
//initDictionary

int initDictionary(String const& dicFileName,
	StringHashTable& dstKeywordHashTable, KeywordAVLTree<int>& dstKeywordTree)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);

	int lenFileName = dicFileName.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name [%s] is too long\n", dicFileName.peekStringToCharPointer());
		printf("Dictionary load fail\n");
		return -1;
	}
	fin.open(dicFileName.peekStringToCharPointer(), std::ios::in);
	if (!fin.is_open())
	{
		printf("File [%s] does not exist\n", dicFileName.peekStringToCharPointer());
		printf("Dictionary load fail\n");
		return -1;
	}

	//Move filestream pointer to actual txt contents (skip header contents)
	//because String is internally char, does not use unsigned char for memory(binary code) compare
	char typeUnicode[] = { 0xFF, 0xFE };
	char typeUnicodeBigEndian[] = { 0xFE, 0xFF };
	char typeUTF8[] = { 0xEF, 0xBB, 0xBF };
	int sizeUnicode = sizeof(typeUnicode) / sizeof(typeUnicode[0]);
	int sizeUnicodeBigEndian = sizeof(typeUnicodeBigEndian) / sizeof(typeUnicodeBigEndian[0]);
	int sizeUTF8 = sizeof(typeUTF8) / sizeof(typeUTF8[0]);

	int const MAX_TXT_HEADER_LEN = 3;
	char txtHeader[MAX_TXT_HEADER_LEN + 1]; //ANSI(none), UNICODE(FF FE), UNICODE Big-Endian(FE FF), UTF-8(EF BB BF)
	fin.read(txtHeader, MAX_TXT_HEADER_LEN);

	bool bFoundType = false;
	if (memcmp(txtHeader, typeUnicode, sizeUnicode) == 0)
	{
		fin.seekg(sizeUnicode);
		bFoundType = true;
	}
	if (!bFoundType &&
		memcmp(txtHeader, typeUnicodeBigEndian, sizeUnicodeBigEndian) == 0)
	{
		fin.seekg(sizeUnicodeBigEndian);
		bFoundType = true;
	}
	if (!bFoundType &&
		memcmp(txtHeader, typeUTF8, sizeUTF8) == 0)
	{
		fin.seekg(sizeUTF8);
		bFoundType = true;
	}

	//actual dictionary initializing
	char strBuffer[MAX_STRING_CHUNK_LEN + 1] = { '\0', };

	while (true)
	{
		//the dictionary's word length must not be > MAX_CHUNK_LEN in char length
		fin.getline(strBuffer, MAX_STRING_CHUNK_LEN);
		if ((int)fin.gcount() == 0) //return std::streamsize (== long long)
			break;

		String string = String(strBuffer);
		int ID = dstKeywordHashTable.add(string);
		dstKeywordTree.insert(Keyword<>(string, ID), ID);
	}
	fin.close();

	printf("Dictionary load success\n");
	return 0;
}

int initDictionary(String const& dicFileName, StringHashTable& dstKeywordHashTable)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);

	int lenFileName = dicFileName.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name [%s] is too long\n", dicFileName.peekStringToCharPointer());
		printf("Dictionary load fail\n");
		return -1;
	}
	fin.open(dicFileName.peekStringToCharPointer(), std::ios::in);
	if (!fin.is_open())
	{
		printf("File [%s] does not exist\n", dicFileName.peekStringToCharPointer());
		printf("Dictionary load fail\n");
		return -1;
	}

	//Move filestream pointer to actual txt contents (skip header contents)
	//because String is internally char, does not use unsigned char for memory(binary code) compare
	char typeUnicode[] = { 0xFF, 0xFE };
	char typeUnicodeBigEndian[] = { 0xFE, 0xFF };
	char typeUTF8[] = { 0xEF, 0xBB, 0xBF };
	int sizeUnicode = sizeof(typeUnicode) / sizeof(typeUnicode[0]);
	int sizeUnicodeBigEndian = sizeof(typeUnicodeBigEndian) / sizeof(typeUnicodeBigEndian[0]);
	int sizeUTF8 = sizeof(typeUTF8) / sizeof(typeUTF8[0]);

	int const MAX_TXT_HEADER_LEN = 3;
	char txtHeader[MAX_TXT_HEADER_LEN + 1]; //ANSI(none), UNICODE(FF FE), UNICODE Big-Endian(FE FF), UTF-8(EF BB BF)
	fin.read(txtHeader, MAX_TXT_HEADER_LEN);

	bool bFoundType = false;
	if (memcmp(txtHeader, typeUnicode, sizeUnicode) == 0)
	{
		fin.seekg(sizeUnicode);
		bFoundType = true;
	}
	if (!bFoundType &&
		memcmp(txtHeader, typeUnicodeBigEndian, sizeUnicodeBigEndian) == 0)
	{
		fin.seekg(sizeUnicodeBigEndian);
		bFoundType = true;
	}
	if (!bFoundType &&
		memcmp(txtHeader, typeUTF8, sizeUTF8) == 0)
	{
		fin.seekg(sizeUTF8);
		bFoundType = true;
	}

	//actual dictionary initializing
	char strBuffer[MAX_STRING_CHUNK_LEN + 1] = { '\0', };

	while (true)
	{
		//the dictionary's word length must not be > MAX_CHUNK_LEN in char length
		fin.getline(strBuffer, MAX_STRING_CHUNK_LEN);
		if ((int)fin.gcount() == 0) //return std::streamsize (== long long)
			break;

		String string = String(strBuffer);
		int ID = dstKeywordHashTable.add(string);
	}
	fin.close();

	printf("Dictionary load success\n");
	return 0;
}

////////////////////////////////////////////////////////////////////////
//extractInfo

int extractInfo(String const& srcFileName, String const& dstFileName)
{
	int result = 0;

	String strHTMLContents;
	String strHTMLKeyContents;

	result = strHTMLContents.readFile(srcFileName);
	if (result != 0)
	{
		printf("Load[%s] : fail\n", srcFileName.peekStringToCharPointer());
		printf("Extract info fail\n");
		return -1;
	}
	else
		printf("Load[%s] : success\n", srcFileName.peekStringToCharPointer());

	strHTMLContents.parseHTML(strHTMLKeyContents);
	result = strHTMLKeyContents.writeFile(dstFileName);


	if (result != 0)
	{
		printf("Write[%s] : fail\n", dstFileName.peekStringToCharPointer());
		printf("Extract info fail\n");
		return -1;
	}
	else
		printf("Write[%s] : success\n", dstFileName.peekStringToCharPointer());


	printf("Extract info success\n");
	return 0;
}

////////////////////////////////////////////////////////////////////////
//divideWords

int divideWords(String const& srcFileName, String const& dstFileName,
	StringHashTable const& srcKeywordgHashTable, KeywordAVLTree<int>& srcKeywordTree, Doc<int>& doc)
{
	if (srcKeywordTree.isEmpty())
	{
		printf("Error : ::divideWords() : The srcKeywordTree is empty\n");
		return -1;
	}

	int result = 0;

	String strHTMLKeyContents;
	if (strHTMLKeyContents.readFile(srcFileName) != 0)
	{
		printf("Load[%s] : fail\n", srcFileName.peekStringToCharPointer());
		printf("Divide words fail\n");
		return -1;
	}

	int len = strHTMLKeyContents.getTotalLength();
	String strKeyString;

	StringLinkedList<int> listFoundKeyWords;
	int i = 1;
	bool bFoundResult = false;

	//calling getSubstring fuction in every possible length is not effect
	//reduce the substring's possible length cases
	while (i <= len)
	{
		//get first chinese character of current pos
		if (i + CHINESE_CHARACTER_LEN - 1 < len)
			strKeyString = strHTMLKeyContents.getSubstring(i, CHINESE_CHARACTER_LEN);

		//if the firstChineseCharacter is in the word list
		AVLTree<StringHashSubBucket>* pSubBucketTree = srcKeywordgHashTable.doesFirstStrCharMatch(strKeyString);
		if (!pSubBucketTree)
			i++;
		else
		{
			//check if even the seoncdChineseCharacter matches one of the word list
			typedef LinkedList<LinkedList<StringBasicInfo>> LenLenList;
			typedef LinkedList<StringBasicInfo> LenList;
			strKeyString = strHTMLKeyContents.getSubstring(i, 2 * CHINESE_CHARACTER_LEN);
			LenLenList* pLenLenList = srcKeywordgHashTable.doesSecondStrCharMatch(strKeyString, pSubBucketTree);
			if (!pLenLenList) //not found any matches
				i += CHINESE_CHARACTER_LEN;
			else
			{ //found a match
				//Get all available keyword length and compare the string
				LinkedListIter<LenList> iter1(pLenLenList);
				while (iter1.isValid())
				{
					int stringLen = iter1.curr()->m_key;
					if (i + stringLen - 1 < len)
						strKeyString = strHTMLKeyContents.getSubstring(i, stringLen);

					LinkedListIter<StringBasicInfo> iter2(iter1.getNodeData());
					while (iter2.isValid())
					{
						StringBasicInfo* pStringBasicInfo = iter2.curr()->getNodeData();
						if (pStringBasicInfo->m_string == strKeyString)
						{
							//insert found keyword (no duplication)
							//& update keywordTree
							//& insert and update doc for the found keyword
							Keyword<int>* pKeyword = srcKeywordTree.search(pStringBasicInfo->m_ID);
							pKeyword->increaseOccur();

							Doc<int>*pDoc = pKeyword->searchDoc(doc.getID());
							if (!pDoc)
							{
								pDoc = pKeyword->insert(doc);
								listFoundKeyWords.append(strKeyString, pStringBasicInfo->m_ID);

								pKeyword->increaseDF();
								pDoc->increaseTimes();
							}
							else
								pDoc->increaseTimes();
						}
						iter2.next();
					}
					iter1.next();
				}
				i += CHINESE_CHARACTER_LEN;
			}
		}
	}

	result = listFoundKeyWords.writeFile(dstFileName, '\n');
	if (result != 0)
	{
		printf("Write[%s] : fail\n", dstFileName.peekStringToCharPointer());
		printf("Divide words fail\n");
		return -1;
	}
	else
	{
		printf("Write[%s] : success\n", dstFileName.peekStringToCharPointer());
		printf("Divide words success\n");
	}

	return 0;
}

int divideWords(String const& srcFileName, String const& dstFileName,
	StringHashTable const& srcKeywordgHashTable)
{
	int result = 0;

	String strHTMLKeyContents;
	if (strHTMLKeyContents.readFile(srcFileName) != 0)
	{
		printf("Load[%s] : fail\n", srcFileName.peekStringToCharPointer());
		printf("Divide words fail\n");
		return -1;
	}

	int len = strHTMLKeyContents.getTotalLength();
	String strKeyString;

	AVLTree<int> KeywordIDTree;
	StringLinkedList<int> listFoundKeyWords; //to show the keyword list in scan line order
	int i = 1;
	bool bFoundResult = false;

	//calling getSubstring fuction in every possible length is not effect
	//reduce the substring's possible length cases
	while (i <= len)
	{
		//get first chinese character of current pos
		if (i + CHINESE_CHARACTER_LEN - 1 < len)
			strKeyString = strHTMLKeyContents.getSubstring(i, CHINESE_CHARACTER_LEN);

		//if the firstChineseCharacter is in the word list
		AVLTree<StringHashSubBucket>* pSubBucketTree = srcKeywordgHashTable.doesFirstStrCharMatch(strKeyString);
		if (!pSubBucketTree)
			i++;
		else
		{
			//check if even the seoncdChineseCharacter matches one of the word list
			typedef LinkedList<LinkedList<StringBasicInfo>> LenLenList;
			typedef LinkedList<StringBasicInfo> LenList;
			strKeyString = strHTMLKeyContents.getSubstring(i, 2 * CHINESE_CHARACTER_LEN);
			LenLenList* pLenLenList = srcKeywordgHashTable.doesSecondStrCharMatch(strKeyString, pSubBucketTree);
			if (!pLenLenList) //not found any matches
				i += CHINESE_CHARACTER_LEN;
			else
			{ //found a match
				//Get all available keyword length and compare the string
				LinkedListIter<LenList> iter1(pLenLenList);
				while (iter1.isValid())
				{
					int stringLen = iter1.curr()->m_key;
					if (i + stringLen - 1 < len)
						strKeyString = strHTMLKeyContents.getSubstring(i, stringLen);

					LinkedListIter<StringBasicInfo> iter2(iter1.getNodeData());
					while (iter2.isValid())
					{
						StringBasicInfo* pStringBasicInfo = iter2.curr()->getNodeData();
						if (pStringBasicInfo->m_string == strKeyString)
						{
							//insert found keyword (no duplication)
							//to check duplication (to only show the pure keyword list)

							AVLTreeNode<int>* pKeywordIDNode = KeywordIDTree.search(pStringBasicInfo->m_ID);
							if (!pKeywordIDNode) //not added yet (no duplication)
							{
								KeywordIDTree.insert(pStringBasicInfo->m_ID, pStringBasicInfo->m_ID);
								listFoundKeyWords.append(strKeyString, pStringBasicInfo->m_ID);
							}
						}
						iter2.next();
					}
					iter1.next();
				}
				i += CHINESE_CHARACTER_LEN;
			}
		}
	}

	result = listFoundKeyWords.writeFile(dstFileName, '\n');
	if (result != 0)
	{
		printf("Write[%s] : fail\n", dstFileName.peekStringToCharPointer());
		printf("Divide words fail\n");
		return -1;
	}
	else
	{
		printf("Write[%s] : success\n", dstFileName.peekStringToCharPointer());
		printf("Divide words success\n");
	}

	return 0;
}

////////////////////////////////////////////////////////////////////////

int extractKeywords(StringHashTable& KeywordHashTable, KeywordAVLTree<int>& KeywordTree)
{
	////////////////////////////////////////////////////////////////////////
	//initDictionary
	//Store dictionary according to..
	//First character -> Second character -> string length
	//Default : STRING_HASH_TABLE_SIZE = INITIAL_STRING_BUCKET_SIZE;
	//StringHashTable KeywordHashTable;

	char *chineseDicRoot = "..\\input\\";
	char chineseDicFileName[FILENAME_MAX]; //(.dic)
	sprintf(chineseDicFileName, "%sdic.dic", chineseDicRoot);

	//KeywordAVLTree<int> KeywordTree;
	initDictionary(String(chineseDicFileName), KeywordHashTable, KeywordTree);

	//TEST
	//FileFunctor<StringHashTable> writeFileFunc(KeywordHashTable,String("test.txt"),FileFunctorMode::WRITE);
	//writeFileFunc();
	//DocList.print();

	////////////////////////////////////////////////////////////////////////
	//extractInfo
	//divideWords
	char *sourceHTMLRoot = "..\\input\\";
	char sourceHTMLFileName[FILENAME_MAX]; //(.html)
	char *parsedHTMLRoot = "..\\output\\";
	char parsedHTMLFileName[FILENAME_MAX]; //(.info)
	char *dividedWordsRoot = "..\\output\\";
	char dividedWordsFileName[FILENAME_MAX]; //(.txt)

	int const nFileNumFirst = 1;
	int const nFileNumLast = 10;
	for (int i = nFileNumFirst; i <= nFileNumLast; i++)
	{
		sprintf(sourceHTMLFileName, "%s%04d.html", sourceHTMLRoot, i);
		sprintf(parsedHTMLFileName, "%s%04d.info", parsedHTMLRoot, i);
		sprintf(dividedWordsFileName, "%s%04d.txt", dividedWordsRoot, i);
		String strSourceHTMLFileName = String(sourceHTMLFileName);

		Doc<int> doc(strSourceHTMLFileName, i); //TODO : change to string ID

		//extractInfo
		if (extractInfo(strSourceHTMLFileName, String(parsedHTMLFileName)) != 0)
			continue;

		//divideWords (store found keywordList as a file)
		//No duplication of keyword.. just increase the count internally
		divideWords(String(parsedHTMLFileName), String(dividedWordsFileName),
			KeywordHashTable, KeywordTree, doc);
	}

	return 0;
}

int extractKeywordsFast(StringHashTable& KeywordHashTable)
{
	////////////////////////////////////////////////////////////////////////
	//initDictionary
	//Store dictionary according to..
	//First character -> Second character -> string length
	//Default : STRING_HASH_TABLE_SIZE = INITIAL_STRING_BUCKET_SIZE;
	//StringHashTable KeywordHashTable;

	char *chineseDicRoot = "..\\input\\";
	char chineseDicFileName[FILENAME_MAX]; //(.dic)
	sprintf(chineseDicFileName, "%sdic.dic", chineseDicRoot);

	initDictionary(String(chineseDicFileName), KeywordHashTable);

	//TEST
	//FileFunctor<StringHashTable> writeFileFunc(KeywordHashTable,String("test.txt"),FileFunctorMode::WRITE);
	//writeFileFunc();
	//DocList.print();

	////////////////////////////////////////////////////////////////////////
	//extractInfo
	//divideWords
	char *sourceHTMLRoot = "..\\input\\";
	char sourceHTMLFileName[FILENAME_MAX]; //(.html)
	char *parsedHTMLRoot = "..\\output\\";
	char parsedHTMLFileName[FILENAME_MAX]; //(.info)
	char *dividedWordsRoot = "..\\output\\";
	char dividedWordsFileName[FILENAME_MAX]; //(.txt)

	int const nFileNumFirst = 1;
	int const nFileNumLast = 10;
	for (int i = nFileNumFirst; i <= nFileNumLast; i++)
	{
		sprintf(sourceHTMLFileName, "%s%04d.html", sourceHTMLRoot, i);
		sprintf(parsedHTMLFileName, "%s%04d.info", parsedHTMLRoot, i);
		sprintf(dividedWordsFileName, "%s%04d.txt", dividedWordsRoot, i);
		String strSourceHTMLFileName = String(sourceHTMLFileName);

		Doc<int> doc(strSourceHTMLFileName, i); //TODO : change to string ID

		//extractInfo
		if (extractInfo(strSourceHTMLFileName, String(parsedHTMLFileName)) != 0)
			continue;

		//divideWords (store found keywordList as a file)
		//No duplication of keyword.. just increase the count internally
		divideWords(String(parsedHTMLFileName), String(dividedWordsFileName),
			KeywordHashTable);
	}

	return 0;
}
