/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:00 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 15:27:39 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <deque>
#include <vector>

template <typename Container>
class PmergeMe
{
public:
  PmergeMe() = default;
  PmergeMe(const PmergeMe &other) = default;
  PmergeMe &operator=(const PmergeMe &other) = default;
  ~PmergeMe() = default;

  void sort(Container &container);

private:
  static unsigned int _compCount;
  template <typename T>
  void PmergeMe<Container>::fordJohnson(Container &container);
};

unsigned int calcJacobsthalNum(unsigned int n);

#include "PmergeMe.tpp"

#endif PMERGEME_HPP