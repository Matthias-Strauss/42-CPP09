/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.cpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:03:22 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 18:32:32 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <iterator> //debug

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

// template <typename Container>
// void PmergeMe<Container>::fordJohnson(typename Container::iterator begin, typename Container::iterator end)
// {

//   if (distance(begin, end) < 2)
//     return;

//   unsigned int count = distance(begin, end);
//   unsigned int hasStraggler = (count % 2 != 0);
//   unsigned int pairs = count / 2;

//   Container cont(pairs);
// }

template <typename Container>
void PmergeMe<Container>::fordJohnson(typename Container::iterator begin, typename Container::iterator end, vector_tag)
{
  // Implementation for vector
  std::cout << "Ford-Johnson algorithm for vector" << std::endl; // Example
}

template <typename Container>
void PmergeMe<Container>::fordJohnson(typename Container::iterator begin, typename Container::iterator end, deque_tag)
{
  // Implementation for deque
  std::cout << "Ford-Johnson algorithm for deque" << std::endl; // Example
}