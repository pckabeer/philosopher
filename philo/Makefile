# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kpanikka <kpanikka@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/10/20 01:10:58 by kpanikka          #+#    #+#              #
#    Updated: 2022/10/20 10:44:21 by kpanikka         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= philo
cc		= gcc -g3 -pthread
CFLAG	= -Wall -Werror -Wextra
RM		= rm
RMFLAG  = -f
SRC		= util.c util1.c philo.c mutex.c

OBJS	= $(SRC:.c=.o)

all		: $(NAME)

bonus	: all

%.o : %.c
	$(CC) $(CFLAG) -c $< -o $@

clean	:
	$(RM) $(RMFLAG) $(OBJS)
fclean	: clean
	$(RM) $(RMFLAG) $(NAME)

re		: fclean all

$(NAME) : $(OBJS)
	$(cc) $(CFLAG) $(OBJS) -o $(NAME)

.PHONY : all clean fclean re
