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

int	PmergeMe::is_num(char* str)
{
	for (int i = 0; str[i]; i++)
	{
		if (!(str[i] >= 48 && str[i] <= 57))
		{
			return (0);
		}
	}
	return (1);
}

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

	std::cout << "Time to process a range of " << this->_list.size() << " elements with std::list : " << this->_lduration << " us" << std::endl;
	std::cout << "Time to process a range of " << this->_vector.size() << " elements with std::vector : " << this->_vduration << " us" << std::endl;
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
		if (is_num(argv[i]))
		{
			tmp = std::atoi(argv[i]);
			if (tmp < 0)
			{
				OperationException ex("Error");
				throw ex;
			}
			this->_list.push_back(tmp);
		}
		else
		{
			OperationException ex("Error");
			throw ex;
		}
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
		right.merge(left);
		list.clear();
		list = right;
	}
	else
		insertSortList(list);
}

void PmergeMe::insertSortList(std::list<int> &list)
{
	std::list<int>::iterator ibegin = list.begin();
	std::list<int>::iterator jbegin = list.begin();
	ibegin++;
	for (std::list<int>::iterator it = ibegin; it != list.end(); it++)
	{
		for (std::list<int>::iterator jt = jbegin; jt != list.end(); jt++)
		{
			if (*it < *jt)
				std::swap(*it, *jt);
		}
	}
}

/*------------------Vector------------------*/

void PmergeMe::sortVector(int argc, char **argv)
{
	int tmp;
	for (int i = 1; i < argc; i++)
	{
		if (is_num(argv[i]))
		{
			tmp = std::atoi(argv[i]);
			if (tmp < 0)
			{
				OperationException ex("Error");
				throw ex;
			}
			this->_vector.push_back(tmp);
		}
		else
		{
			OperationException ex("Error");
			throw ex;
		}
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
	for (size_t i = 1; i < vector.size(); i++)
	{
		for (size_t j = 0; j < vector.size(); j++)
		{
			if (vector[i] < vector[j])
				std::swap(vector[i], vector[j]);
		}
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