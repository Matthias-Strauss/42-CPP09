/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:05:14 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 02:00:24 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RNP.hpp"

RNP::RNP(std::string fileName)
{

    std::ifstream file(fileName);
    if (!file.is_open())
    {
        throw std::runtime_error("Could not open file");
    }
    std::string line;
    while (std::getline(file, line))
    {
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ' '))
        {
            this->push(token);
        }
    }
}

RNP::RNP(const RNP &src)
{
    *this = src;
}

RNP::~RNP() {}

RNP &RNP::&operator=(const RNP &rhs)
{
    if (this != &rhs)
    {
        std::stack<std::string>::operator=(rhs);
    }
    return *this;
}

void RNP::_processRNP(std::string &expression)
{
    while (!_values.empty())
    {
        _values.pop();
    }

    std::istringstream iss(expression);
    std::string token;

    while (iss >> token)
    {
        if (token.size() == 1 && isdigit(token[0]))
            _values.push(static_cast<double>(token[0] - '0'));
        else if (isOperator(token))
            executeOperation(token);
        else
            throw RNPError("Error: invalid token '" + token + "'");
    }

    if (_values.size() != 1)
    {
        throw RNPError("Error: invalid expression");
    }
}

double RNP::top() const
{
    if (_values.empty())
    {
        throw RNPError("Error: stack is empty");
    }
    return _values.top();
}