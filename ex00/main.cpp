/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/15 19:10:53 by rbony             #+#    #+#             */
/*   Updated: 2023/03/25 09:05:35 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int argc, char**argv)
{
    if(argc != 2)
    {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        return (1);
    }


    try
    {
        BitcoinExchange btc("data.csv");
        btc.exchange(argv[1]);
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    
}
