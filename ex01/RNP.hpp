/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:05:14 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 01:59:21 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNP_HPP
#define RNP_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

/*
Container choice : STD::STACK
- Stack is a LIFO (Last In First Out) data structure.
*/
class RNP : std::stack<std::string>
{
public:
    RNP() = delete;
    RNP(std::string input);
    RNP(const RNP &src);
    RNP &operator=(const RNP &rhs);
    ~RNP();
    
    void processRNP(std::string &input);

private:
    void _calculate(std::string token);
    void pop();
    void push(const std::string &token);
    double top() const;
    
    bool isOperator(const std::string &token) const;
    double applyOperator(double a, double b, const std::string &op) const;
};

class RNPError : public std::exception
{
public:
    RNPError(const std::string &message) : _message(message) {}
    virtual ~RNPError() throw();
    virtual const char *what() const throw()
    {
        return _message.c_str();
    }
    private:
    std::string _message = "RNP Error: ";
};

class RNPInvalidInput : public RNPError
{
public:
    RNPInvalidInput(const std::string &message) : RNPError(message) {}

    virtual const char *what() const throw()
    {
        return ("RNP Invalid Input: " + _message).c_str();
    }
        private:
    std::string _message = " the input you gave is invalid";
};
