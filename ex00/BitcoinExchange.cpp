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

BitcoinExchange::~BitcoinExchange(){};

BitcoinExchange::BitcoinExchange(const std::string &dbname) : _dbname(dbname)
{
    readData();
}

std::map<std::string, float> BitcoinExchange::getData()
{
    return this->_data;
}

bool BitcoinExchange::isValidDate(const std::string &date) const
{
    std::tm tm;
    std::sscanf(date.c_str(), "%d-%d-%d", &tm.tm_year, &tm.tm_mon, &tm.tm_mday);
    if (date.size() != 10 && tm.tm_mon <= 12 && tm.tm_mday <= 31)
    {
        return false;
    }
    return true;
}

void BitcoinExchange::readData()
{
    std::ifstream input(this->_dbname.c_str());
    if (!input.is_open())
    {
        ExchangeException ex("Could not open file");
        throw ex;
    }

    std::string line;
    char delim;
    std::getline(input, line);
    if (!line.empty())
        delim = findDelimiter(line);
    else
    {
        ExchangeException ex("Empty csv file");
        throw ex;
    }
    float fvalue;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string date, value;

        std::getline(ss, date, delim);
        date = removeWhitespaces(date);
        std::getline(ss, value, delim);
        value = removeWhitespaces(value);
        if (isValidDate(date))
        {
            try
            {
                fvalue = std::atof(value.c_str());
                this->_data[date] = fvalue;
            }
            catch (const std::exception &e)
            {
                std::cout << "Error: bad input => " << date << std::endl;
            }
        }
        else
            std::cout << "Error: bad date format" << std::endl;
    }
}

void BitcoinExchange::exchange(const std::string &filename) const
{
    std::ifstream input(filename.c_str());
    if (!input.is_open())
    {
        ExchangeException ex("Could not open file");
        throw ex;
    }

    std::string line;
    std::getline(input, line);
    char delim = findDelimiter(line);
    float fvalue;
    while (std::getline(input, line))
    {
        std::stringstream ss(line);
        std::string date, value;

        std::getline(ss, date, delim);
        date = removeWhitespaces(date);
        std::getline(ss, value, delim);
        value = removeWhitespaces(value);
        try
        {
            if (value.c_str()[0] == '\0')
            {
                ExchangeException ex("");
                throw ex;
            }
            fvalue = std::atof(value.c_str());
        }
        catch (const std::exception &e)
        {
            std::cout << "Error: bad input => " << date << std::endl;
            continue;
        }
        if (isValidDate(date))
        {
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
                if (it != this->_data.end() && it->first == date)
                {
                    std::cout << date << " => " << fvalue << " = " << it->second * fvalue << std::endl;
                }
                else if (it != this->_data.end())
                {
                    it--;
                    std::cout << date << " => " << fvalue << " = " << it->second * fvalue << std::endl;
                }
                else
                {
                    if (date > this->_data.rbegin()->first)
                        std::cout << date << " => " << fvalue << " = " << this->_data.rbegin()->second * fvalue << std::endl;
                    else
                    {
                        ExchangeException ex("Error: wrong date.");
                        throw ex;
                    }
                }
            }
            catch (const std::exception &e)
            {
                std::cerr << e.what() << '\n';
            }
        }
        else
            std::cout << "Error: bad date format" << std::endl;
    }
}

std::string BitcoinExchange::removeWhitespaces(const std::string &str) const
{
    std::string newStr = "";
    for (std::string::const_iterator it = str.begin(); it != str.end(); it++)
    {
        if (!std::isspace(*it))
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
