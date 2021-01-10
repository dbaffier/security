NAME = ft_strace

CC = gcc

FLAGS = -Wextra -Wall -Werror

SRC_DIR = src/

OBJS_DIR = objs/

INC = inc/

SRC =	main.c				\
		syscalls_64.c		\
		handle_str.c		\
		signal_table.c		\
		do_trace.c			\
		signal_handler.c	\
		error_table.c		\
		handle_execve.c

OBJS = $(addprefix $(OBJS_DIR), $(SRC:.c=.o))

all: $(OBJS_DIR) $(NAME)

$(OBJS_DIR):
	@mkdir -p $@

$(NAME): $(OBJS)
	$(CC) $(FLAGS) -o $@ $(OBJS)

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	$(CC) $(FLAGS) -o $@ -c $< -I $(INC)

clean:
	rm -rf $(OBJS_DIR)

fclean: clean
	$(RM) $(NAME)

re: fclean all
