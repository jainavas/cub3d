LIB = ar rcs
RM = rm -f

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src
LIB_DIR = minilibx-linux

SRC = func_map/map0.c func_map/map1.c so_long.c graphics0.c graphics1.c

OBJ = $(SRC:.c=.o)
INCLUDE = so_long.h

NAME = so_long

MLXA = minilibx-linux/libmlx_Linux.a

LIBFTA = libft/libft.a

PRINTFA = printf/libftprintf.a

all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -I/libft/libft.h -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@cd libft && make
	@cd printf && make
	@$(CC) $(CCFLAGS) $(OBJ) -I ../so_long.h -I /libft/libft.h $(MLXA) $(PRINTFA) $(LIBFTA) -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(RM) $(OBJ)
	@cd libft && make clean
	@cd printf && make clean

fclean: clean
	$(RM) $(NAME)
	@cd printf && make fclean
	@cd libft && make fclean

re: fclean all

.PHONY: all clean fclean re