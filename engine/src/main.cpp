#include "MainModule.h"


int getResult(String const& queryFileName, String const& resultFileName)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);

	int lenFileName = queryFileName.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name [%s] is too long\n", queryFileName.peekStringToCharPointer());
		printf("Show result fail\n");
		return -1;
	}
	fin.open(queryFileName.peekStringToCharPointer(), std::ios::in);
	if (!fin.is_open())
	{
		printf("File [%s] does not exist\n", queryFileName.peekStringToCharPointer());
		printf("Show result fail\n");
		return -1;
	}

	//Move filestream pointer to actual txt contents (skip header contents)
	//because String is internally char, does not use unsigned char for memory(binary code) compare
	/*enum class TXT_FILE_TYPE
	{

	};*/
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

	int const BUFFER_SIZE_IN_KB = 3;
	char strBuffer[BUFFER_SIZE_IN_KB * 1024 + 1] = { '\0', };
	KeywordAVLTree<int> keywordTree;
	DocLinkedList<int> docListOverall;
	int posFrom = 0;
	int posTo = 0;
	while (true)
	{
		////the dictionary's word length must not be > MAX_CHUNK_LEN in char length
		posFrom = (int)fin.tellg();
		fin.getline(strBuffer, BUFFER_SIZE_IN_KB * 1024);
		int nRead = (int)fin.gcount();
		if (nRead == 0) //return 
			break;
		//(maybe because i'm using 64bit system)
		//gcount()
		//std::streamsize(== long long)
		//tellg()
		//std::streamoff (== long long) : typedef

		if ((posTo = fin.tellg()) == EOF) //EOF(-1)(End of File)
		{
			fin.clear(); //clear EOF state
			fin.seekg(0, std::ios_base::end);
			posTo = fin.tellg();
		}
		fin.seekg(posFrom);

		String keyword;
		while (fin.tellg().operator!=(posTo) &&
			fin.tellg().operator!=(EOF))
		{
			fin >> strBuffer; //automatically adds '\0'
			keyword = strBuffer;
			//docListOverall.append()
		}

		
		//printf("%d %d\n",posFrom, posTo);
		//String strQueryKeywordList;
		//while (fin.tellg().operator!=(posTo))
		//{
		//	fin >> strBuffer;
		//	strQueryKeywordList = strBuffer;

		//	//srcKeywordTree
		//	
		//}
		//break;

		fin.seekg(posTo);

		//int ID = dstKeywordHashTable.add(string);
		//dstKeywordTree.insert(Keyword<>(string, ID), ID);
	}
	fin.close();

	printf("Show result success\n");
	return 0;
}


int main()
{
	////////////////////////////////////////////////////////////////////////
	//DataStructure Experiment1
	//
	//initDictionary() -> extractInfo() -> divideWords()

	//Example 1
	//StringHashTable keywordHashTable;
	//KeywordAVLTree<int> keywordTree;
	//extractKeywords(keywordHashTable, keywordTree);

	//Example 2
	StringHashTable keywordHashTable;
	extractKeywordsFast(keywordHashTable);

	////////////////////////////////////////////////////////////////////////
	//DataStructure Experiment2
	//
	//query.txt -> result.txt
	//query.txt (each line is list made of to be searched one or more keywords)
	//result.txt (show all the keywords in each line found in ..
	//(1) which file (in ID) & (2) found how many times)

	//char *exeFileRoot = "..\\";//"..\\input\\";
	//char queryFileName[FILENAME_MAX] = "query.txt"; //(.txt)
	//char resultFileName[FILENAME_MAX] = "result.txt"; //(.txt)
	//
	//String strQueryFileName(exeFileRoot);
	//String strResultFileName(exeFileRoot);
	//strQueryFileName.concat(queryFileName);
	//strResultFileName.concat(resultFileName);

	//HashTable version
	//getResult(strQueryFileName, strResultFileName);

	//AVLTree version
	//showResult();
	//showResultDetail();

	return 0;
}