/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:00 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/15 16:48:40 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <deque>
#include <vector>

class PmergeMe {
public:
  PmergeMe() = default;
  PmergeMe(const PmergeMe &other) = default;
  PmergeMe &operator=(const PmergeMe &other) = default;
  ~PmergeMe() = default;

  static unsigned int compCount;

private:
  template <typename T> void PmergeMe::fordJohnson(T &container, int pairSize);
};

unsigned int calcJacobsthalNum(unsigned int n);

#include "PmergeMe.tpp"

#endif PMERGEME_HPP