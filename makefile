# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rafaefer <rafaefer@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2024/10/07 15:45:11 by rafaefer          #+#    #+#              #
#    Updated: 2024/10/07 15:45:12 by rafaefer         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = so_long

CC = cc
CFLAGS = -Wall -Wextra -Werror -g -Iheaders/
MFLAGS = -lX11 -lXext
RM = rm -rf

LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a
LIBFT_REPO = https://github.com/RafaelSKD/Libft_Ultra.git

MLX_DIR = minilibx-linux
MLX = $(MLX_DIR)/libmlx_Linux.a
MLX_REPO = https://github.com/42Paris/minilibx-linux.git

SRCS = 	game/so_long.c\
		game/check_path.c\
		game/controls.c\
		game/create_map.c\
		game/errors.c\
		game/get_map.c\
		
OBJS = $(SRCS:%.c=%.o)
LIBRARY := -L$(MLX_DIR) -lmlx -lX11 -lXext -lm

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
	@if [ ! -d "$(LIBFT_DIR)" ]; then \
		echo "Cloning libft from $(LIBFT_REPO)..."; \
		git clone $(LIBFT_REPO) $(LIBFT_DIR); \
	fi
	@$(MAKE) -C $(LIBFT_DIR)

$(MLX):
	@if [ ! -d "$(MLX_DIR)" ]; then \
		echo "Cloning minilibx-linux from $(MLX_REPO)..."; \
		git clone $(MLX_REPO) $(MLX_DIR); \
	fi
	@$(MAKE) -C $(MLX_DIR)

$(NAME): $(OBJS) $(LIBFT) $(MLX)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MFLAGS) -o $(NAME)

clean:
	@$(MAKE) clean -C $(LIBFT_DIR)
	@$(MAKE) clean -C $(MLX_DIR)
	@$(RM) $(OBJS)
	
fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR)
	@$(RM) $(NAME)

re: fclean all

.PHONY: all clean fclean re

