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

int ReversePolishNotation::checkToken(const std::string &str) const
{
  for (size_t i = 0; i < str.size(); i++)
  {
    if (!isdigit(str[i]))
      return 0;
  }
  return 1;  
}

ReversePolishNotation::ReversePolishNotation(std::string expression)
{
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
            this->tokens.push(digit / 10);
            this->tokens.push(digit % 10);
        }
    } 
    else if(token == "+" || token == "-" || token == "*" || token == "/")
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
  std::cout << this->tokens.top() << std::endl;
}

ReversePolishNotation::~ReversePolishNotation()
{
    
}