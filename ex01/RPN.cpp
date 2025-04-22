/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:05:14 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 03:01:37 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"

RPN::RPN() : std::stack<double>() {}

RPN::RPN(const RPN &src) : std::stack<double>(src) {}

RPN &RPN::operator=(const RPN &rhs)
{
    if (this != &rhs)
    {
        std::stack<double>::operator=(rhs);
    }
    return *this;
}

RPN::~RPN() {}