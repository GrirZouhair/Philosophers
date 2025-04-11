NAME = philo
CC = cc
CFLAGS = -Wall -Wextra -Werror #-g -fsanitize=address

SRC_MANDATORY = MANDATORY/error.c MANDATORY/parssing.c MANDATORY/main.c MANDATORY/get_time.c MANDATORY/utils.c MANDATORY/init.c \
MANDATORY/lifesycle.c

OBJ_MANDATORY = $(SRC_MANDATORY:.c=.o)

all : $(NAME)

$(NAME) : $(OBJ_MANDATORY)
	$(CC) $(CFLAGS) $(OBJ_MANDATORY) -o $(NAME)
%.o : %.c ./MANDATORY/philo.h
	$(CC) $(CFLAGS) -c $< -o $@

clean :
	rm -rf $(OBJ_MANDATORY)
fclean : clean
	rm -rf $(NAME)
re : fclean all