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
	std::vector<int> _vectorBefore;
	double _vduration;
	std::list<int> _list;
	std::list<int> _listBefore;
	double _lduration;

	template <typename T>
	void sort(int argc, char **argv, T &container, T &containerBefore);


	template <typename T>
	void mergeSort(T &container);

	template <typename T>
	void mergeInsert(T &container, T &left, T &right);

	template <typename T>
	void insert(T &container, int i);

	PmergeMe(const PmergeMe &f);
	PmergeMe &operator=(const PmergeMe &f);
	PmergeMe();

public:
	PmergeMe(int argc, char **argv);
	~PmergeMe();
	
	const std::vector<int> &getVector() const;
	const std::vector<int> &getVectorBefore() const;
	const std::list<int> &getList() const;
	const std::list<int> &getListBefore() const;

	double getVDuration() const;
	double getLDuration() const;

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

template <typename T>
void display(std::ostream &os, T &container, const std::string &comment);

std::ostream &operator<<(std::ostream &os, const PmergeMe &merge);

#endif