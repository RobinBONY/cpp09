/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:10:47 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 16:47:07 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP


class BitcoinExchange
{


private:
    const std::string filename;
    std::map<std::string, float> data;


    BitcoinExchange(const BitcoinExchange &f);
    BitcoinExchange &operator=(const BitcoinExchange &f);
    BitcoinExchange();
    std::string removeWhitespaces(const std::string &str) const;

public:
    BitcoinExchange(const std::string &filename);
    ~BitcoinExchange();

    void    readData();
    void    exchange() const;
    
    class ExchangeException : public std::exception
    {
        private:
            const std::string message;
        public:
            ExchangeException(std::string message): message(message){};
            virtual ~ExchangeException(){};

            virtual const char *what() const throw()
            {
            return this->message.c_str();
           }
    };
};

#endif