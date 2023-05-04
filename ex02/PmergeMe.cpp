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
	sortList(argc, argv);
	end = clock();
	_lduration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

	start = clock();
	sortVector(argc, argv);
	end = clock();
	_vduration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

	std::cout << "Before: ";
	for (int i = 1; i < argc; i++)
	{
		if (i > 5)
		{
			std::cout << "[...]";
			break;
		}
		std::cout << argv[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "List after: ";
	int j = 0;
	for (std::list<int>::iterator it = this->_list.begin(); it != this->_list.end(); it++)
	{
		if (j > 4)
		{
			std::cout << "[...]";
			break;
		}
		std::cout << *it << " ";
		j++;
	}
	std::cout << std::endl;

	std::cout << "Vector after: ";
	for (size_t i = 0; i < this->_vector.size(); i++)
	{
		if (i > 4)
		{
			std::cout << "[...]";
			break;
		}
		std::cout << this->_vector[i] << " ";
	}
	std::cout << std::endl;

	std::cout << "Time to process a range of " << this->_list.size() << " elements with std::list : " << this->_lduration << std::endl;
	std::cout << "Time to process a range of " << this->_vector.size() << " elements with std::vector : " << this->_vduration << std::endl;
}

PmergeMe::~PmergeMe()
{
}

/*------------------List--------------------*/

void PmergeMe::sortList(int argc, char **argv)
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
		this->_list.push_back(tmp);
	}
	mergeSortList(this->_list);
}

void PmergeMe::mergeSortList(std::list<int> &list)
{
	if (list.size() > 100)
	{
		std::list<int>::iterator middle = list.begin();
		std::advance(middle, std::distance(list.begin(), list.end()) / 2);
		std::list<int> left(list.begin(), middle);
		mergeSortList(left);
		std::list<int> right(middle, list.end());
		mergeSortList(right);
		mergeInsertList(list, left, right);
	}
	else
		insertSortList(list);
}

void PmergeMe::mergeInsertList(std::list<int> &container, std::list<int> &left, std::list<int> &right)
{
	int i;
	container.clear();
	while (left.size() > 0 && right.size() > 0)
	{
		if (*left.begin() < *right.begin())
		{
			i = *left.begin();
			left.erase(left.begin());
			insertList(container, i);
		}
		else
		{
			i = *right.begin();
			right.erase(right.begin());
			insertList(container, i);
		}
	}
	while (left.size() > 0)
	{
		i = *left.begin();
		left.erase(left.begin());
		insertList(container, i);
	}
	while (right.size() > 0)
	{
		i = *right.begin();
		right.erase(right.begin());
		insertList(container, i);
	}
}

void PmergeMe::insertList(std::list<int> &container, int i)
{
	std::list<int>::iterator it = container.begin();
	while (it != container.end() && *it < i)
		it++;
	container.insert(it, i);
}

void PmergeMe::insertSortList(std::list<int> &list)
{
	std::list<int>::iterator it, rit, tmpit;
	int tmp;
	for (it = list.begin(); it != list.end(); it++)
	{
		tmp = *it;
		for (rit = it; rit != list.begin() && tmp <= *rit; rit--)
		{
			tmpit = rit;
			tmpit--;
			std::swap(*rit, *tmpit);
		}
	}
}

/*------------------Vector------------------*/

void PmergeMe::sortVector(int argc, char **argv)
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
		this->_vector.push_back(tmp);
	}
	mergeSortVector(this->_vector);
}

void PmergeMe::insertVector(std::vector<int> &vector, int tmp)
{
	size_t i = 0;
	while (i < vector.size() && vector[i] < tmp)
		i++;
	vector.insert(vector.begin() + i, tmp);
}

void PmergeMe::mergeInsertVector(std::vector<int> &vector, std::vector<int> &left, std::vector<int> &right)
{
	int tmp;
	vector.clear();
	while (left.size() > 0 && right.size() > 0)
	{
		if (left[0] < right[0])
		{
			tmp = left[0];
			left.erase(left.begin());
			insertVector(vector, tmp);
		}
		else
		{
			tmp = right[0];
			right.erase(right.begin());
			insertVector(vector, tmp);
		}
	}
	while (left.size() > 0)
	{
		tmp = left[0];
		left.erase(left.begin());
		insertVector(vector, tmp);
	}
	while (right.size() > 0)
	{
		tmp = right[0];
		right.erase(right.begin());
		insertVector(vector, tmp);
	}
}

void PmergeMe::insertSortVector(std::vector<int> &vector)
{
	int i, ri, tmp;
	for (i = 0; i < (int)vector.size(); i++)
	{
		tmp = vector[i];
		for (ri = i; ri > 0 && tmp <= vector[ri]; ri--)
		{
			vector[ri] = vector[ri - 1];
		}
		vector[ri] = tmp;
	}
}

void PmergeMe::mergeSortVector(std::vector<int> &vector)
{
	if (vector.size() > 100)
	{
		std::vector<int>::iterator middle = vector.begin();
		std::advance(middle, std::distance(vector.begin(), vector.end()) / 2);
		std::vector<int> left(vector.begin(), middle);
		mergeSortVector(left);
		std::vector<int> right(middle, vector.end());
		mergeSortVector(right);
		mergeInsertVector(vector, left, right);
	}
	else
		insertSortVector(vector);
}