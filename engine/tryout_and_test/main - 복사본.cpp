#include <iostream>
#include <time.h>

#include "String.h"
#include "StringHashTable.h"

#include "TestFunction.h"

//extract html info
//srcFileName (.html) : sourceHTMLFileName
//dstFileName (.info) : parsedHTMLFileName
int extractInfo(String const& srcFileName, String const& dstFileName)
{
	String strHTMLContents;
	String strHTMLKeyContents;
	int result = 0;

	result = strHTMLContents.readFile(srcFileName);
	if (result != 0) { printf("Load[%s] : fail\n", srcFileName.peekStringToCharPointer()); return -1; }
	else printf("Load[%s] : success\n", srcFileName.peekStringToCharPointer());

	strHTMLContents.parseHTML(strHTMLKeyContents);

	result = strHTMLKeyContents.writeFile(dstFileName);
	if (result != 0) { printf("Write[%s] : fail\n", dstFileName.peekStringToCharPointer()); return -1; }
	else printf("Write[%s] : success\n", dstFileName.peekStringToCharPointer());
	
	return 0;
}

//init (chinese) dictionary
//Uses HashTable for more oragnized and faster search of strings
//and the HashTable uses StringLinkedLists internally (only when occurs collision in buckets)
//cf> independent usage of StringLinkedList is also no prob (but in terms of search, it's too slow)
//dstStringHashTable : to store word list
//dicFileName (.dic) : chineseDicFileName
int initDictionary(String const& dicFileName, StringHashTable& dstStringHashTable)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);

	int lenFileName = dicFileName.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name is too long\n");
		return -1;
	}
	fin.open(dicFileName.peekStringToCharPointer(), std::ios::in);
	if (!fin.is_open())
	{
		printf("File does not exist\n");
		return -1;
	}
	
	//Check if it's TXT
	char *pExtensionName = dicFileName.peekStringToCharPointer();
	bool bHasExtension = false;
	int i;
	for (i = lenFileName-1; i >= 0; i--)
	{
		if (pExtensionName[i] == '.')
		{
			bHasExtension = true;
			break;
		}
	}
	if (bHasExtension)
	{//Move filestream pointer to actual txt contents (skip header contents)
		if(strcmp(&pExtensionName[i], ".txt")==0)
		{
			char typeUnicode[] = {0xFF,0xFE};
			char typeUnicodeBigEndian[] = { 0xFE, 0xFF };
			char typeUTF8[] = { 0xEF,0xBB , 0xBF};
			int sizeUnicode = sizeof(typeUnicode) / sizeof(typeUnicode[0]);
			int sizeUnicodeBigEndian = sizeof(typeUnicodeBigEndian) / sizeof(typeUnicodeBigEndian[0]);
			int sizeUTF8 = sizeof(typeUTF8) / sizeof(typeUTF8[0]);

			int const MAX_TXT_HEADER_LEN = 3;
			char txtHeader[MAX_TXT_HEADER_LEN+1]; //ANSI(none), UNICODE(FF FE), UNICODE Big-Endian(FE FF), UTF-8(EF BB BF)
			fin.read(txtHeader, MAX_TXT_HEADER_LEN);

			bool bFoundType = false;
			if (memcmp(txtHeader, typeUnicode, sizeUnicode) == 0)
			{
				fin.seekg(sizeUnicode);
				bFoundType = true;
				printf("1\n");
			}
			if (!bFoundType &&
				memcmp(txtHeader, typeUnicodeBigEndian,sizeUnicodeBigEndian) == 0)
			{
				fin.seekg(sizeUnicodeBigEndian);
				bFoundType = true;
				printf("2\n");
			}
			if (!bFoundType &&
				memcmp(txtHeader, typeUTF8,sizeUTF8) == 0)
			{
				fin.seekg(sizeUTF8);
				bFoundType = true;
				printf("3\n");
			}
			printf("%d %d %d\n",sizeUnicode,sizeUnicodeBigEndian,sizeUTF8);
			
		}
	}
	
	char strBuffer[MAX_STRING_CHUNK_LEN + 1] = { '\0', };
	while (true)
	{
		//the dictionary's word length must not be > MAX_CHUNK_LEN in char length
		fin.getline(strBuffer, MAX_STRING_CHUNK_LEN);
		if ((int)fin.gcount() == 0) //return std::streamsize (== long long)
			break;
		dstStringHashTable.add(String(strBuffer));
	}

	fin.close();

	return 0;
}

//srcFileName (.info) : parsedHTMLFileName
//dstFileName (.txt) : dividedWordsFileName
int divideWords(String const& srcFileName, String const& dstFileName, StringHashTable const& srcStringHashTable)
{
	String strHTMLKeyContents;
	if (strHTMLKeyContents.readFile(srcFileName) != 0)
		return -1;
	
	int len = strHTMLKeyContents.getTotalLength();
	String strKeyString;

	StringLinkedList listFoundKeyWords;
	int i = 0;
	bool bFoundResult = false;

	//const int WORD_LENGTH_MAX = 10;
	//calling getSubstring fuction in every possible length is not effect
	//to reduce the function call, reduce the substring's possible length cases
	while (i<len)
	{
		//if the subString is in the word list


		//get first chinese character of current pos
		strKeyString = strHTMLKeyContents.getSubstring(i, CHINESE_CHARACTER_LEN);




		//if the character is in one of the buckets,	
		int lenKeyWord;
		

		bFoundResult = srcStringHashTable.search(strKeyString);
		if (bFoundResult == true)
		{
			strKeyString.append('\n');
			listFoundKeyWords.append(strKeyString);

			i += 3;
		}
		else
		{
			i++;
		}
		
	}

	int result = 0;
	if (result != 0) { printf("Write[%s] : fail\n", dstFileName.peekStringToCharPointer()); return -1; }
	else printf("Write[%s] : success\n", dstFileName.peekStringToCharPointer());
	return listFoundKeyWords.writeFile(dstFileName);
}

int main()
{
	int result = 0;
	////////////////////////////////////////////////////////////////////////
	//initDictionary
	const int STRING_HASH_TABLE_SIZE = INITIAL_STRING_BUCKET_SIZE;
	StringHashTable stringHashTable(STRING_HASH_TABLE_SIZE);

	char *chineseDicRoot = "..\\input\\";
	char chineseDicFileName[FILENAME_MAX]; //(.dic)
	sprintf(chineseDicFileName, "%sdic.dic", chineseDicRoot);

	result = initDictionary(String(chineseDicFileName), stringHashTable);
	if (result != 0) printf("Dictionary load fail\n");
	else printf("Dictionary load success\n");

	for (int i = 0; i < stringHashTable.nCurBuckets; i++)
	{
		String name("..\\test\\");
		char str[10] = {'\0',};
		name.concat(itoa(i, str, 10));
		name.concat(".txt");
		stringHashTable.pBucket[i].link->writeFile(name,'\n');
	}

	////////////////////////////////////////////////////////////////////////
	//extractInfo()
	//divideWords()
	//char *sourceHTMLRoot = "..\\input\\";
	//char sourceHTMLFileName[FILENAME_MAX]; //(.html)
	//char *parsedHTMLRoot = "..\\output\\";
	//char parsedHTMLFileName[FILENAME_MAX]; //(.info)
	//char *dividedWordsRoot = "..\\output\\";
	//char dividedWordsFileName[FILENAME_MAX]; //(.txt)


	//int const nFileNumFirst = 1;
	//int const nFileNumLast = 10;
	//for (int i = nFileNumFirst; i <= nFileNumLast; i++)
	//{
	//	sprintf(sourceHTMLFileName, "%s%04d.html", sourceHTMLRoot, i);
	//	sprintf(parsedHTMLFileName, "%s%04d.info", parsedHTMLRoot, i);
	//	sprintf(dividedWordsFileName, "%s%04d.txt", dividedWordsRoot, i);

	//	result = extractInfo(String(sourceHTMLFileName), String(parsedHTMLFileName));
	//	if (result != 0) printf("Extract info fail\n");
	//	else printf("Extract info success\n");

	//	result = divideWords(String(parsedHTMLFileName),String(dividedWordsFileName),stringHashTable);
	//	if (result != 0) printf("Divide words fail\n");
	//	else printf("Divide words success\n");
	//}
	

	return 0;
}