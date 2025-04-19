/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:22 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 15:29:03 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

int calcJacobsthalNum(int n)
{
  if (n == 0)
    return 0;
  else if (n == 1)
    return 1;
  else
    return calcJacobsthalNum(n - 1) + 2 * calcJacobsthalNum(n - 2);
}

template <typename Container>
void sort(Container &container)
{
  static_assert(
      std::is_same<Container, std::vector<typename Container::value_type>>::value ||
          std::is_same<Container, std::deque<typename Container::value_type>>::value,
      "Container must be either std::vector or std::deque");

  if (container.size() < 2)
    return;

  fordJohnsonSort(container.begin(), container.end()){};
}