/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:53:02 by rbony             #+#    #+#             */
/*   Updated: 2023/04/16 18:15:44 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP

class PmergeMe
{
private:
	std::vector<int> _vector;
	double _vduration;

	std::list<int> _list;
	double _lduration;

	void sortList(int argc, char **argv);
	void insertList(std::list<int> &container, int i);
	void mergeInsertList(std::list<int> &container, std::list<int> &left, std::list<int> &right);
	void insertSortList(std::list<int> &list);
	void mergeSortList(std::list<int> &list);

	void sortVector(int argc, char **argv);
	void insertVector(std::vector<int> &vector, int tmp);
	void mergeInsertVector(std::vector<int> &vector, std::vector<int> &left, std::vector<int> &right);
	void insertSortVector(std::vector<int> &vector);
	void mergeSortVector(std::vector<int> &vector);

	int	is_num(char* str);

	PmergeMe(const PmergeMe &f);
	PmergeMe &operator=(const PmergeMe &f);
	PmergeMe();

public:
	PmergeMe(int argc, char **argv);
	~PmergeMe();

	class OperationException : public std::exception
	{
	private:
		const std::string message;

	public:
		OperationException(std::string message) : message(message){};
		virtual ~OperationException() throw(){};

		virtual const char *what() const throw()
		{
			return this->message.c_str();
		}
	};
};

#endif