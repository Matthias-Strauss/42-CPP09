/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:54 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/14 15:50:20 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"
#include <array>
#include <ctime>
#include <iostream>
#include <vector>

double getUnixTime(void) {
  struct timespec tv;

  if (clock_gettime(CLOCK_REALTIME, &tv) != 0)
    return 0;

  return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}

int main(int ac, char **av) {

  if (ac == 1) {
    std::cout << "Usage: ./PmergeMe [range of integers]" << std::endl;
    return 1;
  }

  double start_time = getUnixTime();
  double stop_time;
  double time_diff;

  std::vector<int> vector;
  std::array<int, 10> array; // Allocate later with dynamic size

  try {
    start_time = getUnixTime();
    fordJohnsonAlgo(vector);
    stop_time = getUnixTime();
    time_diff = start_time - stop_time;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << Container << " : " << time_diff << "ms" << std::endl;

    start_time = getUnixTime();
    fordJohnsonAlgo(vector);
    stop_time = getUnixTime();
    time_diff = start_time - stop_time;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << Container << " : " << time_diff << "ms" << std::endl;

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}