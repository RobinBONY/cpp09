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

const char *RPN::removeWhitespaces(const char *str) const
{
	std::string result;
	while (*str)
	{
		if (!isspace(*str))
		{
			result += *str;
		}
		str++;
	}
	char *newStr = new char[result.length() + 1];
	strcpy(newStr, result.c_str());
	return newStr;
}

RPN::RPN(const char *expression)
{
	const char *str = removeWhitespaces(expression);

	for (size_t i = 0; str[i]; i++)
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
	if (this->tokens.size() != 1)
	{
		OperationException ex("Error");
		throw ex;
	}
	std::cout << this->tokens.top() << std::endl;
}

RPN::~RPN()
{
}
