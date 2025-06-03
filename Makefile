# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: aberenge <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 14:30:00 by aberenge          #+#    #+#              #
#    Updated: 2025/06/03 14:23:34 by aberenge         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= cub3d
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
INCDIR		= -I. -I./libs/Libft -I./libs/gnl -I./libs/minilibx
LIBFT_DIR	= libs/Libft
GNL_DIR		= libs/gnl
MLX_DIR		= libs/minilibx
LIBFT		= $(LIBFT_DIR)/libft.a
MLX			= $(MLX_DIR)/libmlx.a
MLX_FLAGS	= -lXext -lX11 -lm -lz

SRCDIR		= src
OBJDIR		= obj

SRCS		= main.c src/exit/exit.c

OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
			$(MAKE) -C $(LIBFT_DIR)

$(MLX):
			$(MAKE) -C $(MLX_DIR)

$(OBJDIR):
			mkdir -p $(OBJDIR)

$(OBJDIR)/%.o: %.c | $(OBJDIR)
			$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
			$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)

clean:
			rm -rf $(OBJDIR)
			$(MAKE) -C $(LIBFT_DIR) clean
			$(MAKE) -C $(MLX_DIR) clean

fclean: clean
			rm -f $(NAME)
			$(MAKE) -C $(LIBFT_DIR) fclean

re: fclean all

.PHONY: all clean fclean re
