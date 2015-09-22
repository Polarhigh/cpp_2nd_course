#ifndef _PHONEBOOK_H_
#define _PHONEBOOK_H_

#include "Record.h"
#include <vector>
#include <iterator>
#include <memory>

class Phonebook
{
	typedef std::vector<std::shared_ptr<Record>> RecordsList;

	RecordsList m_RecordsList;
	RecordsList::iterator m_CurRecord;

public:
	Phonebook() { }
	~Phonebook() { }

	RecordsList::iterator begin()
	{
		return m_RecordsList.begin();
	}

	RecordsList::iterator end()
	{
		return m_RecordsList.end();
	}

	RecordsList::const_iterator begin() const
	{
		return m_RecordsList.cbegin();
	}

	RecordsList::const_iterator end() const
	{
		return m_RecordsList.cend();
	}

	std::shared_ptr<Record> Current() const
	{
		return *m_CurRecord;
	}

	std::shared_ptr<Record> MoveNext()
	{
		return *(++m_CurRecord);
	}

	std::shared_ptr<Record> MovePrevious()
	{
		return *(--m_CurRecord);
	}

	std::shared_ptr<Record> Move(int movPos)
	{
		if (movPos > 0)
		{
			while (m_CurRecord != m_RecordsList.end() - 1 && movPos)
			{
				++m_CurRecord;
				--movPos;
			}
		}
		else if (movPos < 0)
		{
			while (m_CurRecord != m_RecordsList.begin() && movPos)
			{
				--m_CurRecord;
				++movPos;
			}
		}

		return *m_CurRecord;
	}

	int Count() const
	{
		return static_cast<int>(m_RecordsList.size());
	}

	bool IsEmpty() const
	{
		return m_RecordsList.empty();
	}

	bool HasNext() const
	{
		return m_CurRecord != m_RecordsList.end() - 1;
	}

	bool HasPrevious() const
	{
		return m_CurRecord != m_RecordsList.begin();
	}

	void InsertAfter(const std::shared_ptr<Record>& record)
	{
		Insert(std::inserter(m_RecordsList, m_CurRecord + 1), record);
	}

	void InsertBefore(const std::shared_ptr<Record>& record)
	{
		Insert(std::inserter(m_RecordsList, m_CurRecord), record);
	}

	void InsertLast(const std::shared_ptr<Record>& record)
	{
		Insert(std::inserter(m_RecordsList, m_RecordsList.end()), record);
	}

	void ReplaceCurrent(const std::shared_ptr<Record>& record)
	{
		Insert(m_CurRecord, record);;
	}

private:
	template<typename TIterator>
	void Insert(TIterator it, const std::shared_ptr<Record>& record)
	{
		*it = record;
		m_CurRecord = m_RecordsList.begin();
	}
};

#endif //_PHONEBOOK_H_