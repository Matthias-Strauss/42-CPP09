/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:09 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 01:01:50 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

BitcoinExchange::BitcoinExchange() = delete{}

BitcoinExchange::BitcoinExchange(std::string fileName){
    _parseInputFile(fileName);
    _parseDbFile("data.csv");
    _printOut();
}

BitcoinExchange::BitcoinExchange(const BitcoinExchange &src){}

BitcoinExchange::BitcoinExchange &operator=(const BitcoinExchange &rhs){}

BitcoinExchange::~BitcoinExchange(){}

void BitcoinExchange::_parseInputFile(const std::string &filename){}

void BitcoinExchange::_parseDbFile(const std::string &filename){}

void BitcoinExchange::_printOut(){}