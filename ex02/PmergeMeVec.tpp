/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 19:31:25 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "PmergeMeVec.hpp"

void PmergeMeVec::sort(std::vector<int> &vec)
{
    if (vec.size() < 2)
        return;

    fordJohnson(vec.begin(), vec.end());
}

void PmergeMeVec::fordJohnson(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    unsigned int elemCount;

    elemCount = distance(begin, end);
    if (elemCount < 2)
        return;

    bool straggler = (elemCount % 2 != 0);

    unsigned int pairCount = elemCount / 2;

    std::vector<std::pair<int, int>> vec;
    std::vector<int>::iterator it = begin;

    for (size_t i = 0; i < pairCount; i++) // iterate through vector of pairs
    {
        for (size_t i = 0; i < 2; ++i) // iterate through ORIG-VEC
        {
            vec.push_back(std::make_pair(*it, *(it + 1))); // create pair and add ints
            it += 2;
        }
    }

    // handle straggler:
    if (it != end)
    {
        ;
    }

    for (auto a : vec)
    {
        /* code */
    }
}
