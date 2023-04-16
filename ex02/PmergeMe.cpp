/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:51:16 by rbony             #+#    #+#             */
/*   Updated: 2023/04/16 18:25:13 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char **argv)
{
	clock_t start, end;
	start = clock();
	sort<std::list<int> >(argc, argv, this->_list, this->_listBefore);
	end = clock();
	_lduration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

	start = clock();
	sort<std::vector<int> >(argc, argv, this->_vector, this->_vectorBefore);
	end = clock();
	_vduration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
}

PmergeMe::~PmergeMe()
{
}

template <typename T>
void PmergeMe::sort(int argc, char **argv, T &container, T &containerBefore)
{
	int tmp;
	for (int i = 1; i < argc; i++)
	{
		tmp = std::atoi(argv[i]);
		if (tmp < 0)
		{
			OperationException ex("Error");
			throw ex;
		}
		container.push_back(tmp);
	}
	containerBefore = container;
	mergeSort<T >(container);
}

template <typename T>
void PmergeMe::mergeSort(T &container)
{
	if (container.size() > 2)
	{
		typename T::iterator middle = container.begin();
		std::advance(middle, std::distance(container.begin(), container.end()) / 2);
		T left(container.begin(), middle);
		mergeSort<T >(left);
		T right(middle, container.end());
		mergeSort<T >(right);
		mergeInsert<T >(container, left, right);
	}
	else if (container.size() == 2)
	{
		typename T::iterator itr = container.begin();
		typename T::iterator nextItr = itr;
		nextItr++;

		if (*nextItr < *itr)
			std::swap(*nextItr, *itr);
	}
}

template <typename T>
void PmergeMe::mergeInsert(T &container, T &left, T &right)
{
	int i;
	container.clear();
	while (left.size() > 0 && right.size() > 0)
	{
		if (*left.begin() < *right.begin())
		{
			i = *left.begin();
			left.erase(left.begin());
			insert<T >(container, i);
		}
		else
		{
			i = *right.begin();
			right.erase(right.begin());
			insert<T >(container, i);
		}
	}
	while (left.size() > 0)
	{
		i = *left.begin();
		left.erase(left.begin());
		insert<T >(container, i);
	}
	while (right.size() > 0)
	{
		i = *right.begin();
		right.erase(right.begin());
		insert<T >(container, i);
	}
}

template <typename T>
void PmergeMe::insert(T &container, int i)
{
	typename T::iterator it = container.begin();
	while (it != container.end() && *it < i)
		it++;
	container.insert(it, i);
}

const std::vector<int> &PmergeMe::getVector() const
{
	return this->_vector;
}

const std::vector<int> &PmergeMe::getVectorBefore() const
{
	return this->_vectorBefore;
}

const std::list<int> &PmergeMe::getList() const
{
	return this->_list;
}

const std::list<int> &PmergeMe::getListBefore() const
{
	return this->_listBefore;
}

double PmergeMe::getVDuration() const
{
	return this->_vduration;
}

double PmergeMe::getLDuration() const
{
	return this->_lduration;
}

std::ostream &operator<<(std::ostream &os, const PmergeMe &merge)
{
	std::list<int> l = merge.getList();
	std::vector<int> v = merge.getVector();
	display(os, merge.getListBefore(), "List before: ");
	display(os, l, "List after: ");
	display(os, merge.getVectorBefore(), "Vector before: ");
	display(os, v, "Vector after: ");
	os << "Time to process a range of " << l.size() << " elements with std::list : " << merge.getLDuration() << " us" << std::endl;
	os << "Time to process a range of " << v.size() << " elements with std::vector : " << merge.getVDuration() << " us" << std::endl;
	return os;
}

template <typename T>
void display(std::ostream &os, T &container, const std::string &comment)
{
	int i = 0;
	os << comment;
	for (typename T::const_iterator it = container.begin(); it != container.end(); it++)
	{
		if (i > 3)
		{
			os << "[...]";
			break;
		}
		os << *it << "   ";
		i++;
	}
	os << std::endl;
}