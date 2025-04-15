/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/14 15:00:54 by mstrauss          #+#             */
/*   Updated: 2025/04/14 16:51:18 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "PmergeMe.hpp"

#include <ctime>
#include <deque>
#include <iostream>
#include <vector>

double getUnixTime(void) {
  struct timespec tv;

  if (clock_gettime(CLOCK_REALTIME, &tv) != 0)
    return 0;

  return (tv.tv_sec + (tv.tv_nsec / 1000000000.0));
}

int parseNumbers(int ac, char **av, std::vector<int> *vec,
                 std::deque<int> *deq) {

  try {
    for (int i = 1; i < ac; ++i) {
      char *endptr;
      long num = std::strtol(av[i], &endptr, 10);

      if (*endptr != '\0')
        throw std::invalid_argument(
            "Error: Invalid input - Non-numeric character.");
      if (num < 0)
        throw std::invalid_argument("Error: Invalid input - Negative number.");
      if (num > std::numeric_limits<int>::max()) {
        throw std::invalid_argument("Error: Invalid input - Number out of int "
                                    "range.");
      }
      vec->push_back(static_cast<int>(num));
      deq->push_back(static_cast<int>(num));
    }
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
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
  std::deque<int> deque;
  if (parseNumbers(ac, av, &vector, &deque))
    return 1;

  try {
    start_time = getUnixTime();
    fordJohnsonAlgo(vector);
    stop_time = getUnixTime();
    time_diff = start_time - stop_time;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << "std::vector" << " : " << time_diff << "ms" << std::endl;

    start_time = getUnixTime();
    fordJohnsonAlgo(deque);
    stop_time = getUnixTime();
    time_diff = start_time - stop_time;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << "std::deque" << " : " << time_diff << "ms" << std::endl;

  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
