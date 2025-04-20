/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/20 19:58:49 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeVec.hpp"
#include <vector>
#include <utility>
#include <iterator>

/// @brief compairs the int values
/// @param a first int
/// @param b second int
/// @return true if FIRST > SECOND (->implying a swap is neccessary)
bool PmergeMeVec::_compPair(int a, int b)
{
    _compCount++;
    return (a > b);
}

void PmergeMeVec::_swapPair(int a, int b)
{
    std::swap(a, b);

    // OLD
    // std::vector<int>::iterator tmp = a;
    // a = b;
    // b = tmp;
}

void PmergeMeVec::_swapPairs(std::pair<int, int> a, std::pair<int, int> b) // unify and template agnostically with swapPair later
{
    std::swap(a, b);
}

void PmergeMeVec::sort(std::vector<int> &vec)
{
    if (vec.size() < 2)
        return;

    _fordJohnson(vec.begin(), vec.end());
}

void PmergeMeVec::_fordJohnson(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    std::vector<int>::size_type elemCount = std::distance(begin, end);

    if (elemCount < 2)
        return;

    std::vector<int>::size_type pairCount = elemCount / 2;
    bool stragglerFlag = (elemCount % 2 != 0);

    std::vector<std::pair<int, int>> pairs;
    std::vector<int>::iterator it = begin;

    pairs.reserve(pairCount);

    // iterate through new vector of pairs and fill pairs with values
    for (size_t i = 0; i < pairCount; i++)
    {
        pairs.push_back(std::make_pair(*it, *(it + 1))); // create pair and add values
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
    if (stragglerFlag) // alternatively: (it != end)
    {
        int straggler = *std::prev(end);
    }

    for (size_t i = 0; i < (pairCount / 2); ++i)
    {
        if (_compPair(pairs[i].second, pairs[i + 1].second))
            _swapPairs(pairs[i], pairs[i + 1]); // fix types
        i += 2;
    }

    // Build main chain S
    std::vector<int> S;

    // Iterate through the pairs to build the main chain S from the larger elements
    S.reserve(elemCount);
    if (pairCount > 0)
        S.push_back(pairs[0].first); // b1

    for (size_t i = 1; i < pairCount; ++i)
    {
        S.push_back(pairs[i].second); // all a's            TODO: START AT 1 OR 0????
    }

    // Build pend P
    std::vector<int> P;
    P.reserve(pairCount);
    for (size_t i = 1; i < pairCount; ++i)
    {
        P.push_back(pairs[i].first); // remaining b's
    }

    std::size_t pendAmount = P.size();

    if (pendAmount > 0)
    {
        std::vector<bool> pendAlreadyInserted(pendAmount, false); // check values to keep track of already inserted elements
        std::size_t insertCount = 0;

        std::size_t prevJacob = 0;
        std::size_t currJacob = 1;
        std::size_t kJacob = 2;

        while (insertCount < pendAmount)
        {
            std::size_t nextJacob = currJacob + 2 * prevJacob;

            // needed for overflow protection
            if (nextJacob < currJacob)
            {
                nextJacob = std::numeric_limits<std::size_t>::max();
            }

            std::size_t limUpper = std::min(nextJacob, pendAmount + 1);

            for (size_t i = limUpper; i > currJacob; --i)
            {
                if (i < 2)
                    continue;
                std::size_t pendIndex = i - 2;

                if (pendIndex < pendAmount && !pendAlreadyInserted[pendIndex])
                {
                    auto &currElem = P[pendIndex];
                    auto &upperBoundVal = pairs[i - 1].second;
                    auto upperBoundIt = std::lower_bound(S.begin(), S.end(), upperBoundVal); // WHAT std::lower_bound(first, last, value)
                    auto insertPosIt = std::lower_bound(S.begin(), S.end(), currElem);
                    S.insert(insertPosIt, currElem);
                    ++insertCount;
                    pendAlreadyInserted[pendIndex] = true;
                }
            }
            break;
        }
    }
}
