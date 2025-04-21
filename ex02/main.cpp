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

#include "PmergeMeVec.hpp"

#include <ctime>
#include <deque>
#include <iostream>
#include <vector>

double getUnixTime(void)
{
  struct timespec tv;

  if (clock_gettime(CLOCK_REALTIME, &tv) != 0)
    return 0;

  return (tv.tv_sec + (tv.tv_nsec / 1000000.0)); // FIX AND USE SUITABLE UNITS!!!!
}

int parseNumbers(int ac, char **av, std::vector<int> &vec, std::deque<int> &deq)
{
  std::vector<int> duplicateCheck;

  try
  {
    for (int i = 1; i < ac; ++i)
    {
      char *endptr;
      long num = std::strtol(av[i], &endptr, 10);

      if (*endptr != '\0')
        throw std::invalid_argument(
            "\033[31mError: Invalid input - Non-numeric character.\033[0m");
      if (num < 0)
        throw std::invalid_argument("\033[31mError: Invalid input - Negative number.\033[0m");
      if (num > std::numeric_limits<int>::max())
      {
        throw std::invalid_argument("\033[31mError: Invalid input - Number out of int "
                                    "range.\033[0m");
      }
      int intNum = static_cast<int>(num);
      for (int duplicateCheckNum : duplicateCheck)
      {
        if (duplicateCheckNum == intNum)
        {
          throw std::invalid_argument("\033[31mError: Duplicate number found.\033[0m");
        }
      }
      duplicateCheck.push_back(intNum);
      vec.push_back(intNum);
      deq.push_back(intNum);
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
    return 1;
  }
  return 0;
}

int main(int ac, char **av)
{
  if (ac == 1)
  {
    std::cout << "Usage: ./PmergeMe [range of integers]" << std::endl;
    return 1;
  }

  double start_time;
  double stop_time;
  double time_diff;

  std::vector<int> vec;
  std::deque<int> deque;
  if (parseNumbers(ac, av, vec, deque))
    return 1;

  std::cout << "ORIGINAL: \n[ ";
  for (auto &elem : vec)
    std::cout << elem << " ";
  std::cout << "]" << std::endl;

  try
  {
    start_time = getUnixTime();
    PmergeMeVec misVec(vec);
    misVec.sort(vec);
    stop_time = getUnixTime();
    time_diff = stop_time - start_time;
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << "std::vector" << " : " << time_diff << "ms" << std::endl;
    std::cout << "SORTED  : \n";
    misVec.printContainer(vec);

    // start_time = getUnixTime();
    // PmergeMeVec misDeq(deque);
    // misDeq.sort(deque);
    // stop_time = getUnixTime();
    // time_diff =  stop_time - start_time;
    // std::cout << "Time to process a range of " << ac - 1 << " elements with "
    //           << "std::deque" << " : " << time_diff << "ms" << std::endl;
    // std::cout << "SORTED  : \n";
    // misDeq.printContainer(deque);
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}

