/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.tpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/15 13:41:25 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/19 12:57:36 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

PmergeMe::compPair();

PmergeMe::swapPair();

PmergeMe::nextElem();

template <typename T>
void PmergeMe::fordJohnson(T &container, int pairSize)
{
  T newT[];
  // Calc amount of pairs (numbers / 2)
  pairs = T.size() / 2;
  if (pairs > 1)
  {
  }
  leftover = T.size() % 2;

  // (remember straggler)
  // If only one pair -> return

  // amount of pairs odd / even ?
  // -> leave last one out later

  // Set start and End iterators (only full pairs)

  // Sort according to last element in groups only

  // CALL RECURSIVELY !!! -> different level, different grouping size

  // Create MAIN and PEND iterators

  // fill Main with all remaining a's
  // fill Pend with all remaining b's

  // if exist, add unpaired group to Pend

  // INSERTION USING JACOBSTHAL loop
  // calculate which number to insert using jacobsthal
  // determine region to insert using upper bound
  // ---------------------- HANDLE SPECIAL CASE!!!

  // Insert leftovers -- IN REVERSE ORDER
  // calc starting bound                              ---- NEED MORE DETAIL!

  // Create new vector to fill with a copy

  // write the content of copy into the original container
}