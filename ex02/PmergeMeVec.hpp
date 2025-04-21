/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   PmergeMeVec.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/19 18:31:18 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 21:46:54 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef PMERGEMEVEC_HPP
#define PMERGEMEVEC_HPP
#include <iostream>
#include <type_traits>
#include <vector>
#include <deque>
#include <iterator>
#include <utility>
#include <limits>
#include <algorithm>
#include <chrono>

#define DEBUG 0
#define ALLOW_DUPS 0
#define SORTED 0

template <typename T>
struct is_supported_container : std::disjunction<std::is_same<T, std::vector<int>>, std::is_same<T, std::deque<int>>>
{
};

template <typename T>
inline constexpr bool is_supported_container_value = is_supported_container<T>::value;

template <typename Container, typename T = typename Container::value_type, typename It = typename Container::iterator>
class PmergeMeVec
{
    static_assert(is_supported_container_value<Container>,
                  "PMergeMeVec: Error: invalid container type. Use std::vector<int> or std::deque<int>.");

public:
    PmergeMeVec() = default;
    explicit PmergeMeVec(const Container &src) : _container(src) {}
    PmergeMeVec(const PmergeMeVec &other) = default;
    PmergeMeVec &operator=(const PmergeMeVec &other) = default;
    ~PmergeMeVec() = default;

    void fordJohnson(Container &src, int groupSize = 1);
    static void printContainer(Container &src);
    unsigned int getCount();
private:
    Container _container;
    inline static unsigned int _compCount = 0;
    bool _compare(T &a, T &b);
    void _swap(It &a, It &b, int groupSize);
    void _fill(Container &S, It &it, int groupSize);
};

#include "PmergeMeVec.tpp"
#endif