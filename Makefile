# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 20:39:28 by hoskim            #+#    #+#              #
#    Updated: 2025/03/06 17:40:32 by hoskim           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = clang
CFLAGS = -Wall -Wextra -Werror
RM = rm -f

# setup of MiniLibX
MLX_DIR = mlx
MLX_FLAGS = -Lmlx -lmlx -lX11 -lXext -lm

SRC_DIR = srcs/
SRC_FILES = main.c game_input.c game_logic.c game_render.c \
			game_init.c map_parser.c map_validator.c utils.c

SRCS = $(addprefix $(SRC_DIR), $(SRC_FILES))
OBJS = $(SRCS:.c=.o)

INCLUDES = -I$(shell pwd)/includes

all: $(NAME)

$(NAME): $(OBJS)
		@make -C $(MLX_DIR)
		$(CC) $(CFLAGS) $(OBJS) $(MLX_FLAGS) -o $(NAME)
		@echo "$(NAME) created!"

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
		@make -C $(MLX_DIR) clean
		$(RM) $(OBJS)
		@echo "Objects removed!"

fclean: clean
		$(RM) $(NAME)
		@echo "$(NAME) removed!"

re: fclean all

.PHONY: all clean fclean re