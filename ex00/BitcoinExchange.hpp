/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:12 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 03:45:50 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#pragma once
#ifndef BITCOINEXCHANGE_HPP
#define BITCOINEXCHANGE_HPP

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <map>
#include <stdexcept>
#include <cstdlib> 
#include <ctime>

class BitcoinExchange
{
public:
    BitcoinExchange() = delete;
    BitcoinExchange(std::string fileName);
    BitcoinExchange(const BitcoinExchange &src);
    BitcoinExchange &operator=(const BitcoinExchange &rhs);
    ~BitcoinExchange();

private:
    std::string _inputFile;
    std::string _dbFile;
    std::map<std::string, double> _db;

    void _parseInputFile();
    void _parseDbFile();
    bool _isValiDate(const std::string& date);
    bool _isValidDbValue(const std::string& valueStr, double& value);
    bool _isValidInputValue(const std::string& valueStr, double& value);
    double _findExchangeRate(const std::string& date);
    std::string _trim(const std::string& str);
};

class DbError : public std::exception
{
public:
    DbError(const std::string &message) : _message(message) {}
    virtual const char *what() const throw()
    {
        return _message.c_str();
    }
private:
    std::string _message = "DB Error";
};

class InputError : public std::exception
{
public:
    InputError(const std::string &message) : _message(message) {}
    virtual const char *what() const throw()
    {
        return _message.c_str();
    }
private:
    std::string _message = "Input Error";
};

#endif