/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   RNP.cpp                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/22 01:05:14 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 01:31:38 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "RNP.hpp"

RNP::RNP(std::string fileName) {

    std::ifstream file(fileName);
    if (!file.is_open()) {
        throw std::runtime_error("Could not open file");
    }
    std::string line;
    while (std::getline(file, line)) {
        std::istringstream iss(line);
        std::string token;
        while (std::getline(iss, token, ' ')) {
            this->push(token);
        }
    }
}


RNP::RNP(const RNP &src) {
    *this = src;
}
RNP::~RNP() {}
RNP& RNP::&operator=(const RNP &rhs) {}
