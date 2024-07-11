#ifndef STRING_H
#define STRING_H

#include "StringChunk.h"

//writeFile()
//loadHTML()
//parseHTML()

#include <fstream>
#include <locale.h>


#pragma warning (disable:4018) //At getSubString()

//String class
//Kuai form
class String
{
public:
	char *str; //[MAX_STRING_CHUNK_SIZE + 2]
	//[0] : would count the string size
	//[MAX_STRING_CHUNK_SIZE + 1] : (the last character) would be assigned '\0' if needed (for compatibility with other types & functions)(and also for easy debuging)
	String *next;
	String *prev; //not really used.. but for faster search manipulation and index manipulation
	
public:
	String();
	explicit String(char const*const src);
	String(String const& other);
	~String();

	String const& operator =(char const ch);
	String const& operator =(char const*const src);
	String const& operator =(String const& other);
	//TODO : find faster(better) way
	char const& operator[](int const index) const;
	bool const operator==(String const& other) const;
	bool const operator!=(String const& other) const;

	//return the current string's stringChunk's length
	unsigned char getStringChunkLength() const{ return(::getLength(str)); };
	//return the total string length
	unsigned int getTotalLength() const;
	bool isEmptyString() const { return (this->getTotalLength() == 0); }
	void print() const;
	
	void copyStringChunk(StringChunk const src);
	void concat(char const*const charString);
	//use nconcant when charString isn't null-terminated char string
	//(ex: charString is buffer that is read though fstream object)
	//has a bug very sometimes when becomes too large (maybe allocation fail)
	void nconcat(char const*const charString, int const len);
	void concat(String const& other);
	
	void append(char const ch);
	void clear();
	void trim(); //trim : delete the dangling strings that not needed

	int indexOf(String const& subString, int pos) const;
	//int indexOf(String const& subString, int pos); //TODO(KMP)
	String const& getSubstring(int pos, int len) const; //TODO

	//return current string chunk to be peeked
	//and input the address of next dangling string at stringNext output pointer
	char* peekStringToCharPointer(String const*& stringNext) const;
	//return current string chunk to be peeked
	char* peekStringToCharPointer() const;
	

	//String *append(String *); //TODO
	//support successive appending using its internal String pointer
	//search to be appended pos, and return the the String pointer which appended at

	//readFile() needs MAX_BUFFER_LEN
	//must be (BUFFER_LEN > MAX_STRING_CHUNK_LEN)
#define MAX_BUFFER_LEN 10000
	int readFile(String const& filename);
	int writeFile(String const& filename) const;

	//Parsing HTML file module definition
#define PARSEHTML
public:
	bool isKeyHTMLTag() const;
	bool isKeyHTMLTag(int& index) const;
	bool isNonPairedHTMLTag() const;

	//"this" string object (srcString) --parse--> dstString
	void parseHTML(String &dstString) const;
};

#endif