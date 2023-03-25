/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:10:47 by rbony             #+#    #+#             */
/*   Updated: 2023/03/25 09:05:20 by rbony            ###   ########lyon.fr   */
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
    const std::string _dbname;
    std::map<std::string, float> _data;

    void                            readData();
    std::string                     removeWhitespaces(const std::string &str) const;
    char                            findDelimiter(const std::string &line) const;

    BitcoinExchange(const BitcoinExchange &f);
    BitcoinExchange &operator=(const BitcoinExchange &f);
    BitcoinExchange();

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

public:
    BitcoinExchange(const std::string &dbname);
    ~BitcoinExchange();
    
    void                            exchange(const std::string &filename) const;
};

#endif