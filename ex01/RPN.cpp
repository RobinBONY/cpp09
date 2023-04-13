/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:25:47 by rbony             #+#    #+#             */
/*   Updated: 2023/04/12 12:57:29 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool RPN::isoperator(const char c)
{
	if (c == '+')
		return true;
	if (c == '-')
		return true;
	if (c == '*')
		return true;
	if (c == '/')
		return true;
	return false;
}

std::string RPN::removeWhitespaces(const std::string &str) const
{
	std::string newStr = "";
	for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
	{
		if (!std::isspace(*it))
			newStr += *it;
	}
	return newStr;
}

RPN::RPN(std::string expression)
{
	const char *str = removeWhitespaces(expression).c_str();

	for (size_t i = 0; i < expression.length(); i++)
	{
		if (isdigit(str[i]))
		{
			int digit = str[i] - 48;
			this->tokens.push(digit);
		}
		else if (isoperator(str[i]))
		{
			if (this->tokens.size() > 1)
			{
				int operand2 = this->tokens.top();
				this->tokens.pop();
				int operand1 = this->tokens.top();
				this->tokens.pop();

				if (str[i] == '+')
				{
					this->tokens.push(operand1 + operand2);
				}
				else if (str[i] == '-')
				{
					this->tokens.push(operand1 - operand2);
				}
				else if (str[i] == '*')
				{
					this->tokens.push(operand1 * operand2);
				}
				else if (str[i] == '/')
				{
					if (operand2 == 0)
					{
						OperationException ex("Error");
						throw ex;
					}
					this->tokens.push(operand1 / operand2);
				}
			}
			else
			{
				OperationException ex("Error");
				throw ex;
			}
		}
		else
		{
			OperationException ex("Error");
			throw ex;
		}
	}
	if (this->tokens.size() > 1)
	{
		OperationException ex("Error");
		throw ex;
	}
	std::cout << this->tokens.top() << std::endl;
}

RPN::~RPN()
{
}
