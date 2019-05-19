#pragma once

#include <iostream>

template<typename T>
class CMyList
{
	class Node
	{
	public:
		Node(Node *prev, Node *next)
			: prev(prev)
			, next(next)
		{
		}
		virtual ~Node() = default;
		virtual T &GetData()
		{
			throw std::runtime_error("Cannot dereference end iterator");
		}

		Node *prev, *next;
	};

public:
	CMyList(): m_size(0)
	{
		m_first = new Node(nullptr, nullptr);
		m_last = m_first;
	}

	CMyList(const CMyList &other)
	{
		CMyList tmp;
		for (CIterator iter = other.begin(); iter != other.end(); iter++)
		{
			tmp.PushBack(*iter);
		}
		m_first = new Node(nullptr, nullptr);
		m_last = m_first;
		*this = move(tmp);
	}

	CMyList(CMyList &&other)
	{
		Node *endNode = new Node(nullptr, nullptr);
		m_first = other.m_first;
		m_last = other.m_last;
		m_size = other.m_size;
		other.m_first = endNode;
		other.m_last = endNode;
		other.m_size = 0;
	}

	~CMyList()
	{
		Clear();
		delete m_last;
	}

	CMyList &operator=(const CMyList &other)
	{
		if (this != &other)
		{
			CMyList tmp(other);
			*this = move(tmp);
		}
		return *this;
	}

	CMyList &operator=(CMyList &&other)
	{
		if (this != &other)
		{
			Clear();
			std::swap(m_first, other.m_first);
			std::swap(m_last, other.m_last);
			std::swap(m_size, other.m_size);
		}
		return *this;
	}

	void PushFront(const T &data)
	{
		Node *newNode = new NodeWithData(data, nullptr, m_first);
		m_first->prev = newNode;
		m_first = newNode;
		m_size++;
	}

	void PushBack(const T &data)
	{
		Node *newNode = new NodeWithData(data, m_last->prev, m_last);
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

	size_t GetSize() const
	{
		return m_size;
	}

	bool IsEmpty() const
	{
		return m_size == 0;
	}

	void Clear()
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

	class CIterator
	{
	public:
		CIterator()
			: m_node(nullptr)
			, m_isReverse(false)
		{
		}

		CIterator &operator++()
		{
			!m_isReverse ? DoIncrement() : DoDecrement();
			return *this;
		}

		const CIterator operator++(int)
		{
			CIterator tmp(*this);
			++(*this);
			return tmp;
		}

		CIterator &operator--()
		{
			!m_isReverse ? DoDecrement() : DoIncrement();
			return *this;
		}

		const CIterator operator--(int)
		{
			CIterator tmp(*this);
			--(*this);
			return tmp;
		}

		T &operator*() const
		{
			if (m_node == nullptr)
			{
				throw std::runtime_error("Cannot dereference empty iterator");
			}
			return m_node->GetData();
		}

		bool operator==(const CIterator &other) const
		{
			return m_node == other.m_node;
		}

		bool operator!=(const CIterator &other) const
		{
			return m_node != other.m_node;
		}

	private:
		friend CMyList;

		CIterator(Node *node, bool isReverse)
			: m_node(node)
			, m_isReverse(isReverse)
		{
		}

		void DoIncrement()
		{
			if (m_node == nullptr)
			{
				throw std::runtime_error("Cannot increment empty iterator");
			}
			if (m_node->next == nullptr)
			{
				throw std::runtime_error("Cannot increment end iterator");
			}
			m_node = m_node->next;
		}

		void DoDecrement()
		{
			if (m_node == nullptr)
			{
				throw std::runtime_error("Cannot decrement empty iterator");
			}
			if (m_node->prev == nullptr)
			{
				throw std::runtime_error("Cannot decrement begin iterator");
			}
			m_node = m_node->prev;
		}

		Node *m_node;
		bool m_isReverse;
	};

	void Insert(const CIterator &iter, const T &data)
	{
		if (iter.m_node == nullptr)
		{
			throw std::runtime_error("Iterator is empty");
		}

		if (iter == begin())
		{
			PushFront(data);
		}
		else if (iter == end())
		{
			PushBack(data);
		}
		else
		{
			Node *newNode = new NodeWithData(data, iter.m_node->prev, iter.m_node);
			iter.m_node->prev->next = newNode;
			iter.m_node->prev = newNode;
			m_size++;
		}
	}

	void Erase(CIterator &iter)
	{
		if (iter.m_node == nullptr)
		{
			throw std::runtime_error("Iterator is empty");
		}
		if (iter == end())
		{
			throw std::runtime_error("Iterator refers to the end of the list");
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

	CIterator begin() const
	{
		return CIterator(m_first, false);
	}

	CIterator end() const
	{
		return CIterator(m_last, false);
	}

	const CIterator cbegin() const
	{
		return CIterator(m_first, false);
	}

	const CIterator cend() const
	{
		return CIterator(m_last, false);
	}

	CIterator rbegin() const
	{
		return CIterator(m_first, true);
	}

	CIterator rend() const
	{
		return CIterator(m_last, true);
	}

	const CIterator crbegin() const
	{
		return CIterator(m_first, true);
	}

	const CIterator crend() const
	{
		return CIterator(m_last, true);
	}

private:
	class NodeWithData : public Node
	{
	public:
		NodeWithData(const T &data, Node *prev, Node *next)
			: m_data(data)
			, Node(prev, next)
		{
		}

		T &GetData() override
		{
			return m_data;
		}

	private:
		T m_data;
	};

	Node *m_first, *m_last;
	size_t m_size;
};