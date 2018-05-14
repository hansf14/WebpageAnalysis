#include "String.h"

#ifdef PARSEHTML

////////////////////////////////////////////////////////////////////////
//Parse loaded HTML(int the string) and store in another string

#include "LinkedStack.h"

int KEY_HTML_TAGS_TOTAL = 4;
//key HTML-tags of which the contents are needed to be parsed
String const* KEY_HTML_TAGS[] = {
	new String("h1 class=\"headline-title\""),
	new String("h2 class=\"question-title\""),
	new String("span class=\"author\""),
	new String("div class=\"content\""),
};
int const CONTENT_INDEX = 3;
//the last (second) contents of "div class=\"content\" shouldn't be printed (useless content)

#define NON_PAIRED_HTML_TAGS_TOTAL 5
//non-paried HTML-tags (no </..>)
String const* NON_PAIRED_HTML_TAGS[] = {
	new String("!doctype html"),
	new String("img"),
	new String("meta"),
	new String("link"),
	new String("base"),
};


bool String::isKeyHTMLTag() const
{
	bool bTagKey = false;
	for (int i = 0; (i < KEY_HTML_TAGS_TOTAL); i++)
	{
		if (*this == *KEY_HTML_TAGS[i])
		{
			bTagKey = true;
			break;
		}
	}
	return bTagKey;
}

//find out which keyTag
bool String::isKeyHTMLTag(int& index) const
{
	bool bTagKey = false;
	for (int i = 0; (i < KEY_HTML_TAGS_TOTAL); i++)
	{
		if (*this == *KEY_HTML_TAGS[i])
		{
			index = i;
			bTagKey = true;
			break;
		}
	}
	return bTagKey;
}

bool String::isNonPairedHTMLTag() const
{
	bool bTagKey = false;
	for (int i = 0; i < NON_PAIRED_HTML_TAGS_TOTAL; i++)
	{
		if (this->indexOf(*NON_PAIRED_HTML_TAGS[i], 1) == 1)
		{
			bTagKey = true;
			break;
		}
	}
	return bTagKey;
}

void String::parseHTML(String &dstString) const
{
	dstString.clear(); //clear previous contents in the dstString

	bool bTag = false;
	bool bTagPair = false;
	bool bTagKey = false;

	String strHTMLTag;
	LinkedStack<String> stackTag;

	int n = this->getTotalLength();
	char ch;
	int i = 0, k = 0;
	while (i < n)
	{
		ch = (*this)[i++];

		//push(store) tags & pop(delete) tags
		if (bTag == false && ch == '<') //found the start of a tag (maybe paired-tag. or maybe not paired tag)
		{
			k = i;
			bTag = true;

			strHTMLTag.clear(); //clear previous tag
		}
		else if (bTag == true && ch == '>') //found the end of a tag (maybe pair start or maybe pair end tag or maybe non-paired tag)
		{//if it makes pair, pop twice to delete pair //if it doens't make pair and it's non-paired tag, delete it //else it's just a start of a pair tag
			bTag = false;
			stackTag.push(strHTMLTag); //**********add tag & goes into deeper tag

			if (bTagPair == true) //pair tag end
			{
				bTagPair = false;

				//***************delete 2 tags & see the shallower tag
				if (!stackTag.isEmpty())
					stackTag.pop();
				if (!stackTag.isEmpty())
				{
					stackTag.pop(strHTMLTag); //tag level changed
					if (bTagKey == true)
					{
						//check if popped tag is keyTag
						int keyTagIndex;
						if (strHTMLTag.isKeyHTMLTag(keyTagIndex))
						{
							//if (keyTagIndex == CONTENT_INDEX)
							//KEY_HTML_TAGS_TOTAL--;
							dstString.append('\n');
							bTagKey = false; //not keyTag anymore
							//htmlKeyContents.append('\n'); //current keyContent ended, append('\n')
						}
						/*else if (strHTMLTag == String("p"))
						htmlKeyContents.append('\n');*/
					}
				}
			}
			else //pair tag start or non-paired tag
			{
				if (!stackTag.isEmpty())
					stackTag.peek(strHTMLTag);

				if (bTagKey == false)
				{
					//check if it's key tag
					if (strHTMLTag.isKeyHTMLTag())
					{
						bTagKey = true;
						continue;
					}
				}

				//check if it's non-paried tag
				if (strHTMLTag.isNonPairedHTMLTag())
				{
					if (!stackTag.isEmpty())
						stackTag.pop(); //**************delete
					continue;
				}
			}
		}
		else if (bTag == true && ch == '/') //start of pair tag end
		{
			if (i - k == 1)
				bTagPair = true;
			strHTMLTag.append(ch);
		}
		else/*else if (ch != '\n')*/
		{
			if (bTag == false)
			{
				if (bTagKey == true)
					dstString.append(ch);
			}
			else
				strHTMLTag.append(ch);
		}
	}
}



#endif