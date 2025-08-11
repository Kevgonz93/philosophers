NAME = philosophers

CC = cc

CFLAGS = -Wall -Wextra -Werror

SRCS = main.c
SRCS_AUX = ft_atoi.c \
	ft_atoll_safe.c \
	ft_atolli.c \
	ft_isdigit.c \
	ft_isnum.c \
	ft_strcmp.c \
	ft_strlen.c
SRCS_SRC = actions.c \
	checkers.c \
	closep.c \
	forks.c \
	initial_settings.c \
	mutex.c \
	philosophers.c \
	utils.c 

 SRCS_ALL := \
    $(SRCS) \
    $(addprefix aux/,       $(SRCS_AUX))       \
	$(addprefix src/,		$(SRCS_SRC))

OBJS = $(SRCS_ALL:.c=.o)

all: $(NAME)

$(NAME): $(OBJS)
		$(CC) $(CFLAGS) -o $(NAME) $(OBJS)
	
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
