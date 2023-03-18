/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:25:47 by rbony             #+#    #+#             */
/*   Updated: 2023/03/18 13:22:01 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

ReversePolishNotation::ReversePolishNotation(std::string expression)
{
  std::string token;
  std::stringstream ss(expression);
  
  while (std::getline(ss, token, ' ')) {
    if (isdigit(token[0])) 
    {
        int digit = std::stoi(token);
        if (digit < 10)
            this->tokens.push(std::stoi(token));
        else
        {
            OperationException ex("Error");
            throw ex;
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