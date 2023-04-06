/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rbony <rbony@corobizar.com>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/18 13:51:16 by rbony             #+#    #+#             */
/*   Updated: 2023/03/19 17:08:19 by rbony            ###   ########lyon.fr   */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::PmergeMe(int argc, char** argv)
{
    clock_t start, end;
    double duration;
    
    start = clock();
    sortList(argc, argv);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;

    std::cout << "Time to process a range of " << list.size() << " elements with std::list : " << duration << " us" << std::endl;
    
    start = clock();
    sortVector(argc, argv);
    end = clock();
    duration = (double)(end - start) / CLOCKS_PER_SEC * 1000000;
    
    std::cout << "Time to process a range of " << vector.size() << " elements with std::vector : " << duration << " us" << std::endl;
}

PmergeMe::~PmergeMe()
{
    
}

void PmergeMe::displayVector()
{
    int i = 0;
    for (std::vector<int>::iterator it = vector.begin(); it != vector.end(); it++)
    {
        if (i > 3)
        {
            std::cout << "[...]";
            break;
        }
        std::cout << *it << "   ";
        i++;
    }
    std::cout << std::endl;
}

void PmergeMe::sortVector(int argc, char **argv)
{
    try
    {
        int tmp;
        for (int i = 1; i < argc; i++) {
            tmp = atoi(argv[i]);
            if (tmp >= 0)
                vector.push_back(tmp);
            else
            {
                OperationException ex("Error");
                throw ex;
            }
        }
    }
    catch(const std::exception& e)
    {
        OperationException ex("Error");
        throw ex;
    }
    

    std::cout << "Vector Before:    ";
    displayVector();
    
    vmerge_insert_sort(vector);
    
    std::cout << "Vector After:     ";
    displayVector();
}

void PmergeMe::vmerge(std::vector<int>& left, std::vector<int>& right, std::vector<int>& result) {
    size_t i = 0, j = 0;
    while (i < left.size() && j < right.size()) {
        if (left[i] < right[j]) {
            result.push_back(left[i]);
            i++;
        } else {
            result.push_back(right[j]);
            j++;
        }
    }
    while (i < left.size()) {
        result.push_back(left[i]);
        i++;
    }
    while (j < right.size()) {
        result.push_back(right[j]);
        j++;
    }
}

void PmergeMe::vmerge_insert_sort(std::vector<int>& v) {
    if (v.size() <= 1) {
        return;
    }
    size_t middle = v.size() / 2;
    std::vector<int> left(v.begin(), v.begin() + middle);
    std::vector<int> right(v.begin() + middle, v.end());
    vmerge_insert_sort(left);
    vmerge_insert_sort(right);
    v.clear();
    vmerge(left, right, v);
}

void PmergeMe::displayList()
{
    int i = 0;
    for (std::list<int>::iterator it = list.begin(); it != list.end(); it++)
    {
        if (i > 3)
        {
            std::cout << "[...]";
            break;
        }
        std::cout << *it << "   ";
        i++;
    }
    std::cout << std::endl;
}

void PmergeMe::sortList(int argc, char **argv)
{
    try
    {
        int tmp;
        for (int i = 1; i < argc; i++) {
            tmp = atoi(argv[i]);
            if (tmp >= 0)
                list.push_back(tmp);
            else
            {
                OperationException ex("Error");
                throw ex;
            }
        }
    }
    catch(const std::exception& e)
    {
        OperationException ex("Error");
        throw ex;
    }
    

    std::cout << "List Before:  ";
    displayList();

    lmerge_insert_sort(list);
    
    std::cout << "List After:   ";
    displayList();
}

void PmergeMe::lmerge(std::list<int>& left, std::list<int>& right, std::list<int>& result) {
    std::list<int>::iterator it_left = left.begin();
    std::list<int>::iterator it_right = right.begin();
    while (it_left != left.end() && it_right != right.end()) {
        if (*it_left < *it_right) {
            result.push_back(*it_left);
            it_left++;
        } else {
            result.push_back(*it_right);
            it_right++;
        }
    }
    while (it_left != left.end()) {
        result.push_back(*it_left);
        it_left++;
    }
    while (it_right != right.end()) {
        result.push_back(*it_right);
        it_right++;
    }
}

void PmergeMe::lmerge_insert_sort(std::list<int>& lst) {
    if (lst.size() <= 1) {
        return;
    }
    std::list<int> left, right;
    std::list<int>::iterator it = lst.begin();
    for (size_t i = 0; i < lst.size() / 2; i++) {
        left.push_back(*it);
        it++;
    }
    for (; it != lst.end(); it++) {
        right.push_back(*it);
    }
    lmerge_insert_sort(left);
    lmerge_insert_sort(right);
    lst.clear();
    lmerge(left, right, lst);
}
