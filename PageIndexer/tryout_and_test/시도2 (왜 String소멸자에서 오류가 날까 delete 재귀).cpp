#include <iostream>

//String class (Str)
//Upgrade : template
//Upgrade : use unsigned??

//Kuai form
//Every string chunk's max size.
//If the character is wchar_t, then "must" be < 255
#define MAX_STRING_CHUNK_LEN 100

int increaseLengthBy(wchar_t*const wstr, unsigned short int const delta)
{
	if (((unsigned short int)wstr[0] + delta) > MAX_STRING_CHUNK_LEN)
		return -1;
	wstr[0] += delta;
	return 0;
}

int setLength(wchar_t*const wstr, unsigned short int const newLen)
{
	if (newLen > MAX_STRING_CHUNK_LEN)
		return -1;
	wstr[0] = newLen;
	return 0;
}

unsigned short int getLength(wchar_t const*const wstr)
{
	return (unsigned short int)wstr[0];
}

wchar_t* createStringChunk()
{
	wchar_t* stringChunk = (wchar_t*)malloc((MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
	return stringChunk;
}


class String
{
private:
	wchar_t *wstr; //[MAX_STRING_CHUNK_SIZE + 1]
	//[0] : would count the string size
	String *next;

public:
	String();
	~String();
	//String(char const*const){}
	String(wchar_t const*const);
	String(String const& other);

	String& operator =(wchar_t const*const src);
	String& operator =(String const& other);
	//int getIndexOf(){}
	//String getSubstring(){}

	void concat(String const& other);
	unsigned int getLength() const;
	void print() const;

	//return string length (logically equals to 2-byte integer value)
};

String::~String()
{
	delete next;
	if (wstr)
		free(wstr);
	printf("%p : deleted \n",this);
	/*if (this != NULL)
	{
		next = NULL;
		free(wstr);
	}*/
}

unsigned int String::getLength() const
{
	String const* pstr = this;
	unsigned int len = 0;
	while (pstr)
	{
		len += ::getLength(pstr->wstr);
		pstr = pstr->next;
	}
	return len;
}

void String::print() const
{
	String const* pstr = this;
	while (pstr)
	{
		if (::getLength(pstr->wstr) != 0)
			printf("%100ls", &pstr->wstr[1]);
		pstr = pstr->next;
	}
}


wchar_t* createStringChunkCopy(wchar_t const*const stringChunk)
{
	wchar_t* newStringChunk = createStringChunk();
	memcpy(newStringChunk, stringChunk, (MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
	return newStringChunk;
}

String& String::operator =(wchar_t const*const src)
{
	int srcLen = wcslen(src);
	//TODO : exception
	wchar_t const* p = src;

	int n = srcLen / MAX_STRING_CHUNK_LEN;
	int remain = srcLen % MAX_STRING_CHUNK_LEN;

	String *pstr = this; //target string
	if (srcLen > MAX_STRING_CHUNK_LEN)
	{
		String *prevStr = this; //pevious target string
		while (n--)
		{
			//assign string chunk
			if (pstr) //if the number of string chunks is enough for now
			{
				setLength(pstr->wstr, MAX_STRING_CHUNK_LEN);
				memcpy(&pstr->wstr[1], p, (MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
				p += MAX_STRING_CHUNK_LEN;
			}
			else //need more string chunks to get assigned
			{
				pstr = new String();
				prevStr->next = pstr;
				pstr->next = NULL;
				setLength(pstr->wstr, MAX_STRING_CHUNK_LEN);
				memcpy(&pstr->wstr[1], p, (MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
				p += MAX_STRING_CHUNK_LEN;
			}
			prevStr = pstr;
			pstr = pstr->next;
		}

		if (remain == 0)
		{
			if (pstr)
			{
				delete pstr;
				pstr->next = NULL;
			}
			return *this;
		}
		else
		{
			if (!pstr)
			{
				pstr = new String();
				prevStr->next = pstr;
				pstr->next = NULL;
				prevStr = pstr;
			}
		}
	}
	else //"this" string only needs one stringChunk
	{
		if (pstr->next) //buf if already has dangling stringChunks, then trim it
		{
			delete pstr->next;
			pstr->next = NULL;
		}
		remain = srcLen; //include when srcLen == MAX_STRING_CHUNK_LEN
	}

	//assign string chunk
	setLength(pstr->wstr, remain);
	memcpy(&pstr->wstr[1], p, remain*sizeof(wchar_t));

	return *this;
}

String::String(String const& other)
{
	String* pstr=this;
	String const* psrc = &other;

	pstr->next = NULL;
	pstr->wstr = createStringChunkCopy(psrc->wstr);
	psrc = psrc->next;
	while (psrc)
	{
		String *pNewString = new String();
		pstr->next = pNewString;
		pNewString->next = NULL;
		pstr = pNewString;
		pNewString->wstr = createStringChunkCopy(other.wstr);
		psrc = psrc->next;
	}
}

String& String::operator =(String const& other)
{
	String newString(other);
	
	//TODO
	return newString;
}

void String::concat(String const& other)
{
	String *pstr = this;
	while (pstr->next)
		pstr = pstr->next;
	if (other.getLength() == 0)
		;
}

String::String(wchar_t const*const src)
{
	int srcLen = wcslen(src);
	//TODO : exception
	wchar_t const* p = src;

	int n = srcLen / MAX_STRING_CHUNK_LEN;
	int remain = srcLen % MAX_STRING_CHUNK_LEN;

	String *pstr = this;
	if (srcLen >= MAX_STRING_CHUNK_LEN)
	{
		setLength(pstr->wstr, MAX_STRING_CHUNK_LEN);
		memcpy(&pstr->wstr[1], p, (MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
		p += MAX_STRING_CHUNK_LEN;
		while (--n)
		{
			pstr = pstr->next;
			pstr = new String();
			setLength(pstr->wstr, MAX_STRING_CHUNK_LEN);
			memcpy(&pstr->wstr[1], p, (MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
			p += MAX_STRING_CHUNK_LEN;
		}
		if (remain == 0)
			return;
		else
		{
			pstr = pstr->next;
			pstr = new String();
		}
	}

	if (remain != 0)
	{
		setLength(pstr->wstr, remain);
		memcpy(&pstr->wstr[1], p, remain*sizeof(wchar_t));
	}
	else
	{
		memset(pstr->wstr, 0, (MAX_STRING_CHUNK_LEN + 1)* sizeof(wchar_t));
	}
}


String::String()
{
	wstr = createStringChunk();
	next = NULL;
}


//class front declaration;
//class String;
//class LinkedStack;

//Element Class
//1.For generic usage in other data stures and get away with structural dependency
//2.In order to cope with possible change in the future

//template <typename T>
//class Element
//{
//protected:
//	T data;
//
//public:
//	Element(){}
//	~Element(){}
//
//protected:
//	void set(T a_data):T(a_data){}
//	T &get() const { return data; }
//};

class Element
{
protected:
	String data;

public:
	Element() : data(){}
	Element(String const& aData) : data(aData){}
	~Element(){}

protected:
	void set(String const& aData){ data = aData; }
	const String& get() const { return data; }
};



//LinkedStackNode Class
//Node for LinkedStack Class
//template <typename T>

class LinkedStackNode
{
	friend class LinkedStack;
protected:
	//Element<T> element;
	Element element;
	LinkedStackNode *link;

public:
	LinkedStackNode() :element(), link(NULL){}
	~LinkedStackNode(){}
	void setElement(const Element& a_element){ element = a_element; }
private:
	void setLink(LinkedStackNode* pNode){ link = pNode; }
};


//template <typename T>
class LinkedStack
{
protected:
	LinkedStackNode *top;

public:
	//creator
	LinkedStack():top(NULL){}

	//destructor
	~LinkedStack();

	//member functions
	int isEmpty() const { return(top==NULL); }
	int push(Element const& a_element);
	Element pop();
	Element& peek() const;

};

//template <typename T>

int LinkedStack::push(Element const& a_element)
{
	LinkedStackNode *newNode = new LinkedStackNode();
	if (!newNode)
		return -1;
	newNode->setElement(a_element);

	newNode->link = top;
	top = top->link;
	return 0;
}

Element LinkedStack::pop()
{
	if (isEmpty()) //TODO : EXCEPTION
		;
	LinkedStackNode *targetNode = top;
	Element e = targetNode->element;
	top = top->link;
	free(targetNode);
	return e;
}

Element& LinkedStack::peek() const
{
	if (isEmpty()) //TODO : EXCEPTION
		;
	return (top->element);
}


class StringLinkedList
{
protected:
	String* pString;
	
	
};

#define TEST_ON

#ifdef TEST_ON
#include <Windows.h>
#endif



int test1()
{
	wchar_t *Str01 = L"ABC";
	wchar_t *Str02 = L"01234567890123456789012345678901234567890123456789"
		L"01234567890123456789012345678901234567890123456789";
	wchar_t *Str03 = L"01234567890123456789012345678901234567890123456789"
		L"012345678901234567890123456789012345678901234567890";
	wchar_t *Str04 = L"";
	wchar_t Str05[100] = {};
	wchar_t *Str06 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789"\
		L"012345678901234567890123456789012345678901234567890";
	String myString01;

	myString01 = Str01;
	printf("[01]"); myString01.print(); printf("\n");
	printf("%u\n",myString01.getLength());
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

	/*String myString02 = myString01;
	printf("[10]"); myString02.print(); printf("\n");
	printf("%u\n", myString02.getLength());*/

	return 0;
}

int test2()
{

	return 0;
}

class C
{
	int m;
public:
	C():m(0){}
	~C(){ printf("DEL\n"); }
};

int main()
{
	test1();


	return 0;
}