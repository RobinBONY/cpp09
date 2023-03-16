/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:10:47 by rbony             #+#    #+#             */
/*   Updated: 2023/03/15 19:10:47 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>

#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

class BitcoinExchange
{
private:
    BitcoinExchange(const BitcoinExchange &f);
    BitcoinExchange &operator=(const BitcoinExchange &f);
    BitcoinExchange();

public:
    BitcoinExchange(const string &filename);
    ~BitcoinExchange();
};

#endif