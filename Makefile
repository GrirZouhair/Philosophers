NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror

SRC_MANDATORY = MANDATORY/error.c MANDATORY/parssing.c MANDATORY/philo.c

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