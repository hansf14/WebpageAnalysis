#ifndef STRINGCHUNK_H
#define STRINGCHUNK_H

#include <iostream>
#include <stdlib.h>
#include <memory.h>

//Every string chunk's max size
//must be <=255
#define MAX_STRING_CHUNK_LEN 100
typedef char* StringChunk;

extern StringChunk createStringChunk();

extern StringChunk createStringChunkCopy(StringChunk const srcStringChunk);

extern unsigned char getLength(StringChunk const stringChunk);

extern int setLength(StringChunk stringChunk, unsigned char const newLen);

//supports delta <0
extern int increaseLengthBy(StringChunk stringChunk, unsigned char const delta);

extern bool isFullStringChunk(StringChunk const stringChunk);

extern bool isEmptyStringChunk(StringChunk const stringChunk);

#endif