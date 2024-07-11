#include "String.h"


String::String()
{
	str = createStringChunk();
	next = NULL;
	prev = NULL;
}

String::String(char const*const src)
{
	str = createStringChunk();
	next = NULL;
	prev = NULL;
	int srcLen = strlen(src);
	char const* p = src;

	int n = srcLen / MAX_STRING_CHUNK_LEN;
	int remain = srcLen % MAX_STRING_CHUNK_LEN;

	String *pstr = this; //target string
	if (srcLen > MAX_STRING_CHUNK_LEN)
	{
		//assign string chunk
		setLength(pstr->str, MAX_STRING_CHUNK_LEN);
		memcpy(&pstr->str[1], p, MAX_STRING_CHUNK_LEN* sizeof(char));
		pstr->str[MAX_STRING_CHUNK_LEN + 1] = '\0';
		p += MAX_STRING_CHUNK_LEN;
		while (--n)
		{
			String *pNewString = new String();
			pNewString->prev = pstr;
			pstr->next = pNewString;
			pstr = pNewString;
			setLength(pstr->str, MAX_STRING_CHUNK_LEN);
			memcpy(&pstr->str[1], p, MAX_STRING_CHUNK_LEN* sizeof(char));
			pstr->str[MAX_STRING_CHUNK_LEN + 1] = '\0';
			p += MAX_STRING_CHUNK_LEN;
		}
		if (remain == 0)
		{
			return;
		}
		else
		{
			String *pNewString = new String();
			pNewString->prev = pstr;
			pstr->next = pNewString;
			pstr = pNewString;
		}
	}
	else //"this" string only needs one stringChunk
	{
		remain = srcLen; //include when srcLen == MAX_STRING_CHUNK_LEN
	}

	//assign string chunk
	setLength(pstr->str, remain);
	memcpy(&pstr->str[1], p, remain*sizeof(char));
	pstr->str[remain + 1] = '\0';
}

String::String(String const& other)
{
	String* pstr = this;
	String const* psrc = &other;

	pstr->str = createStringChunkCopy(psrc->str); //create the copy of the current string chunk of "other" string
	pstr->next = NULL;
	pstr->prev = NULL;
	psrc = psrc->next;
	while (psrc) //if it has more string chunks to be copied ("other" string has dangling string chunks)
	{
		String *pNewString = new String();
		pNewString->prev = pstr;
		pNewString->copyStringChunk(psrc->str);
		pstr->next = pNewString;
		pstr = pNewString;
		psrc = psrc->next;
	}
}

//delete itself and recursive call to delete the dangling string chunks
String::~String()
{
	free(str);
	delete next;
	this->next = NULL;
}

/////////////////////////////////////////////////////////////////
//String operators

String const& String::operator =(char const ch)
{
	increaseLengthBy(this->str, 1);
	this->str[1] = ch;
	this->str[2] = '\0';

	return *this;
}

//src should be null terminated char string
//so, doesn't support single char assigning (ex: char ch='a'; String str = &ch; (X))
//single char assigning operator is already overloaded above
String const& String::operator =(char const*const src)
{
	int srcLen = strlen(src);
	char const* p = src;

	int n = srcLen / MAX_STRING_CHUNK_LEN;
	int remain = srcLen % MAX_STRING_CHUNK_LEN;

	String *pstr = this; //target string
	if (srcLen > MAX_STRING_CHUNK_LEN)
	{
		String *prevStr = this; //pevious target string
		while (n--) //copy each string chunk
		{
			//assign string chunk
			if (pstr) //if the number of string chunks is enough for now
			{
				setLength(pstr->str, MAX_STRING_CHUNK_LEN);
				memcpy(&pstr->str[1], p, MAX_STRING_CHUNK_LEN* sizeof(char));
				pstr->str[MAX_STRING_CHUNK_LEN + 1] = '\0';
				p += MAX_STRING_CHUNK_LEN;
			}
			else //need more string chunks to get assigned
			{
				pstr = new String();
				pstr->prev = prevStr;
				prevStr->next = pstr;

				setLength(pstr->str, MAX_STRING_CHUNK_LEN);
				memcpy(&pstr->str[1], p, MAX_STRING_CHUNK_LEN* sizeof(char));
				pstr->str[MAX_STRING_CHUNK_LEN + 1] = '\0';
				p += MAX_STRING_CHUNK_LEN;
			}
			prevStr = pstr;
			pstr = pstr->next;
		}
		if (remain == 0) //actually no more chars remained to be copied
		{
			if (pstr) //but if it has dangling string chunks, then delete them
			{
				prevStr->next = NULL;
				delete pstr; //deleting happens recursively in its destructor
			}
			return *this; //asigning is complete
			//the string may have dangling string chunks OR NULL already as default (in constructor or in above "new")
		}
		else //still remain more chars remained to be copied
		{
			if (!pstr) //and if it doesn't have any room(chunk) left to be copied, then create one
			{	//only one string chunk is okay for the after string chunk copy
				pstr = new String();
				pstr->prev = prevStr;
				prevStr->next = pstr;
			}//else it has one ore more dangling string chunks, and only one of them will be used (copy)
		}
	}
	else //"this" string only needs one stringChunk
	{
		if (pstr->next) //buf if already has dangling stringChunks, then trim it
		{
			delete pstr->next;
			pstr->next = NULL;
		}
		//remain = srcLen; //include when srcLen == MAX_STRING_CHUNK_LEN
	}

	//assign string chunk
	setLength(pstr->str, remain);
	memcpy(&pstr->str[1], p, remain*sizeof(char));
	pstr->str[remain + 1] = '\0';

	//the string may have dangling string chunks OR NULL already as default (in constructor or in above "new")
	return *this;
}

String const& String::operator =(String const& other)
{
	String* pstr = this; //target string to be assigned
	String const* psrc = &other;

	pstr->copyStringChunk(psrc->str); //just copy the current string chunk of "other" string
	String *prevStr = this;
	psrc = psrc->next;
	while (psrc) //if it has more string chunks to be copied ("other" string has dangling string chunks)
	{
		pstr = pstr->next;
		if (pstr)
		{
			pstr->copyStringChunk(psrc->str);
		}
		else
		{
			pstr = new String();
			pstr->prev = prevStr;
			prevStr->next = pstr;
			pstr->copyStringChunk(psrc->str);
		}
		prevStr = pstr;
		psrc = psrc->next;
	}
	pstr = pstr->next; //check needless dangling StringChunks if it has, then delete
	if (pstr)
	{
		prevStr->next = NULL;
		delete pstr;
	}
	return *this;
}

//Assumption : all string chunks are compact
char const& String::operator[](int const index) const
{
	int n = (index - 1) / MAX_STRING_CHUNK_LEN;
	int remain = (index - 1) % MAX_STRING_CHUNK_LEN;
	String const* pstr = this;
	while (n--)
		pstr = pstr->next; //go to the string chunk that the index locates
	return (pstr->str[remain + 1]);
}

//need to check if the current string chunk is empty
//need to check if the char pointer got to the end of current string chunk
//so, also need to check the length of current string chunk (not the total string length)
//Also, empty String & empty String considered same
bool const String::operator==(String const& other) const
{
	if (this->getTotalLength() != other.getTotalLength())
		return false;

	String const* pstr = this, *qstr = &other; //both are String const*
	char* p = &pstr->str[1], *q = &qstr->str[1];
	int lenThis = 0, lenOther = 0;
	bool bThisChecked = false, bOtherChecked = false; //check if empty
	//true : isn't empty
	//false : NULL or not checked yet

	while (true)
	{
		if (pstr)
		{
			//checking "this" string starts
			while (isEmptyStringChunk(pstr->str))
			{
				pstr = pstr->next;
				if (!pstr)
					break; //at the end of string
			}
			if (pstr && (bThisChecked == false))
			{
				p = &pstr->str[1];
				lenThis = pstr->getStringChunkLength();
				bThisChecked = true;
			}
		}
		//checking "this" string ends
		//case 1.not empty
		//case 2.not available (NULL)

		while (true)
		{
			//checking "other" starts
			if (qstr)
			{
				while (isEmptyStringChunk(qstr->str))
				{
					qstr = qstr->next;
					if (!qstr)
						break; //at the end of string
				}
				if (qstr && (bOtherChecked == false))
				{
					q = &qstr->str[1];
					lenOther = qstr->getStringChunkLength();
					bOtherChecked = true;
				}
			}
			//checking "other" ends
			//case 1.not empty
			//case 2.not available (NULL)

			if (!pstr && !qstr) //both total strings checking finished, but still in loop
				return true;
			else if (!pstr) //at the end of "this total string" (checking finished)
			{//qstr != NULL
				if (bOtherChecked == true) //qstr has remain
					return false;
			}
			else if (!qstr) //at the end of "other total string" (checking finished)
			{//pstr != NULL
				if (bThisChecked == true) //pstr has remain
					return false;
			}

			//now both are made of not empty strink chunks
			//actual compare
			while ((p <= &pstr->str[lenThis]) && (q <= &qstr->str[lenOther]))
			{
				if ((*p) != (*q))
					return false;
				p++; q++;
			}
			//at least one of them got out of its string chunk

			if (p > &pstr->str[lenThis] && (q <= &qstr->str[lenOther])) //have to check the next string chunk
			{//p is at the end of string chunk
				pstr = pstr->next;
				bThisChecked = false;
				break;
			}
			else if (q > &qstr->str[lenOther] && (p <= &pstr->str[lenThis])) //have to check the next string chunk
			{//q is at the end of string chunk
				qstr = qstr->next;
				bOtherChecked = false;
				continue;
			}
			else
			{//p,q both are at the end of string chunk
				pstr = pstr->next;
				qstr = qstr->next;
				bThisChecked = false;
				bOtherChecked = false;
				break;
			}
		}
	}

	return true;
}

bool const String::operator!=(String const& other) const
{
	return !(*this == other);
}

/////////////////////////////////////////////////////////////////

unsigned int String::getTotalLength() const
{
	String const* pstr = this;
	unsigned int len = 0;
	while (pstr)
	{
		len += ::getLength(pstr->str);
		pstr = pstr->next;
	}
	return len;
}

void String::print() const
{
	String const* pstr = this;
	int len = 0;
	while (pstr)
	{
		if ((len = ::getLength(pstr->str)) != 0)
		{
			pstr->str[1 + len] = '\0';
			printf("%s", &pstr->str[1]);
		}
		pstr = pstr->next;
	}
}

/////////////////////////////////////////////////////////////////

void String::copyStringChunk(StringChunk const src)
{
	memcpy(str, src, (MAX_STRING_CHUNK_LEN + 2)* sizeof(char));
	str[MAX_STRING_CHUNK_LEN + 1] = '\0';
}

//I think this one has a bug when....
//	char *exeFileRoot = "..";//"..\\input\\";
//char queryFileName[FILENAME_MAX] = "query.txt"; //(.txt)
//char resultFileName[FILENAME_MAX] = "result.txt"; //(.txt)
//
//String strQueryFileName(exeFileRoot);
//String strResultFileName(exeFileRoot);
//strQueryFileName.concat(queryFileName);
//strResultFileName.concat(resultFileName));
void String::concat(String const& other)
{
	String *pstr = this;
	while (pstr->next)
		pstr = pstr->next;

	if (::getLength(pstr->str) == 0)
		*pstr = other;
	else
	{
		String *newString = new String(other);
		newString->prev = pstr;
		pstr->next = newString;
	}
}

//charString should be null terminated char string
//so, doesn't support single char concat (ex: char ch='a'; String str; str.concat(&ch); (X))
//to use single char concat, use append() member function
void String::concat(char const*const charString)
{
	int len = strlen(charString);
	String *pstr = this;
	while (pstr->next)
		pstr = pstr->next;

	int thisChunkLen = 0;
	thisChunkLen = ::getLength(pstr->str);

	if ((thisChunkLen + len) <= MAX_STRING_CHUNK_LEN) //single string chunk is enough
	{
		increaseLengthBy(pstr->str, len);
		memcpy(str + 1 + thisChunkLen, charString, len*sizeof(char));
		str[thisChunkLen + len + 1] = '\0';
	}
	else //single string chunk isn't enough to concat
	{
		if (thisChunkLen == 0)
			*pstr = charString;
		else
		{
			String *newString = new String(charString);
			newString->prev = pstr;
			pstr->next = newString;
		}
	}
}

void String::nconcat(char const*const charString, int const len)
{
	char *charStringCopy = (char *)malloc((len + 1)*sizeof(char));
	memcpy(charStringCopy, charString, len*sizeof(char));
	charStringCopy[len] = '\0';

	this->concat(charStringCopy);
}

void String::append(char const ch)
{
	static int i = 0;
	String *pstr = this;
	int appendAt = 0;

	while (pstr->next)
		pstr = pstr->next;

	if (!isFullStringChunk(pstr->str))
		appendAt = 1 + ::getLength(pstr->str);
	else
	{
		String *pNewString = new String();
		pNewString->prev = pstr;
		pstr->next = pNewString;
		pstr = pNewString;
		appendAt = 1;
	}

	increaseLengthBy(pstr->str, 1);
	pstr->str[appendAt] = ch;
	pstr->str[appendAt + 1] = '\0';
}

void String::clear()
{
	delete (this->next);
	this->next = NULL;
	::setLength(this->str, 0);
	this->str[1] = '\0';
}

void String::trim()
{
	if (!(this->next))
		return;

	String *pstr = next;
	String *prevStr = this;
	while (pstr)
	{
		if (isEmptyStringChunk(pstr->str) == 0)
		{
			prevStr->next = pstr->next;
			if (pstr->next)
				pstr->next->prev = prevStr;
			pstr->next = NULL; //no "delete" recursive call (just delete the current string chunk)
			delete pstr;
			pstr = prevStr->next;
		}
		else
		{
			prevStr = pstr;
			pstr = pstr->next;
		}
	}
	pstr = this->next;
	if (pstr)
	{
		if (isEmptyStringChunk(this->str))
		{
			this->copyStringChunk(pstr->str);
			this->next = pstr->next;
			if (pstr->next)
				pstr->next->prev = this;
			pstr->next = NULL;
			delete pstr;
		}
	}
}

int String::indexOf(String const& subString, int pos) const
{
	int i = pos, j = 1;
	int n = this->getTotalLength(), m = subString.getTotalLength();
	while (i <= n && j <= m)
	{
		if ((*this)[i] == subString[j])
		{
			i++; j++;
		}
		else
		{
			i = i - j + 2;
			j = 1;
		}
	}
	if (j > m)
		return (i - m);
	else
		return 0;
}

String const& String::getSubstring(int pos, int len) const
{
	String *strSubStr = new String();
	if (pos < 1 || len<1)
		return *strSubStr; //return empty string

	//warning : int ~ unsigned int
	if ((pos + len - 1) > this->getTotalLength()) //exceeded the total end of string
		return *strSubStr;

	String const* strCurr = this;
	int cntPos = 0;
	int stringChunkLen = 0;
	while (strCurr)
	{
		stringChunkLen = ::getLength(strCurr->str);
		if ((cntPos < pos) && (cntPos + stringChunkLen >= pos))
		{//found start pos (pos : startPos)
			if (len <= stringChunkLen - (pos - cntPos) + 1)
			{
				strSubStr->nconcat(&strCurr->str[pos - cntPos], len);
				break; //finish
			}
			else
			{
				strSubStr->nconcat(&strCurr->str[pos - cntPos], stringChunkLen - (pos - cntPos) + 1);

				pos += (len - 1); //pos set as end pos (pos : endPos)
				//len -= (stringChunkLen - (pos - cntPos) + 1);
				cntPos += stringChunkLen;
				strCurr = strCurr->next;
				while (strCurr)
				{
					stringChunkLen = ::getLength(strCurr->str);
					if ((cntPos < pos) && (cntPos + stringChunkLen >= pos))
					{
						//len -= (stringChunkLen - (cntPos - pos) + 1);
						strSubStr->nconcat(&strCurr->str[1], pos-cntPos);

						return *strSubStr; //finish
					}
					else
					{
						strSubStr->nconcat(&strCurr->str[1], stringChunkLen);
						//len -= stringChunkLen;
						cntPos += stringChunkLen;
						strCurr = strCurr->next;
					}
				}
			}
			break; //found in which string chunk the pos is
		}
		else
		{
			cntPos += stringChunkLen;
			strCurr = strCurr->next;
		}
	}

	return *strSubStr;
}

char* String::peekStringToCharPointer(String const*& stringNext) const
{
	stringNext = this->next;
	int nChunkLen = this->getStringChunkLength();
	str[nChunkLen + 1] = '\0';
	return &str[1];
}

char* String::peekStringToCharPointer() const
{
	int nChunkLen = this->getStringChunkLength();
	str[nChunkLen + 1] = '\0';
	return &str[1];
}

int String::readFile(String const& filename)
{
	std::locale china("chs");
	std::ifstream fin;
	fin.imbue(china);

	int lenFileName = filename.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name is too long\n");
		return -1;
	}
	fin.open(filename.peekStringToCharPointer(), std::ios::in);
	if (!fin.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	this->clear(); //clear previous contents in the string
	int nRead = 0;
	char strBuffer[MAX_BUFFER_LEN + 1] = { '\0', };
	while (true)
	{
		fin.read(strBuffer, MAX_BUFFER_LEN);
		nRead = (int)fin.gcount();
		if (nRead == 0)
			break;
		this->nconcat(strBuffer, nRead);
	}

	fin.close();

	return 0;
}

int String::writeFile(String const& filename) const
{
	std::locale china("chs");
	std::ofstream fout;
	fout.imbue(china);

	int lenFileName = filename.getTotalLength();
	if (lenFileName > MAX_STRING_CHUNK_LEN || lenFileName > FILENAME_MAX)
	{
		printf("File name is too long\n");
		return -1;
	}

	//delete previous file
	std::remove(filename.peekStringToCharPointer());
	fout.open(filename.peekStringToCharPointer(), std::ios::out | std::ios::trunc);
	if (!fout.is_open())
	{
		printf("File open error\n");
		return -1;
	}

	int nStringChunkLen = 0;
	String const* pCurrStr = this;
	String const* pNextStr = pCurrStr;
	char *p = NULL;
	do
	{
		p = pCurrStr->peekStringToCharPointer(pNextStr);
		fout.write(p, pCurrStr->getStringChunkLength());
		pCurrStr = pNextStr;
	} while (pCurrStr);

	fout.close();

	return 0;
}