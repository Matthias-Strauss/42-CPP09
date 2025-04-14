/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:54 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/14 15:26:33 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <array>
#include <ctime>
#include <iostream>
#include <vector>

int main(int ac, char **av) {

  std::vector<int> vector;
  std::array<int, 10> array; // Allocate later with dynamic size

  if (ac == 1) {
    std::cout << "Usage: ./PmergeMe [range of integers]" << std::endl;
    return 1;
  }

  try {
    save old_time1;
    fordJohnsonAlgo(vector);
    save new_time1;
    time1 = new_time1 - old_time1;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << Container << " : " << time1 << "ms" << std::endl;
    save old_time2;
    fordJohnsonAlgo(vector);
    save new_time2;
    time1 = new_time2 - old_time2;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << Container << " : " << time2 << "ms" << std::endl;
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}