# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mpapin <marvin@42.fr>                      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/06/03 14:30:00 by aberenge          #+#    #+#              #
#    Updated: 2025/06/10 18:15:36 by mpapin           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= CUB3D
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

SRCS		= main.c src/exit/exit.c src/init.c src/raycasting.c src/render.c src/controls.c \
			  src/parsing/parsing.c libs/gnl/get_next_line.c
			  
OBJS		= $(SRCS:%.c=$(OBJDIR)/%.o)

all: $(LIBFT) $(MLX) $(NAME)

$(LIBFT):
			@echo "Compiling libft..."
			@$(MAKE) -C $(LIBFT_DIR) -s

$(MLX):
			@echo "Compiling MLX..."
			@cd $(MLX_DIR) && ./configure >/dev/null 2>&1 || true
			@$(MAKE) -C $(MLX_DIR) >/dev/null 2>&1

$(OBJDIR):
			@echo "Compiling all .c"
			@mkdir -p $(OBJDIR)/src

$(OBJDIR)/%.o: %.c | $(OBJDIR)
			@mkdir -p $(dir $@)
			@$(CC) $(CFLAGS) $(INCDIR) -c $< -o $@

$(NAME): $(OBJS) $(LIBFT) $(MLX)
			@$(CC) $(CFLAGS) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS) -o $(NAME)
			@echo "$(NAME) compiled successfully!"

clean:
			@echo "Cleaning objects..."
			@rm -rf $(OBJDIR)
			@$(MAKE) -C $(LIBFT_DIR) clean -s >/dev/null 2>&1
			@cd $(MLX_DIR) && ./configure >/dev/null 2>&1 || true
			@$(MAKE) -C $(MLX_DIR) clean >/dev/null 2>&1

fclean: clean
			@echo "Full clean..."
			@rm -f $(NAME)
			@$(MAKE) -C $(LIBFT_DIR) fclean -s >/dev/null 2>&1

re: fclean all

.PHONY: all clean fclean re
