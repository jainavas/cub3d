CC = cc
CFLAGS = -Wall -Wextra -Werror

NAME = libftprintf.a

SRCS = ft_printf.c ft_intputnbr_fd.c ft_intputchar_fd.c ft_intputstr_fd.c ft_strtoupper.c \
ft_strtolower.c ft_long_hex.c ft_putpointer.c ft_ultoa.c
OBJS = $(SRCS:.c=.o)
INCLUDE = ft_printf.h

all: $(NAME)

$(NAME): $(OBJS) $(INCLUDE)
	@$(AR) rcs $(NAME) $(OBJS)

clean:
	@rm -f $(OBJS)

fclean: clean
	@rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re
