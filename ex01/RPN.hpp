/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RPN.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:05:14 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 03:01:09 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RPN_HPP
#define RPN_HPP

#include <stack>
#include <string>
#include <stdexcept>
#include <iostream>

class RPN : public std::stack<double>
{
public:
    RPN();
    RPN(const RPN &src);
    RPN &operator=(const RPN &rhs);
    ~RPN();
};

class RPNError : public std::exception
{
public:
    RPNError(const std::string &message) : _message("Error: " + message) {}
    virtual const char *what() const throw() { return _message.c_str(); }
    virtual ~RPNError() throw() {}

private:
    std::string _message;
};

class RPNInvalidInput : public RPNError
{
public:
    RPNInvalidInput(const std::string &message) : RPNError("Invalid Input: " + message) {}
    virtual ~RPNInvalidInput() throw() {}
};

#endif
