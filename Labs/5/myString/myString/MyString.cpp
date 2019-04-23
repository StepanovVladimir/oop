#include "pch.h"
#include "MyString.h"
#include <algorithm>

using namespace std;

CMyString::CMyString()
	: m_pChars(new char[1])
	, m_length(0)
{
	m_pChars[0] = '\0';
}

CMyString::CMyString(const char *pString)
	: m_length(strlen(pString))
{
	m_pChars = new char[m_length + 1];
	memcpy(m_pChars, pString, m_length + 1);
}

CMyString::CMyString(const char *pString, size_t length)
	: m_length(length)
	, m_pChars(new char[length + 1])
{
	memcpy(m_pChars, pString, m_length);
	m_pChars[m_length] = '\0';
}

CMyString::CMyString(const CMyString &other)
	: m_length(other.GetLength())
	, m_pChars(new char[other.GetLength() + 1])
{
	memcpy(m_pChars, other.GetStringData(), m_length + 1);
}

CMyString::CMyString(CMyString &&other)
	: m_pChars(other.m_pChars)
	, m_length(other.m_length)
{
	other.m_pChars = NULL;
	other.m_length = 0;
}

CMyString::CMyString(const string &stlString)
	: m_length(stlString.length())
	, m_pChars(new char[stlString.length() + 1])
{
	memcpy(m_pChars, stlString.c_str(), m_length + 1);
}

CMyString::~CMyString()
{
	delete[] m_pChars;
}

size_t CMyString::GetLength() const
{
	return m_length;
}

const char *CMyString::GetStringData() const
{
	return m_pChars;
}

CMyString CMyString::SubString(size_t start, size_t length) const
{
	if (start >= m_length)
	{
		throw runtime_error("Starting position greater than the length of the string");
	}
	return CMyString(&m_pChars[start], min(length, m_length - start));
}

void CMyString::Clear()
{
	m_length = 0;
	delete[] m_pChars;
	m_pChars = new char[1];
	m_pChars[0] = '\0';
}

CMyString &CMyString::operator=(const CMyString &other)
{
	if (this != &other)
	{
		CMyString tmp(other);
		swap(m_pChars, tmp.m_pChars);
		swap(m_length, tmp.m_length);
	}
	return *this;
}

CMyString &CMyString::operator=(CMyString &&other)
{
	if (&other != this)
	{
		delete[] m_pChars;
		m_pChars = other.m_pChars;
		m_length = other.m_length;
		other.m_pChars = NULL;
		other.m_length = 0;
	}
	return *this;
}

CMyString const operator+(const CMyString &str1, const CMyString &str2)
{
	CMyString tmp(str1);
	tmp += str2;
	return  tmp;
}

CMyString &CMyString::operator+=(const CMyString &other)
{
	CMyString tmp(*this);
	delete[] m_pChars;
	if (this != &other)
	{
		m_length += other.GetLength();
		m_pChars = new char[m_length + 1];
		memcpy(m_pChars, tmp.GetStringData(), tmp.GetLength());
		memcpy(&m_pChars[tmp.GetLength()], other.GetStringData(), other.GetLength() + 1);
	}
	else
	{
		m_length *= 2;
		m_pChars = new char[m_length + 1];
		memcpy(m_pChars, tmp.GetStringData(), tmp.GetLength());
		memcpy(&m_pChars[tmp.GetLength()], tmp.GetStringData(), tmp.GetLength() + 1);
	}
	return *this;
}

bool operator==(const CMyString &str1, const CMyString &str2)
{
	if (str1.GetLength() != str2.GetLength())
	{
		return false;
	}

	for (size_t i = 0; i < str1.GetLength(); i++)
	{
		if (str1[i] != str2[i])
		{
			return false;
		}
	}
	return true;
}

bool operator!=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 == str2);
}

bool operator<(const CMyString &str1, const CMyString &str2)
{
	for (size_t i = 0; i < min(str1.GetLength(), str2.GetLength()); i++)
	{
		if (str1[i] < str2[i])
		{
			return true;
		}

		if (str1[i] > str2[i])
		{
			return false;
		}
	}
	return str1.GetLength() < str2.GetLength();
}

bool operator>(const CMyString &str1, const CMyString &str2)
{
	return str2 < str1;
}

bool operator<=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 > str2);
}

bool operator>=(const CMyString &str1, const CMyString &str2)
{
	return !(str1 < str2);
}

const char &CMyString::operator[](size_t index) const
{
	if (index >= m_length)
	{
		throw runtime_error("Index greater than the length of the string");
	}
	return m_pChars[index];
}

char &CMyString::operator[](size_t index)
{
	if (index >= m_length)
	{
		throw runtime_error("Index greater than the length of the string");
	}
	return m_pChars[index];
}

ostream &operator<<(ostream &outStrm, const CMyString &str)
{
	for (size_t i = 0; i < str.GetLength(); i++)
	{
		outStrm << str[i];
	}
	return outStrm;
}

istream &operator>>(istream &inStrm, CMyString &str)
{
	string inStr;
	inStrm >> inStr;
	str = CMyString(inStr);
	return inStrm;
}