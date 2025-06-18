# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/18 10:16:00 by kevwang           #+#    #+#              #
#    Updated: 2025/06/18 10:16:02 by kevwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

CFLAGSSANI = -Wall -Wextra -Werror -fsanitize=thread -g

FILE = main.c \
philosophers_utlis.c

SRC = ${FILE:.c=.o}

NAME = philo

all: ${NAME}

%.o:%.c
	${CC} ${CFLAGS} -c $^ -o $@

${NAME}:${SRC}
	${CC} ${CFLAGS} $^ -o $@

sani:${SRC}
	${CC} ${CFLAGSSANI} $^ -o philo_sani

clean:
	rm -f main.o \
	philosophers_utlis.o

fclean : clean
	rm -f philo
	rm -f philo_sani

re : fclean
	make
