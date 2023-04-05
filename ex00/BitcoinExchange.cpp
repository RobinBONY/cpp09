/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:10:45 by rbony             #+#    #+#             */
/*   Updated: 2023/03/25 09:28:02 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange(const std::string &dbname) : _dbname(dbname)
{
    readData();
}

bool BitcoinExchange::isValidDate(const std::string &date, const std::string &dateFormat) const {
    struct tm tm;
    memset(&tm, 0, sizeof(struct tm));
    if (strptime(date.c_str(), dateFormat.c_str(), &tm) == NULL) {
        return false;
    }
    return true;
}

void BitcoinExchange::readData()
{
    std::string dateFormat = "%Y-%m-%d";

    std::ifstream input(this->_dbname);
    if(!input.is_open())
    {
        ExchangeException ex("Could not open file");
        throw ex;
    }
    
    std::string line;
    std::getline(input,line);
    char delim = findDelimiter(line);
    float fvalue;
    while (std::getline(input,line))
    {
        std::stringstream ss(line);
        std::string date, value;

        std::getline(ss, date, delim);
        date = removeWhitespaces(date);
        std::getline(ss, value, delim);
        value = removeWhitespaces(value);
        if(isValidDate(date, dateFormat))
        {
            try
            {
                fvalue = std::stof(value);
                this->_data[date] = fvalue;
            }
            catch(const std::exception& e)
            {
                std::cout << "Error: bad input => " << date << std::endl;
            }
        }
        else
            std::cout << "Error: bad date format"<< std::endl;
    }
}

void BitcoinExchange::exchange(const std::string &filename) const {
    
    std::string dateFormat = "%Y-%m-%d";

    std::ifstream input(filename);
    if(!input.is_open())
    {
        ExchangeException ex("Could not open file");
        throw ex;
    }
    
    std::string line;
    std::getline(input,line);
    char delim = findDelimiter(line);
    float fvalue;
    while (std::getline(input,line))
    {
        std::stringstream ss(line);
        std::string date, value;

        std::getline(ss, date, delim);
        date = removeWhitespaces(date);
        std::getline(ss, value, delim);
        value = removeWhitespaces(value);
        if(isValidDate(date, dateFormat))
        {
            try
            {
                fvalue = std::stof(value);
            }
            catch(const std::exception& e)
            {
                std::cout << "Error: bad input => " << date << std::endl;
            }
            try
            {
                if (fvalue < 0)
                {
                    ExchangeException ex("Error: not a positive number.");
                    throw ex;
                }
                if (fvalue > 1000)
                {
                    ExchangeException ex("Error: too large a number.");
                    throw ex;
                }
                std::map<std::string, float>::const_iterator it = this->_data.lower_bound(date);
                if (it != this->_data.end() && it != this->_data.begin())
                {
                    it--;
                    std::cout << date << " => " << fvalue << " = " << it->second * fvalue << std::endl;
                }
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
        else
            std::cout << "Error: bad date format"<< std::endl;
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

char BitcoinExchange::findDelimiter(const std::string &line) const
{
    for (size_t i = 0; i < line.size(); i++)
    {
        if (!::isalpha(line[i]) && line[i] != ' ')
            return line[i];
    }
    return ',';
}
