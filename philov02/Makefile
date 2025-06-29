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
philosophers_utlis.c \
philosophers_check.c \
philo_init.c \
philo_free.c \
philo_pthread.c \
philo_routine.c \
philo_time.c \
philo_write.c

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
	philosophers_utlis.o \
	philosophers_check.o \
	philo_init.o \
	philo_free.o \
	philo_pthread.o \
	philo_routine.o \
	philo_time.o \
	philo_write.o

fclean : clean
	rm -f philo
	rm -f philo_sani

re : fclean
	make
