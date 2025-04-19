/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 21:30:26 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeVec.hpp"
#include <vector>
#include <utility>
#include <iterator>

/// @brief compairs the values that two iterators point to.
/// @param a first iter
/// @param b second iter
/// @return true if FIRST > SECOND (->implying a swap is neccessary)
bool _compPair(const std::vector<int>::iterator a, const std::vector<int>::iterator b)
{
    return (*a > *b);
}

void _swapPair(std::vector<int>::iterator a, std::vector<int>::iterator b)
{
    std::vector<int>::iterator tmp = a;
    a = b;
    b = tmp;
}

void PmergeMeVec::sort(std::vector<int> &vec)
{
    if (vec.size() < 2)
        return;

    _fordJohnson(vec.begin(), vec.end());
}

void PmergeMeVec::_fordJohnson(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    unsigned int elemCount;

    elemCount = std::distance(begin, end);
    if (elemCount < 2)
        return;

    bool straggler = (elemCount % 2 != 0);

    unsigned int pairCount = elemCount / 2;

    std::vector<std::pair<std::vector<int>::iterator, std::vector<int>::iterator>> pairs;
    std::vector<int>::iterator it = begin;

    // iterate through new vector of pairs and fill pairs with iterators
    for (size_t i = 0; i < pairCount; i++)
    {
        pairs.push_back(std::make_pair(it, (it + 1))); // create pair and add iterators
        it += 2;
    }

    // iterate through vector of pairs, compare , and swap if necessary
    for (auto const &p : pairs)
    {
        if (_compPair(p.first, p.second))
        {
            _swapPair(p.first, p.second);
        }
    }

    // handle straggler:
    if (it != end)
    {
        ;
    }

    //
    for (auto const &p : pairs)
    {
        /* code */
    }
}
