#include <iostream>


//String class (Str)
//Upgrade : template
//Upgrade : use unsigned??

//Kuai form
//Every string chunk's max size.
//If the character is wchar_t, then "must" be < 255
#define MAX_STRING_CHUNK_SIZE 100


class String
{
private:
	wchar_t *lpwstr; //[MAX_STRING_CHUNK_SIZE + 1]
	//[0] - HIWORD : would count the string size
	//[1] - LOWORD : would count the number of references used in other different types of objects
	//ref counter especially being used in StringLinkedList
	wchar_t *next;

public:
	String();
	//String(char const*const){}
	String(wchar_t const*const);
	//String(String const& other){ wch = other; }

	String const& operator =(wchar_t const*const lpcwstr);
	//String const& operator =(String const& other){}
	//int getIndexOf(){}
	//String getSubstring(){}
	//String concat(String const& other);

	unsigned char getLength();
	unsigned char* getLengthAddress();
	unsigned char getRefCount();
	unsigned char* getRefCountAddress();

private:
	int increaseLengthBy(unsigned char const delta);
	int setLength(unsigned char const newLen);
	//wchar_t* expandFromOuter(wchar_t const*const );
	wchar_t* expand(wchar_t const*const src = NULL, int const srcLen = 0);
};

String::String(wchar_t const*const)
{

}

int String::increaseLengthBy(unsigned char const delta)
{
	if ((getLength() + delta) > MAX_STRING_CHUNK_SIZE)
		return -1;
	*getLengthAddress() += delta;
	return 0;
}

int String::setLength(unsigned char const newLen)
{
	if (newLen > MAX_STRING_CHUNK_SIZE)
		return -1;
	unsigned char *addrLen = getLengthAddress();
	(*addrLen) += newLen;
	return 0;
}

unsigned char* String::getLengthAddress()
{
	return ((unsigned char*)(&lpwstr[0]));
}
unsigned char* String::getRefCountAddress()
{
	return ((unsigned char*)(&lpwstr[0]) + 1);
}


unsigned char String::getLength()
{
	return ((unsigned char(lpwstr[0] >> 8) & 0xffff));
}

unsigned char String::getRefCount()
{
	return (unsigned char(lpwstr[0] & 0xffff));
}



wchar_t* String::expand(wchar_t const*const lpcwstr, int const srcLen)
{
	wchar_t* newlpwstr = (wchar_t*)malloc((MAX_STRING_CHUNK_SIZE + 1)* sizeof(wchar_t));
	if (lpcwstr)
	{
		increaseLengthBy(srcLen);
		memcpy(&newlpwstr[1], lpcwstr, MAX_STRING_CHUNK_SIZE);
	}
	//TODO**********
	//Exception
	return newlpwstr;
}

String::String()
{
	lpwstr = (wchar_t*)calloc(MAX_STRING_CHUNK_SIZE + 1, sizeof(wchar_t));
	next = NULL;
}

String const& String::operator =(wchar_t const*const lpcwstr)
{
	int dstLen = getLength();
	int srcLen = wcslen(lpcwstr);
	//TODO : exception
	wchar_t const* src = lpcwstr;


	//int n = dstLen % MAX_STRING_CHUNK_SIZE;
	//int remain = len / MAX_STRING_CHUNK_SIZE;

	if (dstLen != MAX_STRING_CHUNK_SIZE) //not full
	{
		setLength(srcLen);
		printf("%d \n",getLength());
		memcpy(&lpwstr[dstLen + 1], src, MAX_STRING_CHUNK_SIZE - dstLen);
		src += srcLen;
	}
	while (src != &lpcwstr[srcLen])
	{
		next = expand();
	}

	return *this;
	//if (len>getLength())
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
	Element& pop();
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

Element& LinkedStack::pop()
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
	wchar_t *Str02 = L"01234567890123456789012345678901234567890123456789"\
		L"01234567890123456789012345678901234567890123456789";
	String myString;

	myString = Str01;
	myString = Str02;

	wchar_t str02[100] = {};

	return 0;
}

int main()
{
	test1();


	return 0;
}