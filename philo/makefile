NAME	= philo
CC		= cc

SRC		= main.c error.c init_data.c clean_data.c philo_creat.c monitor.c utils.c helpers.c 

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
