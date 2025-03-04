# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: hoskim <hoskim@student.42prague.com>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/04 20:39:28 by hoskim            #+#    #+#              #
#    Updated: 2025/03/04 22:50:41 by hoskim           ###   ########seoul.kr   #
#                                                                              #
# **************************************************************************** #

NAME = program
CC = clang
CFLAGS = -Wall -Wextra -Werror
MLX_PATH = mlx
MLX_LIB = $(MLX_PATH)/libmlx.a
MLX_FLAGS = -L$(MLX_PATH) -lmlx -lX11 -lXext -lm

SRCS = main.c
OBJS = $(SRCS:.c=.o)

all: $(NAME)

$(NAME): $(OBJS) $(MLX_LIB)
		$(CC) $(OBJS) $(MLX_FLAGS) -o $(NAME)

$(MLX_LIB):
		make -C $(MLX_PATH)

%.o: %.c
		$(CC) $(CFLAGS) -I$(MLX_PATH) -c $< -o $@

clean:
		rm -f $(OBJS)
		make -C $(MLX_PATH) clean

fclean: clean
		rm -f $(NAME)

re: fclean all

.PHONY: all clean fclean re