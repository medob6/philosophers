NAME	= philo_bonus
CC		= cc

SRC		= main.c utils.c parser.c clean.c monitor.c error.c

FLAGS	= -Wall -Werror -Wextra -pthread -g
TSAN	= -fsanitize=thread 
ASAN	= -fsanitize=address

all: $(NAME)

$(NAME):
	@$(CC) $(FLAGS) $(SRC) -o $(NAME)

tsan: 
	@$(CC) $(FLAGS) $(TSAN) $(SRC) -o $(NAME)

asan:
	@$(CC) $(FLAGS) $(ASAN) $(SRC) -o $(NAME)

clean:
	@rm -f $(NAME)

fclean: clean

re: fclean all
