/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:25:47 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 16:50:40 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

bool RPN::isOperator(const char c)
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

bool RPN::checkExpression(const std::string &expression)
{
  const char *str = removeWhitespaces(expression).c_str();
  long operatorCount = 0;
  long digitCount = 0;

  for (int i = 0; str[i]; i++)
  {
    if (isdigit(str[i]))
      digitCount++;
    else if (isOperator(str[i]))
      operatorCount++;
    else
      return false;
  }
  if (operatorCount == (digitCount - 1))
    return true;
  return false;
}

RPN::RPN(std::string expression)
{
  if (!checkExpression(expression.c_str()))
  {
    OperationException ex("Error");
    throw ex;
  }
  std::string token;
  std::stringstream ss(expression);
  
  while (std::getline(ss, token, ' ')) {
    if (checkToken(token)) 
    {
        int digit = std::stoi(token);
        if (digit < 10)
            this->tokens.push(digit);
        else
        {
          if (digit < 100)
          {
            this->tokens.push(digit / 10);
            this->tokens.push(digit % 10);
          }
          else
          {
            OperationException ex("Error");
            throw ex;
          }
        }
    } 
    else if(token == "+" || token == "-" || token == "*" || token == "/")
    {
      if (this->tokens.size() == 2)
      {
        int operand2 = this->tokens.top();
        this->tokens.pop();
        int operand1 = this->tokens.top();
        this->tokens.pop();

        if (token == "+") {
          this->tokens.push(operand1 + operand2);
        } else if (token == "-") {
          this->tokens.push(operand1 - operand2);
        } else if (token == "*") {
          this->tokens.push(operand1 * operand2);
        } else if (token == "/") {
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
  std::cout << this->tokens.top() << std::endl;
}

RPN::~RPN()
{
    
}

std::string RPN::removeWhitespaces(const std::string &str) const
{
    std::string newStr = "";
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if(!std::isspace(*it))
            newStr += *it;
    }
    return newStr;
}

bool RPN::checkToken(const std::string &str) const
{
  for (size_t i = 0; i < str.size(); i++)
  {
    if (!isdigit(str[i]))
      return false;
  }
  return true;  
}