/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   calcMaxComp.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 12:20:50 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 12:41:23 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

/*
GOAL: calculate the max amount of comparisons the algo is allowed to make
*/

int calcMaxComp(int n)
{
    int sum = 0;
    for (int k = 1; k <= n; ++k)
    {
        double value = (3.0 / 4.0) * k;
        sum += static_cast<int>(ceil(log2(value)));
    }
    return sum;
}
