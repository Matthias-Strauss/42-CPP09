/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.tpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:32:40 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 18:49:40 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMeVec.hpp"

void PmergeMeVec::sort(std::vector<int> &vec)
{
    if (vec.size() < 2)
        return;

    PmergeMeVec::fordJohnson(vec.begin(), vec.end());
}

void fordJohnson(std::vector<int>::iterator begin, std::vector<int>::iterator end)
{
    unsigned int elemCount;

    elemCount = distance(begin, end);
    if (elemCount < 2)
        return;

    bool straggler = (n % 2 != 0);

    unsigned int pairCount = elemCount / 2;

    std::vector<std::pair> vec[pairCount];
    std::vector<int>::iterator it = begin;

    for (size_t i = 0; i < pairCount; i++)
    {
        for (size_t i = 0; i < 2; i++)
        {
            vec[];
        }
    }
}
