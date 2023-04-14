/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:51:16 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 17:08:19 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
	if (argc)
	{
	}
	if (argv)
	{
	}
	/*clock_t start, end;
	double duration;

	start = clock();
	sortList(argc, argv);
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << duration << " us" << std::endl;

	start = clock();
	sortVector(argc, argv);
	end = clock();
	duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << duration << " us" << std::endl;
	*/
	std::vector<int> vec(5);
	vec.push_back(5);
	vec.push_back(4);
	vec.push_back(3);
	vec.push_back(2);
	vec.push_back(1);
	mergeInsertSortVector(vec);
}

PmergeMe::~PmergeMe()
{
}

template <typename T>
void PmergeMe::display(const T &container) const
{
	int i = 0;
	for (typename T::iterator it = container.begin(); it != container.end(); it++)
	{
		if (i > 3)
		{
			std::cout << "[...]";
			break;
		}
		std::cout << *it << "   ";
		i++;
	}
	std::cout << std::endl;
}

void PmergeMe::mergeInsertSortVector(std::vector<int> &container)
{
	std::vector<int>::iterator begin = container.begin();
	std::vector<int>::iterator end = container.end();
	mergeSort<std::vector<int> >(begin, end);
	for (std::vector<int>::iterator it = container.begin(); it != container.end(); it++)
	{
		std::cout << *it << std::endl;
	}
}

template <typename T>
void PmergeMe::mergeSort(typename T::iterator &begin, typename T::iterator &end)
{
	if (std::distance(begin, end) > 1)
	{
		typename T::iterator middle = begin;
		std::advance(middle, std::distance(begin, end) / 2);
		mergeSort<T >(begin, middle);
		std::advance(middle, 1);
		mergeSort<T >(middle, end);
	}
	insertSort<T >(begin, end);
}

template <typename T>
void PmergeMe::insertSort(typename T::iterator &begin, typename T::iterator &end)
{
	for (typename T::iterator it = begin + 1; it != end; it++)
	{
		for (typename T::iterator jt = begin; jt != end; jt++)
		{
			if (*it < *jt)
				std::swap(*it, *jt);
		}
	}
}