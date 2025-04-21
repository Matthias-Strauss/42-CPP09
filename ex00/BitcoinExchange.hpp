/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:12 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 00:09:50 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP
#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

class BitcoinExchange
{
public:
    BitcoinExchange() = delete;
    BitcoinExchange(std::string fileName);
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();

private:
    void _parseInputFile(const std::string &filename);
    void _parseDbFile(const std::string &filename);
    void _printOut();

    std::map<std::string, double> _db;
};

#endif