/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:04:43 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 03:20:43 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RPN.hpp"
#include <iostream>
#include <string>
#include <sstream>
#include <cstdlib> 
#include <cctype>

bool isOp(const std::string &token) {
    return (token == "+" || token == "-" || token == "*" || token == "/");
}

double execOp(double a, double b, const std::string &op) {
    if (op == "*") return a * b;
    if (op == "-") return a - b;
    if (op == "+") return a + b;
    if (op == "/") {
        if (b == 0) throw RPNError("Division by zero");
        return a / b;
    }
    throw RPNError("Invalid operator '" + op + "'");
}

int main(int ac, char** av)
{
    if (ac != 2)
    {
        std::cerr << "Usage: ./RPN \"<reverse polish notation expression>\"" << std::endl;
        return 1;
    }

    RPN stack;
    std::string expression = av[1];
    std::istringstream iss(expression);
    std::string token;

    try
    {
        while (iss >> token)
        {
            if (token.length() == 1 && std::isdigit(token[0]))
                stack.push(static_cast<double>(token[0] - '0'));
            else if (token.length() == 2 && token[0] == '-' && std::isdigit(token[1]) && token[1] != '0')
                stack.push(static_cast<double>(-(token[1] - '0')));
            else if (isOp(token))
            {
                if (stack.size() < 2)
                    throw RPNError("Insufficient operands for operator '" + token + "'");
                double operand2 = stack.top(); stack.pop();
                double operand1 = stack.top(); stack.pop();
                double result = execOp(operand1, operand2, token);
                stack.push(result);
            }
            else
                throw RPNInvalidInput("Invalid token encountered: '" + token + "'");
        }
        if (stack.size() != 1)
            throw RPNError("Invalid expression format (stack size is not 1 at the end)");
        std::cout << stack.top() << std::endl;

    }
    catch (const std::exception &e)
    {
        std::cerr << e.what() << std::endl;
        return 1;
    }

    return 0;
}