LIB = ar rcs
RM = rm -f

CC = cc
CCFLAGS = -Wall -Wextra -Werror -g3 -fsanitize=address

SRC_DIR = src
LIB_DIR = minilibx-linux

SRC = core/main.c core/cleanup.c graphics/raycasting.c \
		graphics/render.c graphics/texture.c input/movement.c \
		map/generator.c map/parser.c map/parser2.c map/validator.c map/parser_utils.c \
		utils/image_utils.c utils/math_utils.c

OBJ = $(SRC:.c=.o)
INCLUDE = cub3d.h

NAME = cub3d

MLXA = minilibx-linux/libmlx_Linux.a

LIBFTA = libft_ext/libft.a

GREEN = \033[0;32m
RESET = \033[0m

all: $(NAME)
	@echo "$(GREEN)\n\n──────────────────────────────────────────────────────────────────────────────"
	@echo "─██████████████─██████──██████─██████████████───██████████████─████████████───"
	@echo "─██░░░░░░░░░░██─██░░██──██░░██─██░░░░░░░░░░██───██░░░░░░░░░░██─██░░░░░░░░████─"
	@echo "─██░░██████████─██░░██──██░░██─██░░██████░░██───██████████░░██─██░░████░░░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░██──██░░██───────────██░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░██████░░████─██████████░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░░░░░░░░░░░██─██░░░░░░░░░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░████████░░██─██████████░░██─██░░██──██░░██─"
	@echo "─██░░██─────────██░░██──██░░██─██░░██────██░░██─────────██░░██─██░░██──██░░██─"
	@echo "─██░░██████████─██░░██████░░██─██░░████████░░██─██████████░░██─██░░████░░░░██─"
	@echo "─██░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░░░░░██─██░░░░░░░░░░██─██░░░░░░░░████─"
	@echo "─██████████████─██████████████─████████████████─██████████████─████████████───"
	@echo "──────────────────────────────────────────────────────────────────────────────"
	@echo "$(RESET)\n*** Move with WASD, turn left and right with arrows ***"
	@echo "$(GREEN)\nEnjoy the game!"

%.o: %.c
	$(CC) $(CCFLAGS) -I/libft_ext/libft.h -I/usr/include -Iminilibx-linux -O3 -c $< -o $@

$(NAME): $(OBJ)
	@cd libft_ext && make
	@cd minilibx-linux && make
	@$(CC) $(CCFLAGS) $(OBJ) -I ../cub3d.h -I /libft_ext/libft.h $(MLXA) $(PRINTFA) $(LIBFTA) -Iminilibx-linux -lXext -lX11 -lm -lz -o $(NAME)

clean:
	$(RM) $(OBJ)
	@cd minilibx-linux && make
	@cd libft_ext && make clean

fclean: clean
	$(RM) $(NAME)
	@cd minilibx-linux && make
	@cd libft_ext && make fclean

re: fclean all

.PHONY: all clean fclean re
