/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BitcoinExchange.cpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:09 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 03:46:46 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"


std::string BitcoinExchange::_trim(const std::string& str) {
    const std::string whitespace = " \t\n\r\f\v";

    size_t first = str.find_first_not_of(whitespace);
    if (first == std::string::npos)
        return "";
    size_t last = str.find_last_not_of(whitespace);
    return str.substr(first, (last - first + 1));
}


bool BitcoinExchange::_isValiDate(const std::string& date) {
    struct tm tm = {};
    char *ptr = strptime(date.c_str(), "%Y-%m-%d", &tm);

    if (ptr == NULL || *ptr != '\0') return false;

    int year = tm.tm_year + 1900;
    int month = tm.tm_mon + 1;
    int day = tm.tm_mday;

    if (month < 1 || month > 12 || day < 1 || day > 31) return false;

    if ((month == 4 || month == 6 || month == 9 || month == 11) && day > 30) return false;

    if (month == 2) {
        bool isLeap = (year % 4 == 0 && year % 100 != 0) || (year % 400 == 0);
        if (day > (isLeap ? 29 : 28)) return false;
    }

    char buf[11];
    strftime(buf, sizeof(buf), "%Y-%m-%d", &tm);
    return date == buf;
}


bool BitcoinExchange::_isValidDbValue(const std::string& valueStr, double& value) {
    char* end;
    value = std::strtod(valueStr.c_str(), &end);
    if (*end != '\0' || valueStr.empty()) {
        return false;
    }
    if (value < 0) {
        return false;
    }
    return true;
}

// Validate input value (0 <= value <= 1000)
bool BitcoinExchange::_isValidInputValue(const std::string& valueStr, double& value) {
    char* end;
    value = std::strtod(valueStr.c_str(), &end);
    if (*end != '\0' || valueStr.empty()) {
        if (_trim(valueStr).empty()) return false;
        std::string remaining = end;
        if (remaining.find_first_not_of(" \t\n\r\f\v") != std::string::npos) {
             return false;
        }
    }
    if (value < 0) {
        std::cerr << "Error: not a positive number." << std::endl;
        return false;
    }
    if (value > 1000) {
        std::cerr << "Error: too large a number." << std::endl;
        return false;
    }
    return true;
}

double BitcoinExchange::_findExchangeRate(const std::string& date) {
    if (_db.empty()) {
        throw DbError("Database is empty.");
    }
    std::map<std::string, double>::iterator it = _db.lower_bound(date);
    if (it != _db.end() && it->first == date) {
        return it->second;
    }
    if (it == _db.begin()) {
         std::cerr << "Error: No data available for or before date => " << date << std::endl;
         return -1.0;
    }
    --it;
    return it->second;
}

BitcoinExchange::BitcoinExchange(std::string fileName) : _inputFile(fileName), _dbFile("data.csv") {
    try {
        _parseDbFile();
        _parseInputFile();
    } catch (const std::exception& e) {
        throw;
    }
}

BitcoinExchange::~BitcoinExchange() {}


void BitcoinExchange::_parseDbFile() {
    std::ifstream dbStream(_dbFile.c_str());
    if (!dbStream.is_open()) {
        throw DbError("Could not open database file: " + _dbFile);
    }

    std::string line;
    std::getline(dbStream, line);

    if (_trim(line) != "date,exchange_rate") {
         std::cerr << "Warning: Unexpected database header format." << std::endl;
    }

    while (std::getline(dbStream, line)) {
        std::stringstream ss(line);
        std::string dateStr;
        std::string valueStr;
        double value;

        if (std::getline(ss, dateStr, ',') && std::getline(ss, valueStr)) {
            dateStr = _trim(dateStr);
            valueStr = _trim(valueStr);

            if (!_isValiDate(dateStr)) {
                std::cerr << "Warning: Invalid date format in database => " << line << std::endl;
                continue;
            }
            if (!_isValidDbValue(valueStr, value)) {
                 std::cerr << "Warning: Invalid value format in database => " << line << std::endl;
                 continue;
            }
            _db[dateStr] = value;
        } else {
             std::cerr << "Warning: Invalid line format in database => " << line << std::endl;
        }
    }
    if (_db.empty()) {
        throw DbError("Database file is empty or contains no valid data.");
    }
}


void BitcoinExchange::_parseInputFile() {
    std::ifstream inputStream(_inputFile.c_str());
     if (!inputStream.is_open()) {
        throw InputError("Could not open input file: " + _inputFile);
    }

    std::string line;
    std::getline(inputStream, line);

    if (_trim(line) != "date | value") {
        std::cerr << "Error: Invalid input file header format." << std::endl;
        inputStream.clear();
        inputStream.seekg(0, std::ios::beg);
    }

    while (std::getline(inputStream, line)) {
        std::stringstream ss(line);
        std::string dateStr;
        std::string separator;
        std::string valueStr;
        double inputValue;

        if (std::getline(ss, dateStr, '|') && std::getline(ss, valueStr)) {
            dateStr = _trim(dateStr);
            valueStr = _trim(valueStr);

            if (!_isValiDate(dateStr)) {
                std::cerr << "Error: bad input => " << dateStr << std::endl;
                continue;
            }

            if (!_isValidInputValue(valueStr, inputValue)) {
                continue;
            }

            double exchangeRate = _findExchangeRate(dateStr);
            if (exchangeRate < 0) {
                continue;
            }

            double result = inputValue * exchangeRate;
            std::cout << dateStr << " => " << inputValue << " = " << result << std::endl;

        } else {
            std::string trimmedLine = _trim(line);
            if (!trimmedLine.empty()) {
                 std::cerr << "Error: bad input => " << line << std::endl;
            }
        }
    }
}