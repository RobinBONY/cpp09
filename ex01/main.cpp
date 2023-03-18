/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 12:25:52 by rbony             #+#    #+#             */
/*   Updated: 2023/03/18 12:57:17 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

int main(int argc, char**argv)
{
  if(argc < 2)
  {
    std::cout << "Usage: " << argv[0] << " <expression>" << std::endl;
    return (1);
  }

  try
  {
    ReversePolishNotation rpn(argv[1]);
  }
  catch(const std::exception& e)
  {
    std::cerr << e.what() << '\n';
  }

  return 0;
}