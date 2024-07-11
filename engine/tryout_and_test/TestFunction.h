#ifndef TESTFUNCTION_H
#define TESTFUNCTION_H

#include "String.h"
#include "LinkedStack.h"
//#include "StringLinkedList.h"
//#include "StringHashTable.h"

int test1()
{
	//test
	//1.String creater
	// - default creator
	// - copy creator
	//2.=(char const*const) operator

	char *Str01 = "ABC"; //3
	char *Str02 = "01234567890123456789012345678901234567890123456789"
		"01234567890123456789012345678901234567890123456789"; //100
	char *Str03 = "01234567890123456789012345678901234567890123456789"
		"012345678901234567890123456789012345678901234567890"; //101
	char *Str04 = ""; //0
	char *Str05 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"; //200
	char Str06[100] = {}; //0
	char *Str07 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"012345678901234567890123456789012345678901234567890"; //201
	String myString01;

	myString01 = Str01;
	printf("[01]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	myString01 = Str02;
	printf("[02]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	myString01 = Str03;
	printf("[03]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	myString01 = Str04;
	printf("[04]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	myString01 = Str05;
	printf("[05]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	myString01 = Str06;
	printf("[06]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	myString01 = Str07;
	printf("[07]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());

	String myString02 = myString01;
	printf("[10]"); myString02.print(); printf("\n");
	printf("%u\n", myString02.getTotalLength());

	return 0;
}

int test2()
{
	//test
	//1.String creater
	//2.String concat

	char *Str01 = "ABC"; //3
	char *Str02 = "01234567890123456789012345678901234567890123456789"
		"01234567890123456789012345678901234567890123456789"; //100
	char *Str03 = "01234567890123456789012345678901234567890123456789"
		"012345678901234567890123456789012345678901234567890"; //101
	char *Str04 = ""; //0
	char *Str05 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"; //200
	char *Str06 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"012345678901234567890123456789012345678901234567890"; //201
	String myString01(Str01);
	String myString02(Str02);
	String myString03(Str03);
	String myString04(Str04);
	String myString05(Str05);
	String myString06(Str06);

	printf("[01]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());
	printf("[02]"); myString02.print(); printf("\n");
	printf("%u\n", myString02.getTotalLength());
	printf("[03]"); myString03.print(); printf("\n");
	printf("%u\n", myString03.getTotalLength());
	printf("[04]"); myString04.print(); printf("\n");
	printf("%u\n", myString04.getTotalLength());
	printf("[05]"); myString05.print(); printf("\n");
	printf("%u\n", myString05.getTotalLength());
	printf("[06]"); myString06.print(); printf("\n");
	printf("%u\n", myString06.getTotalLength());

	myString01.concat(myString02);
	printf("[10]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getTotalLength());

	myString03.concat(myString04);
	printf("[11]"); myString03.print(); printf("\n");
	printf("%u\n", myString03.getTotalLength());

	myString05.concat(myString06);
	printf("[12]"); myString05.print(); printf("\n");
	printf("%u\n", myString05.getTotalLength());



	printf("myString01[1] : %c\n", myString01[1]);
	printf("myString02[1] : %c\n", myString02[1]);
	printf("myString02[100] : %c\n", myString02[100]);
	printf("myString03[1] : %c\n", myString03[1]);
	printf("myString03[100] : %c\n", myString03[100]);
	printf("myString03[101] : %c\n", myString03[101]);
	printf("myString05[101] : %c\n", myString05[101]);
	printf("myString05[200] : %c\n", myString05[200]);
	printf("myString06[201] : %c\n", myString06[201]);

	return 0;
}

int test3()
{
	//test
	//1.LinkedStack

	char *Str01 = "ABC"; //3
	char *Str02 = "01234567890123456789012345678901234567890123456789"
		"01234567890123456789012345678901234567890123456789"; //100
	char *Str03 = "01234567890123456789012345678901234567890123456789"
		"012345678901234567890123456789012345678901234567890"; //101
	char *Str04 = ""; //0
	char *Str05 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"; //200
	char *Str06 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"012345678901234567890123456789012345678901234567890"; //201
	String myString01(Str01);
	String myString02(Str02);
	String myString03(Str03);

	String myString07(Str04);
	String myString08(Str05);
	String myString09(Str06);

	String myString04;
	String myString05;
	String myString06;
	myString04 = myString07;
	myString05 = myString08;
	myString06 = myString09;



	LinkedStack<String> stack;
	String str;
	int stackResult = 0;
	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n", stackResult);

	printf("push[01]\n");
	stack.push(myString01);
	stack.peek(myString01);
	myString01.print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("push[02]\n");
	stack.push(myString02);
	stack.peek(myString02);
	myString02.print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("push[03]\n");
	stack.push(myString03);
	stack.peek(myString03);
	myString03.print(); printf("\n");
	printf("size : %d\n", stack.getSize());


	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n", stackResult);
	printf("\n");

	printf("pop[03]\n");
	stack.pop(str);
	str.print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("pop[02]\n");
	stack.pop(str);
	str.print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("pop[01]\n");
	stack.pop(str);
	str.print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n", stackResult);

	return 0;
}

//
//int testSubString()
//{
//	char *Str01 = "ABC"; //3
//	char *Str02 = "01234567890123456789012345678901234567890123456789"
//		"01234567890123456789012345678901234567890123456789"; //100
//	char *Str03 = "01234567890123456789012345678901234567890123456789"
//		"012345678901234567890123456789012345678901234567890"; //101
//	char *Str04 = ""; //0
//	char *Str05 = "01234567890123456789012345678901234567890123456789"\
//		"01234567890123456789012345678901234567890123456789"\
//		"01234567890123456789012345678901234567890123456789"\
//		"01234567890123456789012345678901234567890123456789"; //200
//	char *Str06 = "01234567890123456789012345678901234567890123456789"\
//		"01234567890123456789012345678901234567890123456789"\
//		"01234567890123456789012345678901234567890123456789"\
//		"012345678901234567890123456789012345678901234567890"; //201
//
//	{
//		String strSrc("9876543210");
//		String strSub;
//		strSub = strSrc.getSubstring(1, 1);
//		strSub.print(); printf("\n");
//		strSub = strSrc.getSubstring(10, 1);
//		strSub.print(); printf("\n");
//		printf("\n");
//	}
//	{
//		String strSrc[6] = {
//			String(Str01), String(Str02), String(Str03),
//			String(Str04), String(Str05), String(Str06),
//		};
//
//		String strSub;
//		int i = 0;
//		strSub = strSrc[i].getSubstring(1, 1);
//		strSub.print(); printf("\n");
//		strSub = strSrc[i].getSubstring(1, 3);
//		strSub.print(); printf("\n");
//		strSub = strSrc[i].getSubstring(3, 1);
//		strSub.print(); printf("\n");
//		strSub = strSrc[i].getSubstring(2, 2);
//		strSub.print(); printf("\n");
//		printf("\n");
//
//		i = 1;
//		strSub = strSrc[i].getSubstring(1, 100);
//		strSub.print(); printf("\n");
//		strSub = strSrc[i].getSubstring(100, 1);
//		strSub.print(); printf("\n");
//		strSub = strSrc[i].getSubstring(90, 10);
//		strSub.print(); printf("\n");
//		strSub = strSrc[i].getSubstring(91, 10);
//		strSub.print(); printf("\n");
//		printf("\n");
//
//		i = 2;
//		strSub = strSrc[i].getSubstring(101, 1);
//		strSub.print(); printf("\n");
//	}
//
//
//	return 0;
//}
//

int testLinkedList()
{
	//TODO : test remove

	StringLinkedList L1;
	String newString[10] = {
		String(""),
		String("1"),
		String("2"),
		String("3"),
		String("4"),
		String("5"),
		String("  1234"),
		String(" 1234"),
	};
	StringLinkedListNode *pFoundNode = NULL;

	printf("%d\n", String("") == String(""));
	printf("\n");

	L1.append(newString[0]);
	L1.append(newString[1]);
	L1.append(newString[2]);
	L1.append(newString[3]);
	L1.append(newString[4]);
	L1.append(newString[5]);
	L1.append(newString[6]);
	L1.append(newString[7]);

	for (int i = 0; i < 8; i++)
	{
		pFoundNode = L1.search(newString[i]);
		if (pFoundNode)
		{
			pFoundNode->print();
			printf("\n"); //empty string
		}
	}

	printf("\n");
	L1.print();

	return 0;
}

int test_initDictionary(StringHashTable& dstStringHashTable, String const& dicFileName)
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
		printf("File open error\n");
		return -1;
	}

	String newString;
	char strBuffer[MAX_STRING_CHUNK_LEN + 1] = { '\0', };
	int nRead = 0; int i = 0;
	while (true)
	{
		i++;
		//the dictionary's word length must not be > MAX_CHUNK_LEN in char length
		fin.getline(strBuffer, MAX_STRING_CHUNK_LEN);
		nRead = (int)fin.gcount(); //return std::streamsize (== long long)
		if (nRead == 0)
			break;

		if (strBuffer[nRead - 1] == '\0')
		{
			strBuffer[nRead - 1] = '\n';
			strBuffer[nRead] = '\0';
		}
		else if (strBuffer[nRead] == '\0')
		{
			strBuffer[nRead] = '\n';
			strBuffer[nRead + 1] = '\0';
		}

		dstStringHashTable.add(String(strBuffer));

	}
	for (int i = 0; i < dstStringHashTable.nCurBuckets; i++)
		dstStringHashTable.pBucket[i].link->writeFile(String("myDic.dic"));
	fin.close();

	return 0;
}


int testSubString()
{
	char *Str01 = "ABC"; //3
	char *Str02 = "01234567890123456789012345678901234567890123456789"
		"01234567890123456789012345678901234567890123456789"; //100
	char *Str03 = "01234567890123456789012345678901234567890123456789"
		"012345678901234567890123456789012345678901234567890"; //101
	char *Str04 = ""; //0
	char *Str05 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"; //200
	char *Str06 = "01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"01234567890123456789012345678901234567890123456789"\
		"012345678901234567890123456789012345678901234567890"; //201

	String myString01(Str01);
	String myString02(Str02);
	String myString03(Str03);
	String myString04(Str04);
	String myString05(Str05);
	String myString06(Str06);
	String subString;

	if (0)
	{//3
		subString = myString01.getSubstring(1, 1);
		subString.print(); printf("\n");
		subString = myString01.getSubstring(1, 2);
		subString.print(); printf("\n");
		subString = myString01.getSubstring(1, 3);
		subString.print(); printf("\n");
		subString = myString01.getSubstring(1, 4); //exceed
		subString.print(); printf("\n");
		subString = myString01.getSubstring(2, 1);
		subString.print(); printf("\n");
		subString = myString01.getSubstring(2, 2);
		subString.print(); printf("\n");
		subString = myString01.getSubstring(2, 3); //exceed
		subString.print(); printf("\n");
		subString = myString01.getSubstring(3, 1);
		subString.print(); printf("\n");
		subString = myString01.getSubstring(3, 2); //exceed
		subString.print(); printf("\n");
		printf("//////////////////////////////////\n");
	}

	if (0)
	{//100
		subString = myString02.getSubstring(1, 1);
		subString.print(); printf("\n");
		subString = myString02.getSubstring(1, 10);
		subString.print(); printf("\n");
		subString = myString02.getSubstring(1, 100);
		subString.print(); printf("\n");
		subString = myString02.getSubstring(1, 101); //exceed
		subString.print(); printf("\n");
		subString = myString02.getSubstring(100, 1);
		subString.print(); printf("\n");
		subString = myString02.getSubstring(100, 2); //exceed
		subString.print(); printf("\n");
		subString = myString02.getSubstring(0, 3); //pos == 0
		subString.print(); printf("\n");
		subString = myString02.getSubstring(3, 0); //len == 0
		subString.print(); printf("\n");
		printf("//////////////////////////////////\n");
	}

	if (0)
	{//101
		subString = myString03.getSubstring(1, 100);
		subString.print(); printf("\n");
		subString = myString03.getSubstring(1, 101);
		subString.print(); printf("\n");
		subString = myString03.getSubstring(1, 102); //exceed
		subString.print(); printf("\n");
		subString = myString03.getSubstring(100, 1);
		subString.print(); printf("\n");
		subString = myString03.getSubstring(100, 2);
		subString.print(); printf("\n");
		subString = myString03.getSubstring(100, 3); //exceed
		subString.print(); printf("\n");
		subString = myString03.getSubstring(101, 1);
		subString.print(); printf("\n");
		subString = myString03.getSubstring(101, 2); //exceed 
		subString.print(); printf("\n");
		subString = myString03.getSubstring(91, 11);
		subString.print(); printf("\n");
		subString = myString03.getSubstring(91, 12); //exceed
		subString.print(); printf("\n");
		printf("//////////////////////////////////\n");
	}

	if (0)
	{//0
		subString = myString04.getSubstring(1, 1);
		subString.print(); printf("\n");
		subString = myString04.getSubstring(1, 0);
		subString.print(); printf("\n");
		subString = myString04.getSubstring(0, 1);
		subString.print(); printf("\n");
		printf("//////////////////////////////////\n");
	}

	if (0)
	{//200
		subString = myString05.getSubstring(1, 100);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(1, 101);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(1, 110);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(21, 40);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(1, 140);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(1, 200);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(21, 81);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(100, 100);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(100, 101);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(21, 180);
		subString.print(); printf("\n");
		subString = myString05.getSubstring(21, 181); //exceed
		subString.print(); printf("\n");
		printf("//////////////////////////////////\n");
	}

	if (0)
	{//201
		subString = myString06.getSubstring(1, 200);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(11, 100);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(51, 50);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(41, 130);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(100, 1);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(100, 2);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(101, 100);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(101, 101);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(1, 201);
		subString.print(); printf("\n");
		subString = myString06.getSubstring(1, 202); //exceed
		subString.print(); printf("\n");
		printf("//////////////////////////////////\n");
	}


	return 0;
}


int checkDictionaryContent(StringHashTable& dstStringHashTable, String const& dicFileName)
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
		printf("File open error\n");
		return -1;
	}

	String newString;
	char strBuffer[MAX_STRING_CHUNK_LEN + 1] = { '\0', };
	int nRead = 0;
	int nMin = 10000;
	int nMax = 0;
	bool bUsedLen[61] = { false, };
	int cntFreq[61] = {0,};
	StringLinkedList list;
	while (true)
	{
		//the dictionary's word length must not be > MAX_CHUNK_LEN in char length
		fin.getline(strBuffer, MAX_STRING_CHUNK_LEN);
		nRead = (int)fin.gcount(); //return std::streamsize (== long long)
		if (nRead == 0)
			break;
		nMin = nMin < nRead ? nMin : nRead;
		nMax = nMax > nRead ? nMax : nRead;
		bUsedLen[nRead] = true;
		cntFreq[nRead]++;
		if (nRead == 12 || nRead == 15)
		{
			if (strBuffer[nRead - 1] == '\0') //originally had '\n' so '\n' is CONVERTED to '\0'
			{
				strBuffer[nRead - 1] = '\n';
				strBuffer[nRead] = '\0';
			}
			else if (strBuffer[nRead] == '\0') //originally didn't have '\n' so '\0' is ADDED
			{
				strBuffer[nRead] = '\n';
				strBuffer[nRead + 1] = '\0';
			}
			list.append(String(strBuffer));
		}
		///dstStringHashTable.add(String(strBuffer));
	}
	list.writeFile(String("2Byte.txt"));
	printf("%d %d\n", nMin, nMax);
	for (int i = 1; i <= 20; i++)
		printf("%2d ", i);
	printf("\n");
	for (int i = 1; i <= 20; i++)
		printf("%2d ", bUsedLen[i]);
	printf("\n");
	for (int i = 1; i <= 20; i++)
		printf("%2d ", cntFreq[i]);
	printf("\n");

	for (int i = 21; i <= 40; i++)
		printf("%2d ", i);
	printf("\n");
	for (int i = 21; i <= 40; i++)
		printf("%2d ", bUsedLen[i]);
	printf("\n");
	for (int i = 21; i <= 40; i++)
		printf("%2d ", cntFreq[i]);
	printf("\n");

	for (int i = 41; i <= 60; i++)
		printf("%2d ", i);
	printf("\n");
	for (int i = 41; i <= 60; i++)
		printf("%2d ", bUsedLen[i]);
	printf("\n");
	for (int i = 41; i <= 60; i++)
		printf("%2d ", cntFreq[i]);
	printf("\n");

	fin.close();

	return 0;
}


#endif