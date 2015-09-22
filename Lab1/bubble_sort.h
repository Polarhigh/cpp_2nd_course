#ifndef _BUBBLE_SORT_H_
#define _BUBBLE_SORT_H_

#include <vector>
#include <random>
#include <chrono>

// сортировка пузырьком с использованием оператора []
template<typename T>
void VectorBubbleSort(std::vector<T>& vec)
{
	T temp;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = i + 1; j < vec.size(); ++j)
		{
			if (vec[i] > vec[j])
			{
				temp = vec[i];
				vec[i] = vec[j];
				vec[j] = temp;
			}
		}
	}
}

// сортировка пузырьком с использованием at
template<typename T>
void VectorBubbleSort2(std::vector<T>& vec)
{
	T temp;

	for (size_t i = 0; i < vec.size(); ++i)
	{
		for (size_t j = i + 1; j < vec.size(); ++j)
		{
			if (vec.at(i) > vec.at(j))
			{
				temp = vec.at(i);
				vec.at(i) = vec.at(j);
				vec.at(j) = temp;
			}
		}
	}
}

// сортировка пузырьком с использованием только итераторов
template<typename T>
void VectorBubbleSort3(std::vector<T>& vec)
{
	T temp;

	for (auto it = vec.begin(); it != vec.end(); ++it)
	{
		for (auto it2 = it; it2 != vec.end(); ++it2)
		{
			if (*it > *it2)
			{
				temp = *it;
				*it = *it2;
				*it2 = temp;
			}
		}
	}
}

#endif // _BUBBLE_SORT_H_