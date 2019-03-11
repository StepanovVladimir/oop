#include "pch.h"
#include "Decoder.h"

struct HtmlCharacter
{
	char ch;
	string code;
};

const HtmlCharacter QUOT = { '"', "&quot;" };
const HtmlCharacter APOS = { '\'', "&apos;" };
const HtmlCharacter LT = { '<', "&lt;" };
const HtmlCharacter GT = { '>', "&gt;" };
const HtmlCharacter AMP = { '&', "&amp;" };

string GetChangedStr(const string& str, const string& searchStr, const char& replaceCh)
{
	string changedStr;
	size_t  index = 0;
	size_t  foundIndex;
	while (index < str.length())
	{
		foundIndex = str.find(searchStr, index);
		if (foundIndex != string::npos)
		{
			changedStr.append(str, index, foundIndex - index);
			changedStr += replaceCh;
			index = foundIndex + searchStr.length();
		}
		else
		{
			changedStr.append(str, index);
			break;
		}
	}
	return changedStr;
}

string HtmlDecode(const string &html)
{
	string text = GetChangedStr(html, QUOT.code, QUOT.ch);
	text = GetChangedStr(text, APOS.code, APOS.ch);
	text = GetChangedStr(text, LT.code, LT.ch);
	text = GetChangedStr(text, GT.code, GT.ch);
	return GetChangedStr(text, AMP.code, AMP.ch);
}