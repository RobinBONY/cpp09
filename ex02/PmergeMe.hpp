/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:53:02 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 17:01:01 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include <iostream>
#include <vector>
#include <list>
#include <ctime>
#include <cstdlib>

#ifndef PMERGEME_HPP
#define PMERGEME_HPP


class PmergeMe
{
    private:
        std::vector<int> vector;
        void displayVector();
        void vmerge(std::vector<int>& left, std::vector<int>& right, std::vector<int>& result);
        void vmerge_insert_sort(std::vector<int>& v);
        void sortVector(int argc, char **argv);
        
        std::list<int> list;
        void displayList();
        void lmerge(std::list<int>& left, std::list<int>& right, std::list<int>& result);
        void lmerge_insert_sort(std::list<int>& lst);
        void sortList(int argc, char **argv);

        PmergeMe(const PmergeMe &f);
        PmergeMe &operator=(const PmergeMe &f);
        PmergeMe();

    public:
        PmergeMe(int argc, char** argv);
        ~PmergeMe();
    
    class OperationException : public std::exception
    {
        private:
            const std::string message;
        public:
            OperationException(std::string message): message(message){};
            virtual ~OperationException() throw(){};

            virtual const char *what() const throw()
            {
            return this->message.c_str();
           }
    };
};

std::ostream& operator<<(std::ostream& os, const PmergeMe& merge);

#endif