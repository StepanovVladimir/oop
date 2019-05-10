#pragma once

#include <string>

class CStringList
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
		virtual std::string &GetData()
		{
			throw std::runtime_error("Cannot dereference end iterator");
		}

		Node *prev, *next;
	};

public:
	CStringList();
	CStringList(const CStringList &other);
	CStringList(CStringList &&other);
	~CStringList();

	CStringList &operator=(const CStringList &other);
	CStringList &operator=(CStringList &&other);

	void PushFront(const std::string &str);
	void PushBack(const std::string &str);

	size_t GetSize() const;
	bool IsEmpty() const;

	void Clear();

	class CIterator
	{
	public:
		CIterator();

		CIterator &operator++();
		const CIterator operator++(int);

		CIterator &operator--();
		const CIterator operator--(int);

		std::string &operator*() const;

		bool operator==(const CIterator &other) const;
		bool operator!=(const CIterator &other) const;

	private:
		friend CStringList;

		CIterator(Node *node, bool isReverse);
		void DoIncrement();
		void DoDecrement();

		Node *m_node;
		bool m_isReverse;
	};

	void Insert(const CIterator &iter, const std::string &str);
	void Erase(CIterator &iter);

	CIterator begin() const;
	CIterator end() const;

	const CIterator cbegin() const;
	const CIterator cend() const;

	CIterator rbegin() const;
	CIterator rend() const;

	const CIterator crbegin() const;
	const CIterator crend() const;

private:
	class NodeWithData : public Node
	{
	public:
		NodeWithData(const std::string &str, Node *prev, Node *next)
			: m_str(str)
			, Node(prev, next)
		{
		}
		std::string &GetData() override
		{
			return m_str;
		}

	private:
		std::string m_str;
	};

	Node *m_first, *m_last;
	size_t m_size;
};