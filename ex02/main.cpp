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
      if (ALLOW_DUPS)
      {
        for (int duplicateCheckNum : duplicateCheck)
        {
          if (duplicateCheckNum == intNum)
          {
            throw std::invalid_argument("\033[31mError: Duplicate number found.\033[0m");
          }
        }
        duplicateCheck.push_back(intNum);
      }
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

  // Use chrono types for timing
  std::chrono::high_resolution_clock::time_point start_time;
  std::chrono::high_resolution_clock::time_point stop_time;
  std::chrono::microseconds time_diff;

  std::vector<int> vec;
  std::deque<int> deque;
  if (parseNumbers(ac, av, vec, deque))
    return 1;

  std::cout << "Before: [ ";
  for (auto &elem : vec)
    std::cout << elem << " ";
  std::cout << "]" << std::endl;

  try
  {
    start_time = std::chrono::high_resolution_clock::now();
    PmergeMeVec misVec(vec);
    misVec.fordJohnson(vec, 1);
    stop_time = std::chrono::high_resolution_clock::now();
    time_diff = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
    std::cout << "Sorted: ";
    misVec.printContainer(vec);
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << "std::vector" << " : " << time_diff.count() << " us" << std::endl;
    start_time = std::chrono::high_resolution_clock::now();
    PmergeMeVec misDeq(deque);
    misDeq.fordJohnson(deque, 1);
    stop_time = std::chrono::high_resolution_clock::now();
    time_diff = std::chrono::duration_cast<std::chrono::microseconds>(stop_time - start_time);
    std::cout << "Time to process a range of " << ac - 1 << " elements with "
              << "std::deque" << " : " << time_diff.count() << " us" << std::endl;
    if (SORTED)
    {
      if (std::is_sorted(vec.begin(), vec.end()))
        std::cout << "std::vector successfully sorted!" << std::endl;
      else
        std::cout << "std::vector unsuccessfully sorted!" << std::endl;
      if (std::is_sorted(deque.begin(), deque.end()))
        std::cout << "std::deque successfully sorted!" << std::endl;
      else
        std::cout << "std::deque unsuccessfully sorted!" << std::endl;
    }
  }
  catch (const std::exception &e)
  {
    std::cerr << e.what() << '\n';
  }
  return 0;
}
