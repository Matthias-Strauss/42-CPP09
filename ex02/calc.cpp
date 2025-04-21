/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 06:11:56 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 08:17:38 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <deque>
#include <stdexcept>
#include <iterator>
// #include <algorithm>

// ~~~~~~~~~~~~~
//    NOTES
// ~~~~~~~~~~~~~
// std::swap_ranges(src iterator start, src iterator end, dest iterator start);
// or
// std::swap_ranges(src.begin(), src.end(), dest.begin());

void printVec(std::vector<int> *vec)
{
    for (auto elem : *vec)
        std::cout << elem << " ";
    std::cout << std::endl;
}

template <typename It>
void printRange(It first, It last)
{
    if (first == last)
    {
        return;
    }
    std::copy(first, last, std::ostream_iterator<typename std::iterator_traits<It>::value_type>(std::cout, " "));
    std::cout << std::endl;
}

template <typename It>
void recursiveMergeSort(It first, It last)
{
    auto n = std::distance(first, last);
    if (n <= 1)
        return;
    printRange(first, last);
    auto mid = std::next(first, n / 2);
    recursiveMergeSort(first, mid);
    recursiveMergeSort(mid, last);
    std::inplace_merge(first, mid, last);
}

template <typename It, typename Container>
void safeSwapRange(Container &src, It first, It last, It dest)
{
    // static_assert(std::is_base_of_v<std::random_access_iterator_tag, typename std::iterator_traits<It>::iterator_category>); // assert compatible iterator (vector in this case)
    auto n = std::distance(first, last);

    if (first < src.begin() || last > src.end())
        throw std::out_of_range("First Iterator out of range");
    if (dest < src.begin() || dest + n > src.end())
        throw std::out_of_range("Second Iterator out of range");
    // if (std::distance(first, last) != std::distance(dest, last))
    //     throw std::invalid_argument("Source and destination ranges must be of equal length");
    std::swap_ranges(first, last, dest);
}

// void sort()
// int main()
// {
//     std::vector<int> vec = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
//     recursiveMergeSort(vec.begin(), vec.end());
//     printVec(&vec);
// }

int main()
{
    std::vector<int> vec = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};
    size_t comparisonCount = 0;
    size_t numCount = vec.size();
    size_t groupSize = 1;
    size_t i;
    size_t j;

    while (groupSize <= numCount / 2)
    {
        for (i = 0; i < numCount; i += groupSize)
        {
            printVec(&vec);
            {
                j = i + groupSize;
                if (j >= numCount)
                    continue;
                ++comparisonCount;
                if (vec.at(i) > vec.at(i + groupSize))
                {
                    safeSwapRange(vec, vec.begin() + i, vec.begin() + i + groupSize, vec.begin() + i + groupSize + 1);
                }
            }
        }
        groupSize *= 2;
    }
}
// ####################################################
/* i want to:

compare 1,2 3,4 5,6 7,8 9,10.......
compare 2,4 6,8 10,12 14,16.......
compare 4,8 12,16 20,24.......

*/
// compare vec[0] with vec[1]
// compare vec[1] with vec[3]
// compare vec[3] with vec[7]
// compare vec[7] with vec[15]

// {
//     size_t index1 = k;
//     size_t index2 = 2 * k + 1;

//     // Check if the second index is within bounds
//     if (index2 >= numCount)
//     {
//         std::cout << "Stopping: Index " << index2 << " is out of bounds (size=" << numCount << ")." << std::endl;
//         break;
//     }
// }