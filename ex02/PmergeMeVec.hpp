/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:31:18 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/20 22:59:47 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PMERGEMEVEC_HPP
#define PMERGEMEVEC_HPP
#include <iostream>
#include <vector>
#include <iterator>
#include <utility>
#include <limits>
#include <algorithm>

// unsigned int calcJacobsthalNum(unsigned int n);

class PmergeMeVec
{
public:
    PmergeMeVec() = default;
    PmergeMeVec(const PmergeMeVec &other) = default;
    PmergeMeVec &operator=(const PmergeMeVec &other) = default;
    ~PmergeMeVec() = default;

    static void sort(std::vector<int> &vec);
    static void _fordJohnson(std::vector<int>::iterator begin, std::vector<int>::iterator end);
    static bool _compPair(int &a, int &b);
    static void _swapPair(int &a, int &b);
    static void _swapPairs(std::pair<int, int> &a, std::pair<int, int> &b);

private:
    inline static unsigned int _compCount = 0;
    // void _nextElem();
};

#endif