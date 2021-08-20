# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jkhong <jkhong@student.42kl.edu.my>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/08/16 13:18:28 by jkhong            #+#    #+#              #
#    Updated: 2021/08/20 18:38:55 by jkhong           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS		=	$(wildcard srcs/*.c)
OBJS		=	${SRCS:.c=.o}
HEADER		=	-I ./includes
CC			=	gcc
CFLAGS		=	-Wall -Wextra -Werror
NAME		=	philo

%.o: %.c
			$(CC) $(CFLAGS) -c $(HEADER) $< -o ${<:.c=.o}

all:		$(NAME)

$(NAME): 	$(OBJS)
			$(CC) $(CFLAGS) -pthread -o  $(NAME) $(OBJS)

clean:
			rm -f $(OBJS)

fclean:		clean
			rm -f $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
