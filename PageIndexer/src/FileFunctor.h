#ifndef FILE_FUNCTOR_H
#define FILE_FUNCTOR_H

#include "StringHashTable.h"
#include "KeywordAVLTree.h"

enum class FileFunctorMode
{
	WRITE,
	READ,
};

template <typename ReferredObj>
class FileFunctor
{
private:
	std::ofstream m_fout;
	String m_filename;
	union //Reference list (only one reference object per functor) //Ref(read) only (instance not copied)
	{
		ReferredObj const* m_pReferredObj;

		StringHashTable const* m_pReferredHashTable;
		StringHashSubBucket const* m_pReferredSubBucket;
		LinkedList<StringBasicInfo> const* m_pReferredList;
		StringBasicInfo const* m_pReferredStringInfo;

		KeywordAVLTree<int> const* m_pReferredKeywordTree;
		Keyword<int> const* m_pReferredKeyword;
	}; //(thanks to pointer's attributes, they all have the same size)
	FileFunctorMode m_mode;

public:
	FileFunctor(ReferredObj const& referredObj, String const& filename, FileFunctorMode mode)
		: m_pReferredObj(&referredObj), m_filename(filename), m_mode(mode)
	{
		this->open();
	}
	~FileFunctor()
	{
		this->close();
	}

public:
	void changeMode(FileFunctorMode mode);
	void changeFileName(String const& newFileName);

private:
	template <typename NewReferredObj>
	void changeReferredObj(NewReferredObj const& Obj);

	int open();
	int close();

	//TODO (imcomplete)
	int write();
	template <typename NewReferredObj>
	int write();
	//TODO
	//int read();

public:
	//Do write/read
	void operator()()
	{
		switch (m_mode)
		{
		case FileFunctorMode::READ:
			//read();
			break;
		case FileFunctorMode::WRITE:
			write();
			break;
		default:
			printf("Error : Such FileFunctorMode does not exist\n");
			break;
		}
	}
	//First, change the referred object, and do write/read
	template <typename NewReferredObj>
	void operator()(NewReferredObj& RefObj)
	{
		changeReferredObj<NewReferredObj>(RefObj);
		switch (m_mode)
		{
		case FileFunctorMode::READ:
			//read();
			break;
		case FileFunctorMode::WRITE:
			write<NewReferredObj>();
			break;
		default:
			printf("Error : Such FileFunctorMode does not exist\n");
			break;
		}
	}
};

template <typename ReferredObj>
void FileFunctor<ReferredObj>::changeMode(FileFunctorMode mode)
{
	if (m_mode != mode)
	{
		this->close();
		m_mode = mode;
		this->open();
	}
}

template <typename ReferredObj>
void FileFunctor<ReferredObj>::changeFileName(String const& newFileName)
{
	if (m_filename != newFileName)
	{
		this->close();
		m_filename = newFileName;
		this->open();
	}
}

template <typename ReferredObj>
template <typename NewReferredObj>
void FileFunctor<ReferredObj>::changeReferredObj(NewReferredObj const& Obj)
{
	m_pReferredObj = reinterpret_cast<ReferredObj const*>(&Obj);
}

template <typename ReferredObj>
int FileFunctor<ReferredObj>::open()
{
	if (m_fout.is_open())
	{
		printf("Error : WriteFileFunctor : The file is already open\n");
		return -1;
	}
	
	if (m_filename.getTotalLength() > MAX_STRING_CHUNK_LEN ||
		m_filename.getTotalLength() > FILENAME_MAX)
	{
		printf("Error : WriteFileFunctor : The file name is too long\n");
		return -1;
	}

	std::locale china("chs");
	m_fout.imbue(china);

	switch (m_mode)
	{
	case FileFunctorMode::READ:
		m_fout.open(m_filename.peekStringToCharPointer(), std::ios::in);
		if (m_fout.is_open() == false)
		{
			printf("Error : WriteFileFunctor : cannot open the file.\n"
				"Might be currently being used by other instance\n");
			m_fout.clear();
			return -1;
		}

		break;
	case FileFunctorMode::WRITE:
		//delete previous file
		std::remove(m_filename.peekStringToCharPointer());
		m_fout.open(m_filename.peekStringToCharPointer(), std::ios::out | std::ios::app);
		if (m_fout.is_open() == false)
		{
			printf("Error : WriteFileFunctor : cannot open the file.\n"
				"Might be currently being used by other instance\n");
			m_fout.clear();
			return -1;
		}
		break;
	}
	return 0;
}

template <typename ReferredObj>
int FileFunctor<ReferredObj>::close()
{
	if (m_fout.is_open())
		m_fout.close();
	else
		return -1;
	return 0;
}

////////////////////////////////////////////////////////////////////////
//write basic template functions

template <typename ReferredObj>
int FileFunctor<ReferredObj>::write()
{
	//TODO : write
	printf("Error : FileFunctor<T>::write : This function for current type is not defined");
	return 0;
}

template <typename ReferredObj>
template <typename NewReferredObj>
int FileFunctor<ReferredObj>::write()
{
	//TODO : write
	printf("Error : FileFunctor<T>::write<NewReferredObj> : This function for current type is not defined\n");
	return 0;
}

#endif