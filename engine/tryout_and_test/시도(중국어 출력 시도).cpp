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
		int lineFoundFrom;
	};
	StringLinkedListNode *link;
	
public:
	StringLinkedListNode():str(),lineFoundFrom(0),link(NULL){}

protected:
	void setLine(int line){ lineFoundFrom = line; }
	void setString(String const& srcString){ str=srcString; }
};

class StringLinkedList
{
protected:
	StringLinkedListNode headerNode;
	int size; //count the nodes

public:
	StringLinkedList();
	~StringLinkedList();
	int getSize(){ return size; }

	void append(); //add at last
	void remove(const String keyString);
	void removeAll(const String srcString);
	StringLinkedListNode* search(const String keyString);
	//StringLinkedListNode* searchAll(const String srcString)
};

StringLinkedList::StringLinkedList()
{

}

StringLinkedList::~StringLinkedList()
{
	
}

void append()
{

}

void remove(const String keyString)
{

}

//void removeAll(const String srcString)
//{
//
//}

StringLinkedListNode* search(const String keyString)
{
	//TODO
	return NULL;
}

//StringLinkedListNode* searchAll(const String srcString)

//#define TEST_ON




//Class ParseHTML
//Parsing HTML file module

#include <fstream>


int parseHTML(wchar_t const*const filename)
{
	String htmlFileContents;
	std::wifstream wfin;
	wfin.open(filename,std::ios::in);
	if (!wfin.is_open())
	{
		printf("File open error\n");
		return -1;
	}
	
	int nRead = 0;
	const int MAX_BUFFER_LEN = 1000;
	wchar_t wstrBuffer[MAX_BUFFER_LEN + 1] = { '\0', };

	String stringBuffer;
	while (true)
	{
		wfin.read(wstrBuffer, MAX_BUFFER_LEN);
		nRead = wfin.gcount();
		if (nRead == 0)
			break;
		stringBuffer = wstrBuffer;
		htmlFileContents.concat(stringBuffer);
	}
	htmlFileContents.print();
	

	/*char *p = "ABCDEFG";
	wchar_t q[100];
	convertCharToMultibyte(q, p,7);
	q[7] = '\n';
	printf("%ls",q);*/
	
	//std::wofstream wfout;
	//wfout.imbue
	return 0;
}

#ifdef TEST_ON
#include <Windows.h>
#endif


int test1()
{
	//test
	//1.String creater

	wchar_t *Str01 = L"ABC"; //3
	wchar_t *Str02 = L"01234567890123456789012345678901234567890123456789"
		L"01234567890123456789012345678901234567890123456789"; //100
	wchar_t *Str03 = L"01234567890123456789012345678901234567890123456789"
		L"012345678901234567890123456789012345678901234567890"; //101
	wchar_t *Str04 = L""; //0
	wchar_t *Str05 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"; //200
	wchar_t Str06[100] = {}; //0
	wchar_t *Str07 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"012345678901234567890123456789012345678901234567890"; //201
	String myString01;

	myString01 = Str01;
	printf("[01]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	myString01 = Str02;
	printf("[02]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	myString01 = Str03;
	printf("[03]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	myString01 = Str04;
	printf("[04]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	myString01 = Str05;
	printf("[05]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	myString01 = Str06;
	printf("[06]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	myString01 = Str07;
	printf("[07]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());

	String myString02 = myString01;
	printf("[10]"); myString02.print(); printf("\n");
	printf("%u\n", myString02.getLength());

	return 0;
}

int test2()
{
	//test
	//1.String creater
	//2.String concat

	wchar_t *Str01 = L"ABC"; //3
	wchar_t *Str02 = L"01234567890123456789012345678901234567890123456789"
		L"01234567890123456789012345678901234567890123456789"; //100
	wchar_t *Str03 = L"01234567890123456789012345678901234567890123456789"
		L"012345678901234567890123456789012345678901234567890"; //101
	wchar_t *Str04 = L""; //0
	wchar_t *Str05 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"; //200
	wchar_t *Str06 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"012345678901234567890123456789012345678901234567890"; //201
	String myString01(Str01);
	String myString02(Str02);
	String myString03(Str03);
	String myString04(Str04);
	String myString05(Str05);
	String myString06(Str06);

	printf("[01]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());
	printf("[02]"); myString02.print(); printf("\n");
	printf("%u\n", myString02.getLength());
	printf("[03]"); myString03.print(); printf("\n");
	printf("%u\n", myString03.getLength());
	printf("[04]"); myString04.print(); printf("\n");
	printf("%u\n", myString04.getLength());
	printf("[05]"); myString05.print(); printf("\n");
	printf("%u\n", myString05.getLength());
	printf("[06]"); myString06.print(); printf("\n");
	printf("%u\n", myString06.getLength());

	myString01.concat(myString02);
	printf("[10]"); myString01.print(); printf("\n");
	printf("%u\n", myString01.getLength());

	myString03.concat(myString04);
	printf("[11]"); myString03.print(); printf("\n");
	printf("%u\n", myString03.getLength());

	myString05.concat(myString06);
	printf("[12]"); myString05.print(); printf("\n");
	printf("%u\n", myString05.getLength());

	return 0;
}

int test3()
{
	//test
	//1.LinkedStack

	wchar_t *Str01 = L"ABC"; //3
	wchar_t *Str02 = L"01234567890123456789012345678901234567890123456789"
		L"01234567890123456789012345678901234567890123456789"; //100
	wchar_t *Str03 = L"01234567890123456789012345678901234567890123456789"
		L"012345678901234567890123456789012345678901234567890"; //101
	wchar_t *Str04 = L""; //0
	wchar_t *Str05 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"; //200
	wchar_t *Str06 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"012345678901234567890123456789012345678901234567890"; //201
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

	

	LinkedStack stack;
	Element element;
	int stackResult = 0;
	stackResult = stack.isEmpty();
	printf("isEmpty Stack? : %d\n",stackResult);

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

#include <locale.h>

int test4()
{
	//std::locale china("zh_CN.UTF-8");
	std::locale china("chs");
	std::wcout.imbue(china);

	int result = 0;
	
	//result = parseHTML(L"0001.html");
	//result = parseHTML("\\input\\0001.html");
	
	wchar_t filename[FILENAME_MAX] = L"我是韩昇范";
	std::wcout << filename;

	//std::wstring wstr = L"我是韩昇范";
	//std::wcout << wstr.c_str();
	

	return result;
}

int test5()
{
//
//	// 현재 locale을 저장
//	//char *old_locale_tmp = setlocale(LC_ALL, NULL); // 임시 locale 문자열 주소 반환
//	//char *old_locale_saved = strdup(old_locale_tmp); // 반환받은 old locale 문자열 주소가 이후 setlocale 호출로 변경되지 않도록 별도로 메모리를 할당받아서 저장
//
//	setlocale(LC_ALL, "ch-CN");
//	// locale을 변경하고 필요한 작업을 수행
//	//setlocale(LC_ALL, new_locale);
//
//	// locale을 복구
//	//setlocale(LC_ALL, old_locale_saved);
//	//free(old_locale_saved);
//
//
//
//
//	//std::locale localeChina("zh_CN.UTF-8");
//	std::locale localeChina("ch-CN");
//	std::wcout.imbue(localeChina);

	//wcout.imbue(locale("kor"));
	//wifstream input_file("data.txt", ios_base::in);
	//input_file.imbue(locale("kor"));
	//wofstream output_file("output.txt", ios_base::out);
	//output_file.imbue(locale("kor"));

	//1.test locale
	//setlocale(LC_ALL,"Chinese");
	//setlocale(LC_ALL, NULL);
	//setlocale(LC_ALL, "CHINESE");
	//setlocale(LC_ALL, "zh-CN");
	std::wcout.imbue(std::locale("chn"));

	//std::wcout.imbue(std::locale("kor"));

	//_wsetlocale(LC_ALL, L"CHN");

	wchar_t filename[FILENAME_MAX] = L"我是韩昇范";
	printf("%ls",filename);

	return 0;
}

int main()
{
	//test1();
	//test2();
	//test3();
	test4();
	//test5();

	return 0;
}