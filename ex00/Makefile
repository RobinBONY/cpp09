# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <rbony@corobizar.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 19:10:43 by rbony             #+#    #+#              #
#    Updated: 2023/03/15 19:10:43 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = btc

SRCS =	main.cpp \
		BitcoinExchange.cpp

HEADERS = BitcoinExchange.hpp

CC = c++
RM = rm -f

FLAGS = -Wall -Wextra -Werror -std=c++98

OBJS = ${SRCS:.cpp=.o}

all: $(NAME)

%.o: %.cpp $(HEADERS) Makefile
	${CC} ${FLAGS} -c $< -o $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re