/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 21:57:47 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

template <typename Container, typename T, typename It>
void PmergeMeVec<Container, T, It>::_fill(Container &Main, It &it, int groupSize)
{
    for (int i = 0; i < groupSize; ++i)
    {
        Main.push_back(*it);
        it++;
    }
}

template <typename Container, typename T, typename It>
unsigned int PmergeMeVec<Container, T, It>::getCount(){return _compCount;};

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

    It first1 = std::prev(a, groupSize - 1);
    It first2 = std::prev(b, groupSize - 1);
    It last1 = std::next(a);

    std::swap_ranges(first1, last1, first2);
}

template <typename Container, typename T, typename It>
void PmergeMeVec<Container, T, It>::fordJohnson(Container &src, int groupSize)
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
    // printContainer(src); //DEBUG
    PmergeMeVec<Container, T, It>::fordJohnson(src, groupSize * 2); // RECURSION :O

    // ##################### BUILD MAIN AND PEND ##############################

    // BUILDING MAIN CHAIN (Main)
    Container Main{};
    // Main.reserve(elemCount);
    Container Pend{};
    // Pend.reserve(elemCount);

    it = src.begin();
    it2 = std::next(begin, groupSize * 2); // CHECK VALUE OF *2!!!!
    end = src.end();

    if(DEBUG){
    std::cout << "\nsrc: " << std::endl;
    printContainer(src);}
    // Iterate through the pairs to build the main chain Main from the larger elements
    // Main.reserve(elemCount); should be handled by constructor
    if (pairCount > 0)
        _fill(Main, it, groupSize); // add a1

    while (std::distance(it, end) >= groupSize)
    {
        _fill(Main, it, groupSize); // add b_k's to main
        if (std::distance(it, end) >= groupSize)
            _fill(Pend, it, groupSize); // add a_k's to pend
    }

    bool stragglerFlag = (std::distance(it, end) > 0); // PART OF GARBAGe
    It straggler;                                      // PART OF GARBAGe

    if (stragglerFlag)
        straggler = it;

    if (DEBUG)
    {
        std::cout << std::endl;
        std::cout << "~~~ After building Main and Pend ~~~" << std::endl; // DEBUG
        std::cout << "Main: ";                                            // DEBUG
        printContainer(Main);
        std::cout << "Pend: "; // DEBUG
        printContainer(Pend);
        std::cout << "Straggler: " << stragglerFlag;                // DEBUG
        std::cout << "      groupSize: " << groupSize << std::endl; // DEBUG
        std::cout << "      straggler: ";                           // DEBUG
        if (stragglerFlag)
        {
            It stragglerCopy = straggler;
            int nummer = 0;
            while (nummer < std::distance(stragglerCopy, src.end())) // DEBUG
            {
                std::cout << *stragglerCopy++ << " "; // DEBUG
            }
        }
        std::cout << std::endl;
    }

    // ##################### INSERTIIIIIIING ##############################
    int pendGroupCount = Pend.size() / groupSize;

    //
    if (pendGroupCount > 0)
    {
        std::vector<bool> inserted(pendGroupCount + 1, false);
        inserted[0] = true; // 0 is not used, but we need to keep track of the indices
        int insertCount = 1;

        long long prevJ = 1;
        long long currJ = 3;

        while (insertCount <= pendGroupCount)
        {
            long long nextJ;
            if (prevJ > (std::numeric_limits<long long>::max() - currJ) / 2)
                nextJ = std::numeric_limits<long long>::max();
            else
                nextJ = currJ + 2 * prevJ;

            int limit = std::min((long long)pendGroupCount, currJ - 1);

            if (DEBUG)
            {
                std::cout << "Jacobsthal step: prevJ=" << prevJ << ", currJ=" << currJ << " (limit=" << limit << "). Inserting indices (k): ";
            }

            for (int k = limit; k > static_cast<int>(prevJ - 1); --k)
            {
                if (k >= 0 && k <= pendGroupCount && !inserted[k])
                {
                    if (DEBUG)
                        std::cout << k << " ";

                    int pendIndex = k - 1;

                    if (pendIndex * groupSize >= static_cast<int>(Pend.size()))
                        continue;
                    It b_k_start = Pend.begin();
                    std::advance(b_k_start, pendIndex * groupSize);
                    It b_k_end = std::next(b_k_start, groupSize);

                    Container current_b_group_vec(b_k_start, b_k_end);
                    T &value_to_insert = current_b_group_vec.back();

                    size_t current_main_size = Main.size();
                    size_t search_limit_idx = std::min((size_t)k + insertCount, current_main_size / groupSize);
                    It search_range_end = Main.begin();
                    std::advance(search_range_end, std::min(search_limit_idx * groupSize + groupSize, current_main_size));

                    std::vector<It> temp_its;
                    for (size_t i = groupSize - 1; i < current_main_size; i += groupSize)
                    {
                        It it = Main.begin();
                        std::advance(it, i);
                        temp_its.push_back(it);
                    }
                    typename std::vector<It>::iterator its_range_end = temp_its.begin();
                    std::advance(its_range_end, search_limit_idx);

                    auto it_first_ge = std::upper_bound(temp_its.begin(), its_range_end, value_to_insert, [](const T &val, const It &it)
                                                        { return val < *it; });
                    It insertPosIt;
                    if (it_first_ge == temp_its.end())
                        insertPosIt = Main.end();
                    else
                        insertPosIt = *it_first_ge;

                    size_t distance = std::distance(Main.begin(), insertPosIt);
                    size_t insert_idx = (distance / groupSize) * groupSize;

                    It insertPosGroupIt = Main.begin();
                    std::advance(insertPosGroupIt, insert_idx);
                    if (DEBUG)
                    {
                        std::cout << "Inserting b" << k << " (value=" << value_to_insert << ", size=" << groupSize << ") at index " << insert_idx << std::endl;
                        printContainer(current_b_group_vec);
                    }
                    Main.insert(insertPosGroupIt, current_b_group_vec.begin(), current_b_group_vec.end());

                    inserted[k] = true;
                    insertCount++;

                    if (DEBUG)
                    {
                    }
                }
            }
            if (DEBUG)
                std::cout << std::endl;

            prevJ = currJ;
            currJ = nextJ;

            if (currJ <= 0 || prevJ < 0)
                break;
        }

        if (insertCount < pendGroupCount)
        {
            if (DEBUG)
                std::cout << "Warning: Jacobsthal loop finished with " << pendGroupCount - insertCount << " elements remaining. Inserting failsafe." << std::endl;
        }
    }

    if (stragglerFlag)
        while (straggler < src.end())
            Main.push_back(*straggler++);
    src.assign(Main.begin(), Main.end());
}

// for (int k = 1; k <= pendGroupCount; ++k)
// {
//     if (!inserted[k])
//     {
//         int pendIndex = k - 1;
//         It b_k_start = Pend.begin();
//         std::advance(b_k_start, pendIndex * groupSize);
//         It b_k_end = std::next(b_k_start, groupSize);
//         std::vector<T> current_b_group_vec(b_k_start, b_k_end);
//         T &value_to_insert = current_b_group_vec.back();

//         auto it_first_ge = std::lower_bound(Main.begin(), Main.end(), value_to_insert);
//         size_t distance = std::distance(Main.begin(), it_first_ge);
//         size_t insert_idx = (distance / groupSize) * groupSize;
//         It insertPosGroupIt = Main.begin();
//         std::advance(insertPosGroupIt, insert_idx);
//         Main.insert(insertPosGroupIt, current_b_group_vec.begin(), current_b_group_vec.end());

//         insertCount++;
//         if (DEBUG)
//         {
//             std::cout << "Failsafe inserted b" << k << std::endl;
//         }
//     }
// }

// if (stragglerFlag && groupSize == 1) /// MADE CHANGES Here< MAYBE DELEte LATER
// {
//     size_t stragglerActualSize = std::distance(straggler, src.end());

//     if (stragglerActualSize > 0)
//     {
//         It straggler_end_it = straggler;
//         std::advance(straggler_end_it, stragglerActualSize);
//         std::vector<T> straggler_group_vec(straggler, straggler_end_it);

//         T &straggler_val = straggler_group_vec.back();

//         auto it_first_ge = std::lower_bound(Main.begin(), Main.end(), straggler_val);

//         size_t distance = std::distance(Main.begin(), it_first_ge);

//         size_t insert_idx = (distance / groupSize) * groupSize;
//         It insertPosGroupIt = Main.begin();
//         std::advance(insertPosGroupIt, insert_idx);

//         Main.insert(insertPosGroupIt, straggler_group_vec.begin(), straggler_group_vec.end());

//         if (DEBUG)
//         {
//             std::cout << "Inserted Straggler (defining value=" << straggler_val << ", size=" << stragglerActualSize << "). Final Main: ";
//             printContainer(Main);
//         }
//     }
//     else if (DEBUG)
//     {
//         std::cout << "Straggler detected but size is 0." << std::endl;
//     }
// }
// else if (DEBUG)
// {
//     std::cout << "No straggler inserted during this step." << std::endl;
// }

// #################################
// ###### GARBAGE STARTS HERE ######
// #################################

//     int pendAmount = Pend.size() / groupSize;

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
//                     auto &currElem = Pend[pendIndex];
//                     auto &upperBoundVal = pairs[i - 1].second;
//                     auto upperBoundIt = std::lower_bound(Main.begin(), Main.end(), upperBoundVal); // WHAT std::lower_bound(first, last, value)
//                     auto insertPosIt = std::lower_bound(Main.begin(), upperBoundIt, currElem);
//                     Main.insert(insertPosIt, currElem);
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
//                 std::cout << "Error: FAILSAFE triggered" << std::endl;
//                 for (int i = 0; i < pendAmount; ++i)
//                 {
//                     if (!pendAlreadyInserted[i])
//                     {
//                         auto &currElem = Pend[i];
//                         auto &upperBoundVal = pairs[i + 1].first;
//                         auto upperBoundIt = std::lower_bound(Main.begin(), Main.end(), upperBoundVal);
//                         auto insertPosIt = std::lower_bound(Main.begin(), upperBoundIt, currElem);
//                         Main.insert(insertPosIt, currElem);
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
//         auto insertPosIt = std::lower_bound(Main.begin(), Main.end(), straggler);
//         Main.insert(insertPosIt, straggler);
//     }
//     // Overwrite the original Container
//     std::move(Main.begin(), Main.end(), begin);
// }
