/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 12:36:33 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#include "PmergeMeVec.hpp"


template <typename Container, typename T, typename It>
void PmergeMeVec<Container, T, It>::printContainer(Container &src)
{
    std::cout << "[ ";
    for (auto &elem : src)
        std::cout << elem << " ";
    std::cout << "]" << std::endl;
}

/// @brief compairs the int values
/// @param a first int
/// @param b second int
/// @return true if FIRST > SECOND (->implying a swap is neccessary)
template <typename Container, typename T, typename It>
bool PmergeMeVec<Container, T, It>::_compare(T &a, T &b)
{
    _compCount++;
    return (a > b);
}

template <typename Container, typename T, typename It>
void PmergeMeVec<Container, T, It>::_swap(It &a, It &b, int groupSize)
{
    std::swap_ranges(a - groupSize + 1, a+1, b - groupSize + 1);
}

template <typename Container, typename T, typename It>
void PmergeMeVec<Container, T, It>::sort(Container &src)
{
    if (src.size() < 2)
        return;

    _fordJohnson(src);
}

template <typename Container, typename T, typename It>
void PmergeMeVec<Container, T, It>::_fordJohnson(Container src, int groupSize)
{
    // ######################## MEERRGGEEE ##################################
    It begin = src.begin();
    It end = src.end();
    
    int elemCount = std::distance(begin, end);
    
    if (elemCount < 2)
    return;
    
    int pairCount = elemCount / (2 * groupSize);
    if (pairCount == 0)
    return;
    // bool stragglerFlag = (elemCount % 2 != 0);
    
    It it = std::next(begin, groupSize - 1);
    It it2 = std::next(begin, 2 * groupSize - 1);
    
    for (int i = 0; i < pairCount; ++i)
    {
        if (_compare(*it, *it2))
        _swap(it, it2, groupSize);
        it = std::next(it, 2 * groupSize);
        it2 = std::next(it2, 2 * groupSize);
    }
    printContainer(src);
    _fordJohnson(src, groupSize * 2); // RECURSION :O
    
    // ######################## INSSEEEERT ##################################

//     // Build main chain S
//     Container<int> S;

//     // Iterate through the pairs to build the main chain S from the larger elements
//     S.reserve(elemCount);
//     if (pairCount > 0)
//         S.push_back(); // b1

//     for (int i = 1; i < pairCount; ++i)
//     {
//         S.push_back(pairs[i].second); // all a's            TODO: START AT 1 OR 0????
//     }

//     // Build pend P
//     Container<int> P;
//     P.reserve(pairCount);
//     for (int i = 1; i < pairCount; ++i)
//     {
//         P.push_back(pairs[i].first); // remaining b's
//     }

//     int pendAmount = P.size();

//     if (pendAmount > 0)
//     {
//         std::vector<bool> pendAlreadyInserted(pendAmount, false); // check values to keep track of already inserted elements
//         int insertCount = 0;

//         int prevJacob = 0;
//         int currJacob = 1;
//         int kJacob = 2;
//         int nextJacob;

//         while (insertCount < pendAmount)
//         {
//             nextJacob = currJacob + 2 * prevJacob;

//             // needed for overflow protection
//             if (nextJacob < currJacob)
//                 nextJacob = std::numeric_limits<int>::max();

//             int limUpper = std::min(nextJacob, pendAmount + 1);

//             for (int i = limUpper; i > currJacob; --i)
//             {
//                 if (i < 2)
//                     continue;
//                 int pendIndex = i - 2;

//                 if (pendIndex < pendAmount && !pendAlreadyInserted[pendIndex])
//                 {
//                     auto &currElem = P[pendIndex];
//                     auto &upperBoundVal = pairs[i - 1].second;
//                     auto upperBoundIt = std::lower_bound(S.begin(), S.end(), upperBoundVal); // WHAT std::lower_bound(first, last, value)
//                     auto insertPosIt = std::lower_bound(S.begin(), upperBoundIt, currElem);
//                     S.insert(insertPosIt, currElem);
//                     ++insertCount;
//                     pendAlreadyInserted[pendIndex] = true;
//                 }
//             }
//             prevJacob = currJacob;
//             currJacob = nextJacob;
//             kJacob++;

//             if (currJacob >= pendAmount + 1 && prevJacob >= pendAmount + 1 && insertCount < pendAmount)
//             {
//                 break;
//                 // check for mistakes and leftover stragglers here if neccessary
//             }
//             // SAME LOOP AS ABOVE, should only trigger in case of error. FAILSAFE. Make changes to both loops if necessary
//             if (kJacob > pendAmount + 5)
//             {
//                 for (int i = 0; i < pendAmount; ++i)
//                 {
//                     if (!pendAlreadyInserted[i])
//                     {
//                         auto &currElem = P[i];
//                         auto &upperBoundVal = pairs[i + 1].first;
//                         auto upperBoundIt = std::lower_bound(S.begin(), S.end(), upperBoundVal);
//                         auto insertPosIt = std::lower_bound(S.begin(), upperBoundIt, currElem);
//                         S.insert(insertPosIt, currElem);
//                         ++insertCount;
//                         pendAlreadyInserted[i] = true;
//                     }
//                 }
//                 break;
//             }
//         }
//     }
//     if (stragglerFlag)
//     {
//         auto insertPosIt = std::lower_bound(S.begin(), S.end(), straggler);
//         S.insert(insertPosIt, straggler);
//     }
//     // Overwrite the original Container
//     std::move(S.begin(), S.end(), begin);
// }
}