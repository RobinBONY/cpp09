/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:26:02 by rbony             #+#    #+#             */
/*   Updated: 2023/03/18 13:19:16 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <stack>
#include <string>
#include <sstream>

#ifndef RPN_HPP
#define RPN_HPP


class ReversePolishNotation
{
    private:
        std::stack<int> tokens;

        ReversePolishNotation(const ReversePolishNotation &f);
        ReversePolishNotation &operator=(const ReversePolishNotation &f);
        ReversePolishNotation();

    public:
        ReversePolishNotation(std::string expression);
        ~ReversePolishNotation();
    
    class OperationException : public std::exception
    {
        private:
            const std::string message;
        public:
            OperationException(std::string message): message(message){};
            virtual ~OperationException(){};

            virtual const char *what() const throw()
            {
            return this->message.c_str();
           }
    };
};

#endif