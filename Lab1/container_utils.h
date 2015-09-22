#ifndef _CONTAINER_UTILS_H_
#define _CONTAINER_UTILS_H_

#include <type_traits>
#include <iterator>
#include <random>
#include <chrono>

// заполняет контейнер случайными значениями, тип контейнера должен являться целым или с плавающей точкой
template<template<class T, class All = std::allocator<T>> class TContainer, class TValues>
void FillContainer(TContainer<TValues>& vec, size_t num, TValues min, TValues max)
{
	using namespace std;
	typedef mt19937 TGenerator;
	typedef typename conditional<is_integral<TValues>::value, uniform_int_distribution<TValues>, uniform_real_distribution<TValues>>::type TUniformDistribution;

	unsigned seed = static_cast<unsigned>(chrono::system_clock::now().time_since_epoch().count());

	TGenerator gen(seed);
	TUniformDistribution distr(min, max);

	vec.resize(num);
	generate(vec.begin(), vec.end(), [&]() { return distr(gen); });
}

// вывод контейнера
template<template<class T, class All = std::allocator<T>> class TContainer, class TValues>
void PrintContainer(const TContainer<TValues>& cont, const char* delimiter = "\r\n")
{
	std::copy(cont.begin(), cont.end(), ostream_iterator<TValues>(std::cout, delimiter));
}

#endif // _CONTAINER_UTILS_H_