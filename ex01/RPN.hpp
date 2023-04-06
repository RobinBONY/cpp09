/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:26:02 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 16:48:57 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <cstdlib>

#ifndef RPN_HPP
#define RPN_HPP


class RPN
{
    private:
        std::stack<long> tokens;

        bool checkToken(const std::string &str) const;
        bool isOperator(const char c);
        bool checkExpression(const std::string &expression);
        std::string removeWhitespaces(const std::string &str) const;

        RPN(const RPN &f);
        RPN &operator=(const RPN &f);
        RPN();

    public:
        RPN(std::string expression);
        ~RPN();
    
    class OperationException : public std::exception
    {
        private:
            const std::string message;
        public:
            OperationException(std::string message): message(message){};
            virtual ~OperationException() throw(){};

            virtual const char *what() const throw()
            {
            return this->message.c_str();
           }
    };
};

std::ostream& operator<<(std::ostream& os, const RPN& rpn);

#endif