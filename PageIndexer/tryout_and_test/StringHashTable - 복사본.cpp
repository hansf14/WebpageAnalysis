#include "StringHashTable.h"

////////////////////////////////////////////////////////////
//StringHashCode member functions

StringHashCode::StringHashCode(StringHashCode const& other)
{
	memcpy(this, &other, sizeof(StringHashCode));
}

StringHashCode::StringHashCode()
{
	memset(firstCharacter, 0, 2 * sizeof(char));
}

StringHashCode::StringHashCode(String const& srcString)
{
	firstCharacter[0] = srcString[1];
	firstCharacter[1] = srcString[2];
}

StringHashCode const& StringHashCode::setHashCode(String const& srcString)
{
	firstCharacter[0] = srcString[1];
	firstCharacter[1] = srcString[2];
	return *this;
}


////////////////////////////////////////////////////////////
//StringHashTable member functions


StringHashTable::StringHashTable(int const numBuckets)
{
	pBucket = new StringHashTableBucket[numBuckets];
	nMaxBuckets = numBuckets;
	nCurBuckets = 0;
}

void StringHashTable::add(String const& newString)
{
	StringHashCode newHashCode(newString);
	int nNewHashCode = int(newHashCode);

	//find available location to be added (linear search)
	//check if already exist in the table with this code
	int i = 0; //to be inserted address(index)
	for (i = 0; i < nCurBuckets; i++)
	{
		int nOldHashCode = int(pBucket[i].HashCode);
		if (nNewHashCode == nOldHashCode)
			break;
	}
	if (i == nMaxBuckets) //if the table is already full to add this
		this->expand(); //then, expand


	if (!(pBucket[i].link)) //the new code
	{
		//append in the string list
		StringLinkedList *newStringList = new StringLinkedList();
		newStringList->append(newString);
		pBucket[i].link = newStringList;

		nCurBuckets++; //increase the current bucket count
		pBucket[i].HashCode = newHashCode; //set the bucket's keycode(and it stores hashcode as keycode)
	}
	else //already exists such code
	{
		pBucket[i].link->append(newString);
	}
}

void StringHashTable::expand()
{
	//because there's no supported "realloc" for "new"ed obejcts
	int nNewMaxBuckets = 2 * (this->nMaxBuckets);
	StringHashTableBucket *pNewBucket = new StringHashTableBucket[nNewMaxBuckets]; //relocated
	memcpy(pNewBucket, this->pBucket, (this->nMaxBuckets)*sizeof(StringHashTableBucket));
	delete[] pBucket;
	this->pBucket = pNewBucket;
	this->nMaxBuckets = nNewMaxBuckets;
}

bool StringHashTable::search(const String& keyString) const
{
	StringHashCode keyHashCode(keyString);
	int nKeyHashCode = int(keyHashCode);

	//find available location to be added (linear search)
	//check if already exist in the table with this code
	int i = 0; //to be inserted address(index)
	for (i = 0; i < nCurBuckets; i++)
	{
		int nOldHashCode = int(pBucket[i].HashCode);
		if (nKeyHashCode == nOldHashCode)
		{
			if (pBucket[i].link->search(keyString) != NULL)
				return true;
			else
				return false;
		}
	}

	return false;
}
