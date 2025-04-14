/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMe.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:02:00 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/14 19:52:24 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PMERGEME_HPP
#define PMERGEME_HPP
#include <algorithm>
#include <deque>
#include <vector>

class PMergeMe {
public:
  PMergeMe() = default;
  PMergeMe(const PMergeMe &other);
  PMergeMe &operator=(const PMergeMe &other);
  ~PMergeMe();

private:
  static int comparisons;
};

#endif PMERGEME_HPP