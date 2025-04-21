# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mstrauss <mstrauss@student.42heilbronn.    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/04/03 16:23:56 by mstrauss          #+#    #+#              #
#    Updated: 2025/04/21 22:08:09 by mstrauss         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = btc
CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17
SRCS = main.cpp BitcoinExchange.cpp
INC = BitcoinExchange.hpp
OBJS = $(SRCS:.cpp=.o)

all: $(NAME)

$(NAME): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(NAME)

%.o: %.cpp $(INC)
	$(CXX) $(CXXFLAGS) -c $< -o $@

re: fclean all

clean:
	rm -f $(OBJS)

fclean:
	rm -f $(OBJS) $(NAME)

.phony: all re clean fclean