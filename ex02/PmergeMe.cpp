/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:22 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/15 17:23:58 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int calcJacobsthalNum(int n) {
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return calcJacobsthalNum(n - 1) + 2 * calcJacobsthalNum(n - 2);
}
