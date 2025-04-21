/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 10:40:06 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "PmergeMeVec.hpp"

/// @brief compairs the int values
/// @param a first int
/// @param b second int
/// @return true if FIRST > SECOND (->implying a swap is neccessary)
template <typename Container, typename T>
bool PmergeMeVec<Container, T>::_compare(T &a, T &b)
{
    _compCount++;
    return (a > b);
}

template <typename Container, typename T>
void PmergeMeVec<Container, T>::_swap(T &a, T &b)
{
    std::swap(a, b);
}

template <typename Container, typename T>
void PmergeMeVec<Container, T>::sort(Container &src)
{
    if (src.size() < 2)
        return;

    _fordJohnson(src.begin(), src.end());
}

template <typename Container, typename T>
void PmergeMeVec<Container, T>::_fordJohnson(typename Container::iterator begin, typename Container::iterator end, int groupSize)
{
    typedef typename Container::iterator It;

    int elemCount = std::distance(begin, end);

    if (elemCount < 2)
        return;

    int pairCount = elemCount / 2;
    bool stragglerFlag = (elemCount % 2 != 0);

    Container pairs;
    It it = std::next(begin, groupSize - 1);
    It it2 = std::next(begin, 2 * groupSize - 1);Í
    pairs.reserve(pairCount);

    for (int i = 0; i < pairCount; ++i)
    {
        if (_compare(*it, *(it + 1)))
            _swap(*it +, p.second);
    }
    // // iterate through new container of pairs and fill pairs with elements
    // for (int i = 0; i < pairCount; i++)
    // {
    //     pairs.push_back(*it);
    // }

    // #####################################
    // ### AT RECURSION: take groupSize * 2
    // #####################################

    // iterate through pairs and swap if neccessary
    for (auto &p : pairs)
    {
        if (PmergeMeVec::_compare(p.first, p.second))
            _swap(p.first, p.second);
    }

    // handle straggler:
    int straggler;
    if (stragglerFlag) // alternatively: (it != end)
        straggler = *std::prev(end);

    // sort pairs
    for (std::size_t i = 0; i < (pairCount / 2); ++i)
    {
        if (_compare(pairs[i].second, pairs[i + 1].second)) // CONTINUE HERE -> LOOP STOPS WAY TOO EARLY
            _swap(pairs[i], pairs[i + 1]);                  // fix types
        i += 2;
    }

    // Build main chain S
    std::vector<int> S;

    // Iterate through the pairs to build the main chain S from the larger elements
    S.reserve(elemCount);
    if (pairCount > 0)
        S.push_back(pairs[0].first); // b1

    for (std::size_t i = 1; i < pairCount; ++i)
    {
        S.push_back(pairs[i].second); // all a's            TODO: START AT 1 OR 0????
    }

    // Build pend P
    std::vector<int> P;
    P.reserve(pairCount);
    for (std::size_t i = 1; i < pairCount; ++i)
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
        std::size_t nextJacob;

        while (insertCount < pendAmount)
        {
            nextJacob = currJacob + 2 * prevJacob;

            // needed for overflow protection
            if (nextJacob < currJacob)
                nextJacob = std::numeric_limits<std::size_t>::max();

            std::size_t limUpper = std::min(nextJacob, pendAmount + 1);

            for (std::size_t i = limUpper; i > currJacob; --i)
            {
                if (i < 2)
                    continue;
                std::size_t pendIndex = i - 2;

                if (pendIndex < pendAmount && !pendAlreadyInserted[pendIndex])
                {
                    auto &currElem = P[pendIndex];
                    auto &upperBoundVal = pairs[i - 1].second;
                    auto upperBoundIt = std::lower_bound(S.begin(), S.end(), upperBoundVal); // WHAT std::lower_bound(first, last, value)
                    auto insertPosIt = std::lower_bound(S.begin(), upperBoundIt, currElem);
                    S.insert(insertPosIt, currElem);
                    ++insertCount;
                    pendAlreadyInserted[pendIndex] = true;
                }
            }
            prevJacob = currJacob;
            currJacob = nextJacob;
            kJacob++;

            if (currJacob >= pendAmount + 1 && prevJacob >= pendAmount + 1 && insertCount < pendAmount)
            {
                break;
                // check for mistakes and leftover stragglers here if neccessary
            }
            // SAME LOOP AS ABOVE, should only trigger in case of error. FAILSAFE. Make changes to both loops if necessary
            if (kJacob > pendAmount + 5)
            {
                for (std::size_t i = 0; i < pendAmount; ++i)
                {
                    if (!pendAlreadyInserted[i])
                    {
                        auto &currElem = P[i];
                        auto &upperBoundVal = pairs[i + 1].first;
                        auto upperBoundIt = std::lower_bound(S.begin(), S.end(), upperBoundVal);
                        auto insertPosIt = std::lower_bound(S.begin(), upperBoundIt, currElem);
                        S.insert(insertPosIt, currElem);
                        ++insertCount;
                        pendAlreadyInserted[i] = true;
                    }
                }
                break;
            }
        }
    }
    if (stragglerFlag)
    {
        auto insertPosIt = std::lower_bound(S.begin(), S.end(), straggler);
        S.insert(insertPosIt, straggler);
    }
    // Overwrite the original Container
    std::move(S.begin(), S.end(), begin);
}
