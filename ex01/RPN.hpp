/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:26:02 by rbony             #+#    #+#             */
/*   Updated: 2023/04/12 12:51:40 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <string>
#include <cstdlib>
#include <cstring>

#ifndef RPN_HPP
#define RPN_HPP

class RPN
{
private:
	std::stack<long> tokens;

	bool isoperator(const char c);
	const char *removeWhitespaces(const char *str) const;

	RPN(const RPN &f);
	RPN &operator=(const RPN &f);
	RPN();

public:
	RPN(const char *str);
	~RPN();

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

std::ostream &operator<<(std::ostream &os, const RPN &rpn);

#endif