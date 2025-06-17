NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror
SRC_MANDATORY = error.c parssing.c main.c get_time.c utils.c init.c \
lifesycle.c ft_monitoring.c utils2.c

OBJ_MANDATORY = $(SRC_MANDATORY:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_MANDATORY)
	$(CC) $(CFLAGS) $(OBJ_MANDATORY) -o $(NAME)
%.o : %.c philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_MANDATORY)
fclean : clean
	rm -rf $(NAME)
re : fclean all