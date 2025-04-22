/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:22 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/22 03:29:43 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"
#include <iostream>
#include <stdexcept>

int main(int ac, char **av) {
	if (ac != 2) {
		std::cerr << "Error: could not open file." << std::endl;
		std::cerr << "Usage: " << av[0] << " <input_file.txt>" << std::endl;
		return 1;
	}

	try {
		BitcoinExchange btc(av[1]);
		// Processing happens in the constructor
	} catch (const DbError& e) {
		std::cerr << "Database Error: " << e.what() << std::endl;
		return 1;
	} catch (const InputError& e) {
		std::cerr << "Input Error: " << e.what() << std::endl;
		return 1;
	} catch (const std::exception& e) {
		std::cerr << "An unexpected error occurred: " << e.what() << std::endl;
		return 1;
	}

	return 0;
}

/*

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~ PLAN ~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



hardcode 'data.csv' as db file path
input file handling, catch no access, doesnt exist, empty file, wrong format, etc


parsing -> map as a container for the values
    - read data.csv file line by line
    - split by comma
    - store in map (date, value)
    - check if date is valid (YYYY-MM-DD)
    - check if value is valid (must be 0 < value < 1000)

get a line from the input file, validate it and process it. then
 print to stdout: (value * exchangeRate) according to the date
 - find matching date
    - if exact date is not found, USE THE CLOSEST PREVIOUS DATE
    - if date is earlier than first entry print an ERROR

even if we print an error, we still continue until EOF is reached




EXAMPLE:

Sample input file:
date | value
2011-01-03 | 3
2011-01-03 | 2
2011-01-03 | 1
2011-01-03 | 1.2
2011-01-09 | 1
2012-01-11 | -1
2001-42-42
2012-01-11 | 1
2012-01-11 | 2147483648

Sample database file:
2015-11-09,380.62
2015-11-12,340.81
2015-11-15,318.97
2015-11-18,333.66
2015-11-21,326.31
2015-11-24,319.64
2015-11-27,358
2015-11-30,377.27
2015-12-03,361.47
2015-12-06,387.3
2015-12-09,416.49

VVVVVVVVVVVVVVVVV

./btc
Error: could not open file.
$> ./btc input.txt
2011-01-03 => 3 = 0.9
2011-01-03 => 2 = 0.6
2011-01-03 => 1 = 0.3
2011-01-03 => 1.2 = 0.36
2011-01-09 => 1 = 0.32
Error: not a positive number.
Error: bad input => 2001-42-42
2012-01-11 => 1 = 7.1
Error: too large a number.

*/