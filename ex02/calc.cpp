/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calc.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/21 06:11:56 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 06:55:31 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <vector>
#include <iostream>
#include <deque>
#include <stdexcept>
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

// void sort()
int main()
{
    std::vector<int> vec = {25, 24, 23, 22, 21, 20, 19, 18, 17, 16, 15, 14, 13, 12, 11, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1, 0};

    size_t comparisonCount = 0;
    size_t numCount = vec.size();
    size_t groupSize = 2;
    size_t i;
    size_t j;

    while (groupSize <= numCount)
    {
        for (i = 0; i < numCount; i += groupSize)
        {
            printVec(&vec);
            for (j = i; j < i + groupSize - 1 && j < numCount; ++j)
            {
                ++comparisonCount;
                if (vec.at(i) > vec.at(j + groupSize - 1))
                {
                    std::swap_ranges(vec.at(i), vec.at(), vec[j + 1]);
                }
            }
        }
        groupSize *= 2;
    }
}

// i want to:

// compare vec[0] with vec[1]
// compare vec[1] with vec[3]
// compare vec[3] with vec[7]
// compare vec[7] with vec[15]

{
    size_t index1 = k;
    size_t index2 = 2 * k + 1;

    // Check if the second index is within bounds
    if (index2 >= numCount)
    {
        std::cout << "Stopping: Index " << index2 << " is out of bounds (size=" << numCount << ")." << std::endl;
        break;
    }
}