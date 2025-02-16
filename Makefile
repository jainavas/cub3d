LIB = ar rcs
RM = rm -f

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g3

SRC_DIR = src
LIB_DIR = minilibx-linux

SRC = func_map/map0.c func_map/map1.c func_map/map2.c cub3d.c graphics0.c imglisthandle.c math0.c mlxutils.c

OBJ = $(SRC:.c=.o)
INCLUDE = cub3d.h

NAME = cub3d

MLXA = minilibx-linux/libmlx_Linux.a

LIBFTA = libft_ext/libft.a

all: $(NAME)

%.o: %.c
	$(CC) $(CCFLAGS) -I/libft_ext/libft.h -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@cd libft_ext && make
	@$(CC) $(CCFLAGS) $(OBJ) -I ../cub3d.h -I /libft_ext/libft.h $(MLXA) $(PRINTFA) $(LIBFTA) -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(RM) $(OBJ)
	@cd libft_ext && make clean

fclean: clean
	$(RM) $(NAME)
	@cd libft_ext && make fclean

re: fclean all

.PHONY: all clean fclean re