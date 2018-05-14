#include <iostream>

#include "String.h"
#include "LinkedStack.h"



class StringLinkedListNode
{
	friend class StringLinkedList;
protected:
	struct
	{
		String str;
		//int lineFoundFrom;
	};
	StringLinkedListNode *next;
	StringLinkedListNode *prev;

public:
	//StringLinkedListNode():str(),lineFoundFrom(0),link(NULL){}
	StringLinkedListNode() :str(), next(NULL), prev(NULL){}
	explicit StringLinkedListNode(String const& srcString) : str(srcString), next(NULL), prev(NULL){}
	explicit StringLinkedListNode(String const& srcString, StringLinkedListNode* linkTo) : str(srcString), next(linkTo){}
	~StringLinkedListNode(){}

protected:
	//void setLine(int line){ lineFoundFrom = line; }
	void setString(String const& srcString){ str = srcString; }

};


class StringLinkedList
{
protected:
	//Data field
	int size; //count the nodes

	//Link field
	//StringLinkedListNode headerNode;
	StringLinkedListNode* head;
	StringLinkedListNode* tail;

public:
	StringLinkedList() : head(NULL), tail(NULL), size(0){}
	~StringLinkedList();

	bool isEmpty(){ return(head == NULL); };
	int getSize(){ return size; }
	void append(String const& srcString); //add at last
	int remove(String const& keyString); //TODO //return remove result in int value
	int remove(StringLinkedListNode*& pTargetNode); //if successful, assign pTargetNode to NULL
	//void removeAll(const String srcString); //TODO
	StringLinkedListNode* search(String const& keyString);
	//StringLinkedListNode* searchAll(const String srcString); //TODO

private:
	//StringLinkedList(StringLinkedList const& other):head(NULL),tail(NULL),size(0){}
};

StringLinkedList::~StringLinkedList()
{
	StringLinkedListNode *pNextNode = NULL;
	while (head)
	{
		pNextNode = head->next;
		head->next = NULL;
		delete head;
		head = pNextNode;
	}
}

void StringLinkedList::append(String const& srcString)
{
	StringLinkedListNode *pNewNode = NULL;
	if (!head) //empty list
	{
		pNewNode = new StringLinkedListNode(srcString, NULL);
		head = pNewNode;
		tail = pNewNode;
		return;
	}
	pNewNode = new StringLinkedListNode(srcString);
	tail->next = pNewNode;
	pNewNode->next = tail;
}

int StringLinkedList::remove(String const& keyString)
{
	StringLinkedListNode *pTargetNode = NULL;
	if (!head)
		return -1;

	//TODO
	if (head == tail)
	{

	}
}

int StringLinkedList::remove(StringLinkedListNode*& pTargetNode)
{
	if (!pTargetNode)
		return -1;
	if (pTargetNode == head)
	{

	}
	/*if ()
	{

	}*/


	return 0;
}

//void removeAll(const String srcString)
//{
//
//}

StringLinkedListNode* StringLinkedList::search(String const& keyString)
{
	StringLinkedListNode *pTargetNode = head;
	while (pTargetNode)
	{
		if (pTargetNode->str == keyString)
			break;
		pTargetNode = pTargetNode->next;
	}
	return pTargetNode;
}

//StringLinkedListNode* searchAll(const String srcString)
//{
//
//}



#pragma pack(push,1)
class StringHashCode
{
	friend class StringHashTableBucket;
	friend class StringHashTable;
private:
	//Assumption : the string is made of at least 2 or more wide characters
	char firstCharacter[2]; //the pure value of the first character(wide string)(this variable doesn't need '\0')
	unsigned char len; //string length
	char lastCharacter[2]; //the pure value of the last character(wide string)(this variable doesnt' need '\0')

private:
	//Cannot use, create or modify its value outside (except my self-defined classes)
	//which means, only uses hash codes internally
	StringHashCode();
	StringHashCode(StringHashCode const& other);
	StringHashCode(String const& srcString);
	StringHashCode getHashCode(String const& str);
};
#pragma pack(pop)

StringHashCode::StringHashCode(StringHashCode const& other)
{
	
	memcpy(this, &other, sizeof(StringHashCode));
}

StringHashCode::StringHashCode()
{
	len = 0;
	memcpy(firstCharacter, 0, 2 * sizeof(char));
	memcpy(lastCharacter, 0, 2 * sizeof(char));
}

StringHashCode::StringHashCode(String const& srcString)
{
	len = srcString.getTotalLength();
	memcpy(firstCharacter, &srcString[1], 2 * sizeof(char));
	memcpy(lastCharacter, &srcString[len-1], 2 * sizeof(char));
}


StringHashCode StringHashCode::getHashCode(String const& str)
{
	firstCharacter[0] = str[1];
	firstCharacter[1] = str[2];
	len = str.getStringChunkLength();
	lastCharacter[0] = str[len-1];
	lastCharacter[1] = str[len];
	return *this;
}

class StringHashTableBucket
{
	friend class StringHashTable;
public:
	//Data field
	StringHashCode HashCode;
	//Link field (to prevent collision)
	StringLinkedList* link; //for reference only
public:
	StringHashTableBucket() : HashCode(), link(NULL){}
	StringHashTableBucket(StringHashCode const& newHashCode) :HashCode(newHashCode), link(NULL){}
	//setBucket
};

#define INITIAL_STRING_BUCKET_SIZE 
//512

class StringHashTable
{
public:
	StringHashTableBucket *bucket;
	int size; //count total number of buckets created

public:
	StringHashTable() : bucket(NULL), size(0){}
	StringHashTable(int const numBuckets) : bucket(new StringHashTableBucket[size]){}
	~StringHashTable(){ delete bucket; }

	void add(const String &str);
	void search(const String &str);
	void sort();//for future speed
private:
	//expand
};



void StringHashTable::add(const String &str)
{
	StringHashCode newHashCode(str);
	//bucket[size++] = 

}

void StringHashTable::search(const String &str)
{
	

}




#define TEST_ON


#define KEY_HTML_TAGS_TOTAL 4
//key HTML-tags of which the contents are needed to be parsed
String const* KEY_HTML_TAGS[] = {
	new String("headline-title"),
	new String("question-title"),
	new String("author"),
	new String("content"),
};

#define IGNORED_HTML_TAGS_TOTAL 2
//not important HTML-tags
String const* IGNORED_HTML_TAGS[] = {
	new String("p"),
	new String("/p"),
};

#define EXCEPTIONAL_HTML_TAGS_TOTAL 2
//non-paried HTML-tags (no </..>
String const* EXCEPTIONAL_HTML_TAGS[] = {
	new String("img"),
	new String("meta"),
	new String("link"),
};

String const* END_HTML_TAG = new String("html");

String const HTML_TAG_START_OPEN = String("<");
String const HTML_TAG_CLOSE = String(">");
String const HTML_TAG_END_START = String("</");

//Class ParseHTML
//Parsing HTML file module

#include <fstream>
#include <locale.h>

String strHTMLContents;

int saveHTMLInTXT(char const*const HTMLFileName, char const*const SRCFileName)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);
	std::ofstream fout;
	fout.imbue(china);

	fin.open(HTMLFileName, std::ios::in);
	if (!fin.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	fout.open(SRCFileName, std::ios::out | std::ios::trunc);
	if (!fout.is_open())
	{
		printf("File open error\n");
		return -1;
	}


	//test using my string class directly (my buffer len max is 100 so must beaware)
	int nRead = 0;
	const int MAX_BUFFER_LEN = 1000;//must be BUFFER_LEN > MAX_STRING_CHUNK_LEN //10000;
	char strBuffer[MAX_BUFFER_LEN + 1] = { '\0', };
	while (true)
	{
		fin.read(strBuffer, MAX_BUFFER_LEN);
		nRead = fin.gcount();
		if (nRead == 0)
			break;
		strHTMLContents.concat(strBuffer, nRead);
		fout.write(strBuffer, nRead);
	}
	//htmlFileContents.print();

	fin.close();
	fout.close();
}

String htmlKeyContents;

void parseHTML()
{
	bool bTag = false;
	bool bTagOpen = false;
	bool bImportantTag = false; //check if found important (key) tags
	String strHTMLTag;
	LinkedStack<String> stack;
	
	int n = strHTMLContents.getTotalLength();
	//while (strHTMLTag != (*END_HTML_TAG)) //tag!=html
	//{
	//	indexOf();

	//}


	//for (int i = 1; i <= n;i++)
	//{
	//	ch = htmlKeyContents[i];
	//	if (ch == '<')
	//	{
	//		bTag = true;
	//		bTagOpen = true;


	//		//bImportantTag = false;
	//		continue;
	//	}
	//	else if (ch == '>')
	//	{
	//		bTag = false;


	//		bImportantTag = false;

	//		for (int j = 0; j < NOT_IMPORTANT_HTML_TAGS_TOTAL; j++)
	//		{
	//			if (htmlTag == (*NOT_IMPORTANT_HTML_TAGS[j]))
	//			{
	//				bFoundnotImportantTag = true;
	//				break;
	//			}
	//		}
	//		if (bFoundnotImportantTag)
	//		{
	//			htmlTag.clear();
	//			continue;
	//		}
	//		//check if it includes one of keyHTMLTags
	//		for (int j = 0; j < KEY_HTML_TAGS_TOTAL; j++)
	//		{
	//			if (htmlTag.indexOf(*KEY_HTML_TAGS[j], 0)>0)
	//				bKeyContents = true;
	//		}

	//		htmlTag.print(); //TODO
	//		htmlTag.clear();
	//		continue;
	//	}

	//	if (bTag)
	//		strHTMLTag.append(ch);
	//	else
	//	{
	//		if (bKeyContents)
	//		{
	//			htmlKeyContents.append(ch);
	//		}
	//	}
	//}
}

int saveParsedHTMLInTXT(char const*const TXTFileName) //add para : String *strKeyContents
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);
	std::ofstream fout;
	fout.imbue(china);

	fout.open(TXTFileName, std::ios::out | std::ios::trunc);
	if (!fout.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	int nStringChunkLen = 0;
	String *pCurrStr = &htmlKeyContents, *pNextStr = NULL;
	char *p=NULL;
	do
	{
		p = pCurrStr->peekStringToChar(pNextStr);
		nStringChunkLen = pCurrStr->getStringChunkLength();
		fout.write(p, nStringChunkLen);
		pCurrStr = pNextStr;
	} while (pNextStr);

	fin.close();
	fout.close();

	return 0;
}

#ifdef TEST_ON
#include <Windows.h>
#endif


int test1()
{
	//test
	//1.String creater

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
	Element<String> element;
	int stackResult = 0;
	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n", stackResult);

	printf("push[01]\n");
	element = myString01;
	stack.push(element);
	element = stack.peek();
	element.get().print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("push[02]\n");
	element = myString02;
	stack.push(element);
	element = stack.peek();
	element.get().print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("push[03]\n");
	element = myString03;
	stack.push(element);
	element = stack.peek();
	element.get().print(); printf("\n");
	printf("size : %d\n", stack.getSize());


	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n", stackResult);
	printf("\n");

	printf("pop[03]\n");
	element = stack.pop();
	element.get().print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("pop[02]\n");
	element = stack.pop();
	element.get().print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	printf("pop[01]\n");
	element = stack.pop();
	element.get().print(); printf("\n");
	printf("size : %d\n", stack.getSize());

	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n", stackResult);

	return 0;
}

int test4()
{
	String myString01("ABCDE12345");
	String myString02("12345");
	String myString03("345");
	//String myString04("");

	int index = 1;
	index = myString01.indexOf(myString02, 1); //6
	printf("%d ", index);
	index = myString01.indexOf(myString02, 5); //6
	printf("%d ", index);
	index = myString01.indexOf(myString03, 1); //8
	printf("%d ", index);
	index = myString01.indexOf(myString03, 5); //8
	printf("%d ", index);

	return 0;
}

int testSaveHTMLInTXT(char const*const HTMLFileName, char const*const TXTFileName)
{
	int result = 0;
	result = saveHTMLInTXT("0001.html", "0001.txt");
	//result = saveHTMLFileInTXT("001.txt", "0001.txt");
	//result = readHTMLFile("\\input\\0001.html");

	return result;
}

int testParseHTML()
{
	parseHTML();

	return 0;
}

int testSavePasedHTMLInTXT(char const*const TXTFileName)
{
	saveParsedHTMLInTXT(TXTFileName);

	return 0;
}



//load dictionary (ciku)
int loadDictionary(char const*const DICFileName)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);
	std::ofstream fout;
	fout.imbue(china);

	fin.open(DICFileName, std::ios::in);
	if (!fin.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	//for test
	fout.open("myDictionary.dic", std::ios::out | std::ios::trunc);
	if (!fout.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	int nRead = 0;
	const int MAX_BUFFER_LEN = 1000;//must be BUFFER_LEN > MAX_STRING_CHUNK_LEN //10000;
	char strBuffer[MAX_BUFFER_LEN + 1] = { '\0', };
	int nMax = 0;

	//Uses HashTable for more oragnized and faster search of strings
	//and the HashTable uses StringLinkedLists internally
	//cf> independent usage of StringLinkedList is also no prob

	String newString;
	//StringLinkedList StringList;

	const int STRING_HASH_TABLE_SIZE = 1024;
	StringHashTable stringHashTable(STRING_HASH_TABLE_SIZE);
	
	//printf("%d\n", sizeof(StringHashCode));

	while (true)
	{
		fin.getline(strBuffer, MAX_STRING_CHUNK_LEN); //100
		nRead = (int)fin.gcount(); //return std::streamsize (== long long)

		//printf("%d \n",nRead);
		if (nRead == 0)
			break;

		
		newString = strBuffer;

		nMax = (nRead > nMax) ? nRead : nMax;
		//if (nMax == 49)
			//break;

		stringHashTable.add(newString);

		//strHTMLContents.concat(strBuffer, nRead);
		//fout.write(strBuffer, nRead);
	}
	printf("MaxLen : %d\n",nMax);
	//htmlFileContents.print();
	
	fin.close();
	fout.close();
}





int main()
{
	//test1();
	//test2();
	//test3();
	//test5();
	char *filenameHTML = "0001.html";
	char *sourceHTML = "0001.src";
	char *parsedHTML = "0001.info";
	
	char *m = "dictionary.dic";
	//saveHTMLInTXT(filenameHTML,sourceHTML);
	//parseHTML();
	//saveParsedHTMLInTXT(parsedHTML);

	loadDictionary(m);

	return 0;
}