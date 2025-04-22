# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 20:39:28 by hoskim            #+#    #+#              #
#    Updated: 2025/04/21 16:05:18 by hoskim           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long
CC = clang
CFLAGS = -Wall -Wextra -Werror -g

MLX = -Lmlx -lmlx -lXext -lX11 -lm
SRCS_DIR = ./srcs/
MAIN_DIR = $(SRCS_DIR)main/
MAP_MANAGER_DIR = $(SRCS_DIR)map_manager/
GAME_MANAGER_DIR = $(SRCS_DIR)game_manager/
UTILS_DIR = $(SRCS_DIR)utils/

SRCS = $(MAIN_DIR)so_long.c \
		$(GAME_MANAGER_DIR)events.c \
		$(GAME_MANAGER_DIR)game.c \
		$(GAME_MANAGER_DIR)render.c \
		$(GAME_MANAGER_DIR)window_manager.c \
		$(MAP_MANAGER_DIR)map_elements.c \
		$(MAP_MANAGER_DIR)get_map_data.c \
		$(MAP_MANAGER_DIR)if_valid_path.c \
		$(MAP_MANAGER_DIR)validate_map_data.c \
		$(MAP_MANAGER_DIR)count_map_lines.c \
		$(UTILS_DIR)memory_manager.c \
		$(UTILS_DIR)ft_str_utils.c \
		$(UTILS_DIR)ft_put_utils.c

OBJS = $(SRCS:.c=.o)
INCLUDES = -Iincludes -Imlx

all: $(NAME)

$(NAME): $(OBJS)
		$(MAKE) -C mlx
		$(CC) $(CFLAGS) $(OBJS) $(MLX) -o $(NAME)

%.o: %.c
		$(CC) $(CFLAGS) $(INCLUDES) -c $< -o $@

clean:
	$(MAKE) -C mlx clean
	rm -f $(OBJS)

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re