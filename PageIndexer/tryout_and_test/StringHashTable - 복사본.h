#include "String.h"
#include "StringLinkedList.h"


#pragma pack(push,1)
class StringHashCode
{
	friend class StringHashTableBucket;
	friend class StringHashTable;
public:
	//Assumption : the string is made of only and at least 2 or more chinese characters
	char firstCharacter[3]; //the pure value of the first chinese character(this variable doesn't need '\0')
	//unsigned char len; //string length
	//char lastCharacter[2]; //the pure value of the last character(wide string)(this variable doesnt' need '\0')

public:
	//Cannot use, create or modify its value outside (except my self-defined classes)
	//which means, only uses hash codes internally
	StringHashCode();
	StringHashCode(StringHashCode const& other);
	StringHashCode(String const& srcString);
	StringHashCode const& setHashCode(String const& srcString);

	explicit operator int() const { return((int)firstCharacter[0] * (int)firstCharacter[1]); }
};
#pragma pack(pop)


class StringHashTableBucket
{
	friend class StringHashTable;
private:
	//Data field
	StringHashCode HashCode;
	//Link field (to prevent collision)
public:
	StringLinkedList* link; //for reference only
private:
	StringHashTableBucket() : HashCode(), link(NULL){}
	StringHashTableBucket(StringHashCode const& newHashCode) :HashCode(newHashCode), link(NULL){}
	//setBucket
};

#define INITIAL_STRING_BUCKET_SIZE 
//512

class StringHashTable
{
public:
	StringHashTableBucket *pBucket;
	int nMaxBuckets; //count total number of buckets created
public:
//private:
	int nCurBuckets; //count number of currently being used buckets


public:
	StringHashTable() : pBucket(NULL), nMaxBuckets(0), nCurBuckets(0){}
	StringHashTable(int const numBuckets);
	~StringHashTable(){ delete[] pBucket; }

	void add(String const& newString);
	bool search(String const& keyString) const;
	//void sort();//for future speed
private:
	void expand();
};
