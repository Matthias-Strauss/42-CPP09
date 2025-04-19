/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:31:18 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 19:35:40 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PMERGEMEVEC_HPP
#define PMERGEMEVEC_HPP
#include <iostream>
#include <vector>

unsigned int calcJacobsthalNum(unsigned int n);

class PmergeMeVec
{
public:
    PmergeMeVec() = default;
    PmergeMeVec(const PmergeMeVec &other) = default;
    PmergeMeVec &operator=(const PmergeMeVec &other) = default;
    ~PmergeMeVec() = default;

    void sort(std::vector<int> &vec);

private:
    static unsigned int _compCount;

    void fordJohnson(std::vector<int>::iterator begin, std::vector<int>::iterator end);
};

#include "PmergeMeVec.tpp"
#endif