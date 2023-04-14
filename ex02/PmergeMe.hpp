/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:53:02 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 17:01:01 by rbony            ###   ########lyon.fr   */
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

	template <typename T>
	void display(const T &container) const;

	template <typename T>
	void mergeSort(typename T::iterator &begin, typename T::iterator &end);
	template <typename T>
	void PmergeMe::insertSort(T &container)

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

std::ostream &operator<<(std::ostream &os, const PmergeMe &merge);

#endif