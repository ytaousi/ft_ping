NAME = ft_ping

SRCS = ./ft_ping.c ./utils.c ./ft_packet.c ./ft_parse.c 

OBJS = $(SRCS:.c=.o)

all: $(NAME)

# @make -C libft <-- Compile libft.a
# -L libft -lft  <-- Compile with libft.a
$(NAME): $(OBJS)
	@gcc -Wall -Wextra -Werror -o $(NAME) $(OBJS)

%.o: %.c
	@gcc -Wall -Wextra -Werror -c $< -o $@

# @make clean -C libft
clean:
	@rm -f $(OBJS)

# @make fclean -C libft
fclean: clean
	@rm -f $(NAME)

re: fclean all