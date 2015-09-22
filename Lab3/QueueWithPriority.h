#ifndef _QUEUEWITHPRIORITY_H_
#define _QUEUEWITHPRIORITY_H_

#include <iostream>
#include <vector>
#include <deque>
#include <algorithm>
#include <iterator>

// требования к TPriority: class enum от 0 до _count с шагом 1; так же необходима перегрузка <<
template<class TElement, class TPriority>
class QueueWithPriority
{
	typename typedef std::deque<TElement> TIQueue;

	std::vector<TIQueue*> m_Queues;

public:
	QueueWithPriority()
	{
		for (int i = 0; i < PrioritiesCount(); ++i)
			m_Queues.push_back(new TIQueue);
	}

	~QueueWithPriority()
	{
		for (const TIQueue* queue : m_Queues)
			delete queue;
	}

	void PutElementToQueue(const TElement& element, TPriority priority)
	{
		GetQueueP(priority)->push_back(element);
	}

	TElement GetElementFromQueue()
	{
		TElement outElement;

		for (TIQueue* queue : m_Queues)
		{
			if (!queue->empty())
			{
				outElement = queue->front();
				queue->pop_front();

				return outElement;
			}
		}

		throw std::exception("Очередь пуста");
	}

	void Accelerate(TPriority from, TPriority to)
	{
		TIQueue* queueFrom = GetQueueP(from);
		TIQueue* queueTo = GetQueueP(to);

		std::move(queueFrom->rbegin(), queueFrom->rend(), front_inserter(*queueTo));
		queueFrom->clear();
	}

	// элементам с самым низким приоритетом назначается наивысшиый
	void Accelerate()
	{
		Accelerate(static_cast<TPriority>(PrioritiesCount() - 1), static_cast<TPriority>(0));
	}

	bool IsEmpty() const
	{
		for (const TIQueue* queue : m_Queues)
			if (!queue->empty())
				return false;

		return true;
	}

	void ToStdOut() const
	{
		int i = 0;
		for (auto it = m_Queues.begin(); it != m_Queues.end(); ++it)
		{
			std::cout << endl << "[" << static_cast<TPriority>(i++) << "]" << endl;
			std::for_each((*it)->begin(), (*it)->end(), [](const TElement& val) { std::cout << val << endl; });
		}
	}

private:
	// Возвращает указатель на очередь связанную с приоритетом priority
	inline TIQueue* GetQueueP(TPriority priority) { return *(m_Queues.begin() + static_cast<int>(priority)); }

	// Количество приоритетов в TPriority
	inline int PrioritiesCount() { return static_cast<int>(TPriority::_count); }
};

#endif // _QUEUEWITHPRIORITY_H_