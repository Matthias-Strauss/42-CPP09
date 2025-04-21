/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.hpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:05:14 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 01:26:47 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RNP_HPP
#define RNP_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <stack>

class RNP : std::stack<std::string>
{
public:
    RNP() = delete;
    RNP(std::string fileName);
    RNP(const RNP &src);
    RNP &operator=(const RNP &rhs);
    ~RNP();

private:
    void _processRNP(const std::string &line);
};

class RNPError : public std::exception
{
public:
    RNPError(const std::string &message) : _message(message) {}
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
