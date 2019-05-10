#include "pch.h"
#include "StringList.h"

using namespace std;

CStringList::CStringList()
	: m_size(0)
{
	m_first = new Node(nullptr, nullptr);
	m_last = m_first;
}

CStringList::CStringList(const CStringList &other)
{
	CStringList tmp;
	for (CIterator iter = other.begin(); iter != other.end(); iter++)
	{
		tmp.PushBack(*iter);
	}
	m_first = new Node(nullptr, nullptr);
	m_last = m_first;
	*this = move(tmp);
}

CStringList::CStringList(CStringList &&other)
{
	Node *endNode = new Node(nullptr, nullptr);
	m_first = other.m_first;
	m_last = other.m_last;
	m_size = other.m_size;
	other.m_first = endNode;
	other.m_last = endNode;
	other.m_size = 0;
}

CStringList::~CStringList()
{
	Clear();
	delete m_last;
}

CStringList &CStringList::operator=(const CStringList &other)
{
	if (this != &other)
	{
		CStringList tmp(other);
		*this = move(tmp);
	}
	return *this;
}

CStringList &CStringList::operator=(CStringList &&other)
{
	if (this != &other)
	{
		Clear();
		swap(m_first, other.m_first);
		swap(m_last, other.m_last);
		swap(m_size, other.m_size);
	}
	return *this;
}

void CStringList::PushFront(const string &str)
{
	Node *newNode = new NodeWithData(str, nullptr, m_first);
	m_first->prev = newNode;
	m_first = newNode;
	m_size++;
}

void CStringList::PushBack(const string &str)
{
	Node *newNode = new NodeWithData(str, m_last->prev, m_last);
	if (IsEmpty())
	{
		m_first = newNode;
	}
	else
	{
		m_last->prev->next = newNode;
	}
	m_last->prev = newNode;
	m_size++;
}

size_t CStringList::GetSize() const
{
	return m_size;
}

bool CStringList::IsEmpty() const
{
	return m_size == 0;
}

void CStringList::Clear()
{
	Node *curNode = m_first;
	while (curNode->next != nullptr)
	{
		curNode = curNode->next;
		delete curNode->prev;
	}
	m_first = m_last;
	m_size = 0;
}

CStringList::CIterator::CIterator()
	: m_node(nullptr)
	, m_isReverse(false)
{
}

CStringList::CIterator::CIterator(Node *node, bool isReverse)
	: m_node(node)
	, m_isReverse(isReverse)
{
}

CStringList::CIterator &CStringList::CIterator::operator++()
{
	!m_isReverse ? DoIncrement() : DoDecrement();
	return *this;
}

const CStringList::CIterator CStringList::CIterator::operator++(int)
{
	CIterator tmp(*this);
	++(*this);
	return tmp;
}

CStringList::CIterator &CStringList::CIterator::operator--()
{
	!m_isReverse ? DoDecrement() : DoIncrement();
	return *this;
}

const CStringList::CIterator CStringList::CIterator::operator--(int)
{
	CIterator tmp(*this);
	--(*this);
	return tmp;
}

string &CStringList::CIterator::operator*() const
{
	if (m_node == nullptr)
	{
		throw runtime_error("Cannot dereference empty iterator");
	}
	return m_node->GetData();
}

bool CStringList::CIterator::operator==(const CIterator &other) const
{
	return m_node == other.m_node;
}

bool CStringList::CIterator::operator!=(const CIterator &other) const
{
	return m_node != other.m_node;
}

void CStringList::CIterator::DoIncrement()
{
	if (m_node == nullptr)
	{
		throw runtime_error("Cannot increment empty iterator");
	}
	if (m_node->next == nullptr)
	{
		throw runtime_error("Cannot increment end iterator");
	}
	m_node = m_node->next;
}

void CStringList::CIterator::DoDecrement()
{
	if (m_node == nullptr)
	{
		throw runtime_error("Cannot decrement empty iterator");
	}
	if (m_node->prev == nullptr)
	{
		throw runtime_error("Cannot decrement begin iterator");
	}
	m_node = m_node->prev;
}

void CStringList::Insert(const CIterator &iter, const string &str)
{
	if (iter.m_node == nullptr)
	{
		throw runtime_error("Iterator is empty");
	}

	if (iter == begin())
	{
		PushFront(str);
	}
	else if (iter == end())
	{
		PushBack(str);
	}
	else
	{
		Node *newNode = new NodeWithData(str, iter.m_node->prev, iter.m_node);
		iter.m_node->prev->next = newNode;
		iter.m_node->prev = newNode;
		m_size++;
	}
}

void CStringList::Erase(CIterator &iter)
{
	if (iter.m_node == nullptr)
	{
		throw runtime_error("Iterator is empty");
	}
	if (iter == end())
	{
		throw runtime_error("Iterator refers to the end of the list");
	}

	if (iter == begin())
	{
		m_first = iter.m_node->next;
		m_first->prev = nullptr;
	}
	else
	{
		iter.m_node->prev->next = iter.m_node->next;
		iter.m_node->next->prev = iter.m_node->prev;
	}
	delete iter.m_node;
	iter.m_node = nullptr;
	m_size--;
}

CStringList::CIterator CStringList::begin() const
{
	return CIterator(m_first, false);
}

CStringList::CIterator CStringList::end() const
{
	return CIterator(m_last, false);
}

const CStringList::CIterator CStringList::cbegin() const
{
	return CIterator(m_first, false);
}

const CStringList::CIterator CStringList::cend() const
{
	return CIterator(m_last, false);
}

CStringList::CIterator CStringList::rbegin() const
{
	return CIterator(m_first, true);
}

CStringList::CIterator CStringList::rend() const
{
	return CIterator(m_last, true);
}

const CStringList::CIterator CStringList::crbegin() const
{
	return CIterator(m_first, true);
}

const CStringList::CIterator CStringList::crend() const
{
	return CIterator(m_last, true);
}