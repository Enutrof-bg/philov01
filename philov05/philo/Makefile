# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: kevwang <kevwang@student.42.fr>            +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/30 13:28:32 by kevwang           #+#    #+#              #
#    Updated: 2025/06/30 13:28:32 by kevwang          ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = cc

CFLAGS = -Wall -Wextra -Werror

FILE = main.c \
philo_free.c \
philo_init.c \
philo_thread.c \
philo_utils.c \
philo_check.c \
philo_time.c \
philo_get.c \
philo_route.c \
philo_get2.c \
philo_eat_sleep_think.c
# philo_routine.c \

SRC = ${FILE:.c=.o}

NAME = philo

all: ${NAME}

${NAME}:${SRC}
	${CC} ${CFLAGS} $^ -o $@

%.o:%.c
	${CC} ${CFLAGS} -c $^

clean:
	rm -f main.o \
	philo_free.o \
		philo_init.o \
		philo_routine.o \
		philo_thread.o \
		philo_utils.o \
		philo_check.o \
		philo_time.o \
		philo_get.o \
		philo_route.o \
		philo_get2.o \
		philo_eat_sleep_think.o

fclean: clean
	rm -f philo

re:fclean
	make