# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rbony <rbony@corobizar.com>                +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/03/15 19:10:43 by rbony             #+#    #+#              #
#    Updated: 2023/03/18 12:37:27 by rbony            ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = RPN

SRCS =	main.cpp \
		RPN.cpp

HEADERS = RPN.hpp

CC = c++
RM = rm -f

FLAGS = -Wall -Wextra -Werror #-std=c++98

OBJS = ${SRCS:.cpp=.o}

all: $(NAME)

%.o: %.cpp
	${CC} ${FLAGS} -c $< -o $@

$(NAME): $(OBJS) $(HEADERS) Makefile
	$(CC) $(FLAGS) $(OBJS) -o $(NAME)

clean:
	$(RM) $(OBJS)

fclean: clean
	$(RM) $(NAME)

re:	fclean all

.PHONY: all clean fclean re