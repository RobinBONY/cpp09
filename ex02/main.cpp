/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:51:12 by rbony             #+#    #+#             */
/*   Updated: 2023/03/18 13:58:42 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int main(int argc, char**argv)
{
  /*if(argc < 2 || argv[1][0] == '\0')
  {
    std::cout << "Usage: " << argv[0] << " <args>" << std::endl;
    return (1);
  }*/

  try
  {
    PmergeMe merge(argc, argv);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}