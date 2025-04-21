/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/13 14:05:22 by mstrauss          #+#    #+#             */
/*   Updated: 2025/04/21 23:56:59 by mstrauss         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "BitcoinExchange.hpp"

int main(int ac, char **av) { return 0; }

/*

~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~ PLAN ~~~~~~~~~~~~~~~~~~
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~



hardcode 'data.csv' as db file path
input file handling, catch no access, doesnt exist, empty file, wrong format, etc


parsing -> map as a container for the values
    - read file line by line
    - split by comma
    - store in map (date, value)
    - check if date is valid (YYYY-MM-DD)
    - check if value is valid (must be 0 < value < 1000)

 print to stdout: (value * exchangeRate) according to the date
 - find matching date
    - if exact date is not found, USE THE CLOSEST PREVIOUS DATE
    - if date is earlier than first entry print an ERROR



EXAMPLE:

head input.txt
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