#include "StringChunk.h"

StringChunk createStringChunk()
{
	char* stringChunk = (char*)malloc((MAX_STRING_CHUNK_LEN + 2) * sizeof(char));
	stringChunk[0] = 0;
	stringChunk[1] = '\0';
	return stringChunk;
}

StringChunk createStringChunkCopy(StringChunk const srcStringChunk)
{
	char* newStringChunk = createStringChunk();
	memcpy(newStringChunk, srcStringChunk, (MAX_STRING_CHUNK_LEN + 2) * sizeof(char));
	srcStringChunk[MAX_STRING_CHUNK_LEN + 1] = '\0';
	return newStringChunk;
}

unsigned char getLength(StringChunk const stringChunk)
{
	return (unsigned char)stringChunk[0];
}

int setLength(StringChunk stringChunk, unsigned char const newLen)
{
	if (newLen > MAX_STRING_CHUNK_LEN)
		return -1;
	stringChunk[0] = newLen;
	return 0;
}

int increaseLengthBy(StringChunk stringChunk, unsigned char const delta)
{
	if (delta > 0)
	{
		if (((unsigned char)stringChunk[0] + delta) > MAX_STRING_CHUNK_LEN)
			return -1;
	}
	else if (delta < 0)
	{
		if (((unsigned char)stringChunk[0] + delta) < 0)
			return -1;
	}
	stringChunk[0] += delta;
	return 0;
}

bool isFullStringChunk(StringChunk const stringChunk)
{
	return ((unsigned char)stringChunk[0] == MAX_STRING_CHUNK_LEN);
}

bool isEmptyStringChunk(StringChunk const stringChunk)
{
	return ((unsigned char)stringChunk[0] == 0);
}