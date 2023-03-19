/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:10:45 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 16:04:13 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &filename) : filename(filename)
{
    this->readData();
    this->exchange();
    
}

BitcoinExchange::~BitcoinExchange()
{
}

void BitcoinExchange::readData()
{
    std::ifstream data("data.csv");
    if(!data.is_open())
    {
        ExchangeException ex("Could not open file");
        throw ex;
    }
    
    std::string line;
    std::getline(data,line);
    while (std::getline(data,line))
    {
        std::stringstream ss(line);
        std::string date, value;

        std::getline(ss, date, ',');
        std::getline(ss, value, ',');
        this->data[date] = std::stof(value);
    }
}

std::string BitcoinExchange::removeWhitespaces(const std::string &str) const
{
    std::string newStr = "";
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if(!std::isspace(*it))
            newStr += *it;
    }
    return newStr;
}

void BitcoinExchange::exchange() const 
{
    std::ifstream data(this->filename);
    if(!data.is_open())
    {
        ExchangeException ex("Could not open file");
        throw ex;
    }
    
    std::string line;
    long num;
    std::getline(data,line);
    while (std::getline(data,line))
    {
        std::stringstream ss(line);
        std::string date, value;

        std::getline(ss, date, '|');
        date = removeWhitespaces(date);
        std::getline(ss, value, '|');
        value = removeWhitespaces(value);
        
        try
        {
            num = std::stol(value);
            try
            {
                if (num < 0)
                {
                    ExchangeException ex("Error: not a positive number.");
                    throw ex;
                }
                if (num > 1000)
                {
                    ExchangeException ex("Error: too large a number.");
                    throw ex;
                }
                std::map<std::string, float>::const_iterator it = this->data.lower_bound(date);
                if (it != this->data.end())
                    std::cout << date << " => " << value << " = " << it->second * num << std::endl;
                else
                {
                    ExchangeException ex("Error: wrong date.");
                    throw ex;
                }
            }
            catch(const std::exception& e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        catch(const std::exception& e)
        {
            std::cout << "Error: bad input => " << date << std::endl;
        }
        
    }
}